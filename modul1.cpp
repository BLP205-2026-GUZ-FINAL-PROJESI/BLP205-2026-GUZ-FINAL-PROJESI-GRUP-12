#include "modul1.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// ==========================================
// 1. CIFT YONLU DOGRUSAL BAGLI LISTE (KITAP)
// ==========================================
bool kitapIDVarMi(KitapNode* basdugum, int id) {
    KitapNode* iter = basdugum;
    while (iter != NULL) {
        if (iter->kitapID == id) return true;
        iter = iter->next;
    }
    return false;
}

// 1. Kitap Basa Ekle
KitapNode* kitapBasaEkle(KitapNode* basdugum, int id, string ad, string yazar, int sayfa) {
    if (kitapIDVarMi(basdugum, id)) {
        cout << "[!] Hata: " << id << " ID'li kitap zaten mevcut.\n";
        return basdugum;
    }

    KitapNode* yeni = new KitapNode();
    yeni->kitapID = id;
    yeni->kitapAdi = ad;
    yeni->yazar = yazar;
    yeni->sayfaSayisi = sayfa;
    yeni->prev = NULL;
    yeni->next = basdugum;

    if (basdugum != NULL) {
        basdugum->prev = yeni;
    }
    cout << "[!] Kitap listenin basina eklendi.\n";
    return yeni;
}

// 2. Kitap Sona Ekle
KitapNode* kitapSonaEkle(KitapNode* basdugum, int id, string ad, string yazar, int sayfa) {
    if (kitapIDVarMi(basdugum, id)) {
        cout << "[!] Hata: " << id << " ID'li kitap zaten mevcut.\n";
        return basdugum;
    }

    KitapNode* yeni = new KitapNode();
    yeni->kitapID = id;
    yeni->kitapAdi = ad;
    yeni->yazar = yazar;
    yeni->sayfaSayisi = sayfa;
    yeni->next = NULL;
    yeni->prev = NULL;

    if (basdugum == NULL) {
        cout << "[OK] Kitap listenin sonuna eklendi.\n";
        return yeni;
    }

    KitapNode* iter = basdugum;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = yeni;
    yeni->prev = iter;

    cout << "[OK] Kitap listenin sonuna eklendi.\n";
    return basdugum;
}

// 3. Kitap Araya Ekle (Hedef ID Oncesine)
KitapNode* kitapArayaEkleOncesine(KitapNode* basdugum, int hedefID, int id, string ad, string yazar, int sayfa) {
    if (basdugum == NULL) {
        cout << "[!] Liste bos, hedef ID bulunamadi.\n";
        return basdugum;
    }
    if (kitapIDVarMi(basdugum, id)) {
        cout << "[!] Hata: " << id << " ID'li kitap zaten mevcut.\n";
        return basdugum;
    }

    if (basdugum->kitapID == hedefID) {
        return kitapBasaEkle(basdugum, id, ad, yazar, sayfa);
    }

    KitapNode* iter = basdugum;
    while (iter != NULL && iter->kitapID != hedefID) {
        iter = iter->next;
    }

    if (iter == NULL) {
        cout << "[!] Hedef ID (" << hedefID << ") bulunamadi.\n";
        return basdugum;
    }

    KitapNode* yeni = new KitapNode();
    yeni->kitapID = id;
    yeni->kitapAdi = ad;
    yeni->yazar = yazar;
    yeni->sayfaSayisi = sayfa;

    yeni->prev = iter->prev;
    yeni->next = iter;
    if (iter->prev != NULL) {
        iter->prev->next = yeni;
    }
    iter->prev = yeni;

    cout << "[OK] Kitap, " << hedefID << " ID'sinin oncesine eklendi.\n";
    return basdugum;
}

// 4. Kitap Sil (ID ile)
KitapNode* kitapSilID(KitapNode* basdugum, int id) {
    if (basdugum == NULL) {
        cout << "[!] Liste bos.\n";
        return NULL;
    }

    KitapNode* iter = basdugum;
    while (iter != NULL && iter->kitapID != id) {
        iter = iter->next;
    }

    if (iter == NULL) {
        cout << "[!] " << id << " ID'li kitap bulunamadi.\n";
        return basdugum;
    }

    if (iter == basdugum) {
        basdugum = iter->next;
        if (basdugum != NULL) {
            basdugum->prev = NULL;
        }
    }
    else {
        if (iter->prev != NULL) {
            iter->prev->next = iter->next;
        }
        if (iter->next != NULL) {
            iter->next->prev = iter->prev;
        }
    }

    delete iter;
    cout << "[OK] " << id << " ID'li kitap silindi.\n";
    return basdugum;
}

