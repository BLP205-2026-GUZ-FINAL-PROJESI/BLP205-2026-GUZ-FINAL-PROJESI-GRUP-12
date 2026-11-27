#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ==========================================
// 1. CIFT YONLU DOGRUSAL BAGLI LISTE (KITAP)
// ==========================================
struct KitapNode {
    int kitapID;
    string kitapAdi;
    string yazar;
    int sayfaSayisi;
    KitapNode* next;
    KitapNode* prev;
};

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
    cout << "[OK] Kitap listenin basina eklendi.\n";
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

void kitapListesiniTemizle(KitapNode* basdugum) {
    KitapNode* iter = basdugum;
    while (iter != NULL) {
        KitapNode* sil = iter;
        iter = iter->next;
        delete sil;
    }
}

// ==========================================
// GIRIS YARDIMCILARI & MODUL 1 MENUSU (1-6)
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
    int altSecim;

    do {
        cout << "\n--- [MODUL 1: BAGLI LISTELER & DOSYA ISLEMLERI] ---\n";
        cout << "1. Kitap Basa Ekle (Cift Yonlu Bagli Liste)\n";
        cout << "2. Kitap Sona Ekle (Cift Yonlu Bagli Liste)\n";
        cout << "3. Kitap Araya Ekle (Hedef ID Oncesine)\n";
        cout << "4. Kitap Sil (ID ile)\n";
        cout << "5. Kitaplari Bastan Sona Listele (next ile Ileri)\n";
        cout << "6. Kitaplari Sondan Basa Listele (prev ile Ters)\n";
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
        case 0:
            cout << "Ana menuye donuluyor...\n";
            break;
        default:
            cout << "[!] Gecersiz secim! 0-6 arasinda bir deger girin.\n";
            break;
        }
    } while (altSecim != 0);

    kitapListesiniTemizle(kitapBas);
}

int main() {
    modul1Menu();
    return 0;
}