// 5. Kitaplari Bastan Sona Listele (next ile)
void kitaplariBastanSonaListele(KitapNode* basdugum) {
    if (basdugum == NULL) {
        cout << "\n[!] Kitap listesi bos.\n";
        return;
    }

    cout << "\n--- KITAP LISTESI (BASTAN SONA - NEXT ISARETCISI ILE) ---\n";
    cout << " " << left << setw(8) << "ID"
        << setw(28) << "Kitap Adi"
        << setw(22) << "Yazar"
        << setw(10) << "Sayfa" << endl;
    cout << "----------------------------------------------------------------------\n";

    KitapNode* iter = basdugum;
    while (iter != NULL) {
        cout << " " << left << setw(8) << iter->kitapID
            << setw(28) << iter->kitapAdi
            << setw(22) << iter->yazar
            << setw(10) << iter->sayfaSayisi << endl;
        iter = iter->next;
    }
}

// 6. Kitaplari Sondan Basa Listele (prev ile)
void kitaplariSondanBasaListele(KitapNode* basdugum) {
    if (basdugum == NULL) {
        cout << "\n[!] Kitap listesi bos.\n";
        return;
    }

    KitapNode* iter = basdugum;
    while (iter->next != NULL) {
        iter = iter->next;
    }

    cout << "\n--- KITAP LISTESI (SONDAN BASA - PREV ISARETCISI ILE TERS) ---\n";
    cout << " " << left << setw(8) << "ID"
        << setw(28) << "Kitap Adi"
        << setw(22) << "Yazar"
        << setw(10) << "Sayfa" << endl;
    cout << "----------------------------------------------------------------------\n";

    while (iter != NULL) {
        cout << " " << left << setw(8) << iter->kitapID
            << setw(28) << iter->kitapAdi
            << setw(22) << iter->yazar
            << setw(10) << iter->sayfaSayisi << endl;
        iter = iter->prev;
    }
}

// 7. Katalog Istatistik Analizi ve Filtreleme
void katalogAnaliziYap(KitapNode* basdugum, int sayfaEsigi) {
    if (basdugum == NULL) {
        cout << "\n[!] Liste bos oldugu icin analiz yapilamaz.\n";
        return;
    }

    int toplamKitap = 0;
    long toplamSayfa = 0;
    int minSayfa = basdugum->sayfaSayisi;
    int maxSayfa = basdugum->sayfaSayisi;
    string minKitapAdi = basdugum->kitapAdi;
    string maxKitapAdi = basdugum->kitapAdi;

    KitapNode* iter = basdugum;
    while (iter != NULL) {
        toplamKitap++;
        toplamSayfa += iter->sayfaSayisi;

        if (iter->sayfaSayisi < minSayfa) {
            minSayfa = iter->sayfaSayisi;
            minKitapAdi = iter->kitapAdi;
        }
        if (iter->sayfaSayisi > maxSayfa) {
            maxSayfa = iter->sayfaSayisi;
            maxKitapAdi = iter->kitapAdi;
        }
        iter = iter->next;
    }

    double ortalamaSayfa = (double)toplamSayfa / toplamKitap;

    cout << "\n--- KATALOG ISTATISTIK ANALIZI ---\n";
    cout << "Toplam Kitap Sayisi : " << toplamKitap << "\n";
    cout << "Toplam Sayfa Sayisi : " << toplamSayfa << "\n";
    cout << "Ortalama Sayfa      : " << fixed << setprecision(2) << ortalamaSayfa << "\n";
    cout << "En Az Sayfali Kitap : " << minKitapAdi << " (" << minSayfa << " sayfa)\n";
    cout << "En Cok Sayfali Kitap: " << maxKitapAdi << " (" << maxSayfa << " sayfa)\n";

    cout << "\n--- SAYFA ESIK DEGERINI (" << sayfaEsigi << ") ASAN KITAPLAR ---\n";
    bool varMi = false;
    iter = basdugum;
    while (iter != NULL) {
        if (iter->sayfaSayisi > sayfaEsigi) {
            cout << " " << left << setw(8) << iter->kitapID
                << setw(28) << iter->kitapAdi
                << setw(22) << iter->yazar
                << setw(10) << iter->sayfaSayisi << endl;
            varMi = true;
        }
        iter = iter->next;
    }
    if (!varMi) {
        cout << "[!] " << sayfaEsigi << " sayfa sinirini asan kitap bulunamadi.\n";
    }
}

void kitapListesiniTemizle(KitapNode* basdugum) {
    KitapNode* iter = basdugum;
    while (iter != NULL) {
        KitapNode* sil = iter;
        iter = iter->next;
        delete sil;
    }
}

// ==========================================
// 2. TEK YONLU DAIRESEL BAGLI LISTE (DUYURU)
// ==========================================
DuyuruNode* duyuruEkleDairesel(DuyuruNode* basdugum, int no, string baslik) {
    DuyuruNode* yeni = new DuyuruNode();
    yeni->duyuruNo = no;
    yeni->baslik = baslik;

    if (basdugum == NULL) {
        yeni->next = yeni;
        return yeni;
    }

    DuyuruNode* iter = basdugum;
    while (iter->next != basdugum) {
        iter = iter->next;
    }
    iter->next = yeni;
    yeni->next = basdugum;
    return basdugum;
}

void duyuruTamTurYazdir(DuyuruNode* basdugum) {
    if (basdugum == NULL) {
        cout << "\n[!] Duyuru panosu bos.\n";
        return;
    }

    cout << "\n--- DAIRESEL BAGLI LISTE DUYURU PANOSU (1 TAM TUR) ---\n";
    DuyuruNode* iter = basdugum;
    do {
        cout << " [Duyuru #" << iter->duyuruNo << "] " << iter->baslik << "\n";
        iter = iter->next;
    } while (iter != basdugum);
    cout << " -> Baslangic dugumune (#" << basdugum->duyuruNo << ") geri donuldu.\n";
}

// ==========================================
// 3. DOSYA ISLEMLERI (ofstream & ifstream)
// ==========================================
void kataloguDosyayaYaz(KitapNode* basdugum, const string& dosyaAdi) {
    ofstream outFile(dosyaAdi.c_str());
    if (!outFile.is_open()) {
        cout << "[!] Hata: '" << dosyaAdi << "' dosyasi acilamadi.\n";
        return;
    }

    KitapNode* iter = basdugum;
    while (iter != NULL) {
        outFile << iter->kitapID << "|"
            << iter->kitapAdi << "|"
            << iter->yazar << "|"
            << iter->sayfaSayisi << "\n";
        iter = iter->next;
    }

    outFile.close();
    cout << "[OK] Katalog '" << dosyaAdi << "' dosyasina yazildi.\n";
}

void dosyadanOkuVeGoster(const string& dosyaAdi) {
    ifstream inFile(dosyaAdi.c_str());
    if (!inFile.is_open()) {
        cout << "[!] Hata: '" << dosyaAdi << "' dosyasi okunamadi.\n";
        return;
    }

    cout << "\n--- DOSYADAN OKUNAN KATALOG KAYITLARI (" << dosyaAdi << ") ---\n";
    cout << " " << left << setw(8) << "ID"
        << setw(28) << "Kitap Adi"
        << setw(22) << "Yazar"
        << setw(10) << "Sayfa" << endl;
    cout << "----------------------------------------------------------------------\n";

    string satir;
    int sayac = 0;
    while (getline(inFile, satir)) {
        if (satir.empty()) continue;

        stringstream ss(satir);
        string idStr, ad, yazar, sayfaStr;

        if (getline(ss, idStr, '|') &&
            getline(ss, ad, '|') &&
            getline(ss, yazar, '|') &&
            getline(ss, sayfaStr)) {
            sayac++;
            cout << " " << left << setw(8) << idStr
                << setw(28) << ad
                << setw(22) << yazar
                << setw(10) << sayfaStr << endl;
        }
    }

    if (sayac == 0) {
        cout << "[!] Dosyada gosterilecek kayit bulunamadi.\n";
    }
    inFile.close();
}

// ==========================================
// GIRIS YARDIMCILARI & MODUL 1 MENUSU
// ==========================================
int sayiAl(const string& mesaj) {
    int x;
    while (true) {
        cout << mesaj;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "[!] Gecersiz sayi, tekrar girin.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string metinAl(const string& mesaj) {
    string s;
    cout << mesaj;
    getline(cin, s);
    return s;
}

void modul1Menu() {
    KitapNode* kitapBas = NULL;
    DuyuruNode* duyuruBas = NULL;
    int duyuruSayac = 0;
    const string dosyaAdi = "katalog.txt";

    // Ornek baslangic duyurusu
    duyuruSayac++;
    duyuruBas = duyuruEkleDairesel(duyuruBas, duyuruSayac, "Yeni donem kitap katalogu acildi.");

    int altSecim;
    do {
        cout << "\n--- [MODUL 1: BAGLI LISTELER & DOSYA ISLEMLERI] ---\n";
        cout << "1. Kitap Basa Ekle (Cift Yonlu Bagli Liste)\n";
        cout << "2. Kitap Sona Ekle (Cift Yonlu Bagli Liste)\n";
        cout << "3. Kitap Araya Ekle (Hedef ID Oncesine)\n";
        cout << "4. Kitap Sil (ID ile)\n";
        cout << "5. Kitaplari Bastan Sona Listele (next ile Ileri)\n";
        cout << "6. Kitaplari Sondan Basa Listele (prev ile Ters)\n";
        cout << "7. Katalog Istatistik Analizi (Toplam, Ortalama, Min, Max, Filtre)\n";
        cout << "8. Dairesel Bagli Liste Duyuru Panosunu Goruntule / Ekle\n";
        cout << "9. Katalogu Dosyaya Yaz (ofstream) ve Dosyadan Oku (ifstream)\n";
        cout << "0. Ana Menuye Don\n";

        altSecim = sayiAl("Alt Seciminiz: ");

        switch (altSecim) {
        case 1: {
            int id = sayiAl("Kitap ID: ");
            string ad = metinAl("Kitap Adi: ");
            string yazar = metinAl("Yazar Adi: ");
            int sayfa = sayiAl("Sayfa Sayisi: ");
            kitapBas = kitapBasaEkle(kitapBas, id, ad, yazar, sayfa);
            break;
        }
        case 2: {
            int id = sayiAl("Kitap ID: ");
            string ad = metinAl("Kitap Adi: ");
            string yazar = metinAl("Yazar Adi: ");
            int sayfa = sayiAl("Sayfa Sayisi: ");
            kitapBas = kitapSonaEkle(kitapBas, id, ad, yazar, sayfa);
            break;
        }
        case 3: {
            int hedefID = sayiAl("Oncesine eklenecek Hedef Kitap ID: ");
            int id = sayiAl("Yeni Kitap ID: ");
            string ad = metinAl("Yeni Kitap Adi: ");
            string yazar = metinAl("Yeni Yazar Adi: ");
            int sayfa = sayiAl("Yeni Sayfa Sayisi: ");
            kitapBas = kitapArayaEkleOncesine(kitapBas, hedefID, id, ad, yazar, sayfa);
            break;
        }
        case 4: {
            int id = sayiAl("Silinecek Kitap ID: ");
            kitapBas = kitapSilID(kitapBas, id);
            break;
        }
        case 5:
            kitaplariBastanSonaListele(kitapBas);
            break;
        case 6:
            kitaplariSondanBasaListele(kitapBas);
            break;
        case 7: {
            int esik = sayiAl("Sayfa esik degeri: ");
            katalogAnaliziYap(kitapBas, esik);
            break;
        }
        case 8: {
            duyuruTamTurYazdir(duyuruBas);
            int ekle = sayiAl("\nYeni duyuru eklemek ister misiniz? (1: Evet, 0: Hayir): ");
            if (ekle == 1) {
                string baslik = metinAl("Duyuru Basligi/Metni: ");
                duyuruSayac++;
                duyuruBas = duyuruEkleDairesel(duyuruBas, duyuruSayac, baslik);
                duyuruTamTurYazdir(duyuruBas);
            }
            break;
        }
        case 9:
            kataloguDosyayaYaz(kitapBas, dosyaAdi);
            dosyadanOkuVeGoster(dosyaAdi);
            break;
        case 0:
            cout << "Ana menuye donuluyor...\n";
            break;
        default:
            cout << "[!] Gecersiz secim! 0-9 arasinda bir deger girin.\n";
            break;
        }
    } while (altSecim != 0);

    kitapListesiniTemizle(kitapBas);
}

int main() {
    modul1Menu();
    return 0;
}