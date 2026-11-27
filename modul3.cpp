#include "modul3.h"
#include <iomanip>
#include <iostream>
#include <limits>

namespace {

int sayiAl(const std::string& mesaj) {
    int deger;
    while (true) {
        std::cout << mesaj;
        if (std::cin >> deger) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return deger;
        }
        std::cout << "[!] Gecersiz giris, lutfen tam sayi girin.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void kitapTakasEt(Kitap& a, Kitap& b, long long& takasSayisi) {
    Kitap gecici = a;
    a = b;
    b = gecici;
    takasSayisi++;
}

int quickSortBolumle(Kitap* dizi, int sol, int sag, QuickSonuc& sonuc) {
    int pivotId = dizi[sag].id;
    int i = sol - 1;

    for (int j = sol; j < sag; ++j) {
        sonuc.karsilastirmaSayisi++;
        if (dizi[j].id <= pivotId) {
            i++;
            if (i != j) {
                kitapTakasEt(dizi[i], dizi[j], sonuc.takasSayisi);
            }
        }
    }

    if (i + 1 != sag) {
        kitapTakasEt(dizi[i + 1], dizi[sag], sonuc.takasSayisi);
    }
    return i + 1;
}

void quickSortYinelemeli(Kitap* dizi, int sol, int sag, QuickSonuc& sonuc) {
    if (sol < sag) {
        int pivotIndex = quickSortBolumle(dizi, sol, sag, sonuc);
        quickSortYinelemeli(dizi, sol, pivotIndex - 1, sonuc);
        quickSortYinelemeli(dizi, pivotIndex + 1, sag, sonuc);
    }
}

} // namespace

Kitap* modul3KatalogDiziyeAktar(const KitapKatalog& katalog, int& boyut) {
    boyut = 0;
    const KitapDugum* sayac = katalog.head;
    while (sayac != nullptr) {
        boyut++;
        sayac = sayac->next;
    }

    if (boyut <= 0) {
        boyut = 0;
        return nullptr;
    }

    Kitap* dizi = new Kitap[boyut];
    const KitapDugum* curr = katalog.head;
    int idx = 0;
    while (curr != nullptr) {
        dizi[idx++] = curr->veri;
        curr = curr->next;
    }
    return dizi;
}

Kitap* modul3DiziKopyala(const Kitap* kaynak, int boyut) {
    if (kaynak == nullptr || boyut <= 0) {
        return nullptr;
    }
    Kitap* kopya = new Kitap[boyut];
    for (int i = 0; i < boyut; ++i) {
        kopya[i] = kaynak[i];
    }
    return kopya;
}

void modul3DiziYazdir(const Kitap* dizi, int boyut, const std::string& baslik) {
    if (dizi == nullptr || boyut <= 0) {
        std::cout << "[BILGI] Listelenecek kitap dizisi bos.\n";
        return;
    }

    std::cout << "\n--- " << baslik << " ---\n";
    std::cout << " " << std::left << std::setw(6) << "ID"
              << std::setw(28) << "Kitap Adi"
              << std::setw(20) << "Yazar"
              << std::right << std::setw(8) << "Sayfa" << "\n";
    std::cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < boyut; ++i) {
        std::cout << " " << std::left << std::setw(6) << dizi[i].id
                  << std::setw(28) << dizi[i].ad
                  << std::setw(20) << dizi[i].yazar
                  << std::right << std::setw(8) << dizi[i].sayfaSayisi << "\n";
    }
}

BubbleSonuc modul3BubbleSortSayfa(Kitap* dizi, int boyut) {
    BubbleSonuc sonuc{0, 0};
    if (dizi == nullptr || boyut <= 1) {
        return sonuc;
    }

    for (int i = 0; i < boyut - 1; ++i) {
        bool degisti = false;
        for (int j = 0; j < boyut - i - 1; ++j) {
            sonuc.karsilastirmaSayisi++;
            if (dizi[j].sayfaSayisi > dizi[j + 1].sayfaSayisi) {
                kitapTakasEt(dizi[j], dizi[j + 1], sonuc.takasSayisi);
                degisti = true;
            }
        }
        if (!degisti) {
            break;
        }
    }
    return sonuc;
}

InsertionSonuc modul3InsertionSortSayfa(Kitap* dizi, int boyut) {
    InsertionSonuc sonuc{0, 0};
    if (dizi == nullptr || boyut <= 1) {
        return sonuc;
    }

    for (int i = 1; i < boyut; ++i) {
        Kitap anahtar = dizi[i];
        int j = i - 1;

        while (j >= 0) {
            sonuc.karsilastirmaSayisi++;
            if (dizi[j].sayfaSayisi > anahtar.sayfaSayisi) {
                dizi[j + 1] = dizi[j];
                sonuc.kaydirmaSayisi++;
                j--;
            } else {
                break;
            }
        }
        dizi[j + 1] = anahtar;
    }
    return sonuc;
}

QuickSonuc modul3QuickSortId(Kitap* dizi, int boyut) {
    QuickSonuc sonuc{0, 0};
    if (dizi == nullptr || boyut <= 1) {
        return sonuc;
    }

    quickSortYinelemeli(dizi, 0, boyut - 1, sonuc);
    return sonuc;
}

BinaryAramaSonuc modul3BinarySearchId(const Kitap* siraliDizi, int boyut, int arananId) {
    BinaryAramaSonuc sonuc{false, -1, 0, Kitap{0, "", "", 0}};
    if (siraliDizi == nullptr || boyut <= 0) {
        return sonuc;
    }

    int sol = 0;
    int sag = boyut - 1;

    while (sol <= sag) {
        sonuc.adimSayisi++;
        int orta = sol + (sag - sol) / 2;

        if (siraliDizi[orta].id == arananId) {
            sonuc.bulundu = true;
            sonuc.indeks = orta;
            sonuc.kitap = siraliDizi[orta];
            return sonuc;
        } else if (siraliDizi[orta].id < arananId) {
            sol = orta + 1;
        } else {
            sag = orta - 1;
        }
    }

    return sonuc;
}

void modul3OrnekKatalogYukle(KitapKatalog& katalog) {
    modul3KatalogTemizle(katalog);

    const Kitap ornekler[5] = {
        {105, "Veri Yapilari", "A. Yilmaz", 340},
        {101, "Algoritmalara Giris", "E. Kaya", 460},
        {108, "Isletim Sistemleri", "M. Demir", 290},
        {103, "Bilgisayar Aglari", "Z. Sahin", 410},
        {106, "Veritabani Sistemleri", "K. Arslan", 220}
    };

    for (int i = 0; i < 5; ++i) {
        KitapDugum* yeni = new KitapDugum{ornekler[i], katalog.tail, nullptr};
        if (katalog.tail == nullptr) {
            katalog.head = yeni;
            katalog.tail = yeni;
        } else {
            katalog.tail->next = yeni;
            katalog.tail = yeni;
        }
    }
}

void modul3KatalogTemizle(KitapKatalog& katalog) {
    KitapDugum* curr = katalog.head;
    while (curr != nullptr) {
        KitapDugum* silinecek = curr;
        curr = curr->next;
        delete silinecek;
    }
    katalog.head = nullptr;
    katalog.tail = nullptr;
}

void modul3Menu(const KitapKatalog* disKatalog) {
    KitapKatalog yedekKatalog{nullptr, nullptr};
    const KitapKatalog* aktifKatalog = disKatalog;

    if (aktifKatalog == nullptr || aktifKatalog->head == nullptr) {
        modul3OrnekKatalogYukle(yedekKatalog);
        aktifKatalog = &yedekKatalog;
    }

    int secim = -1;
    do {
        std::cout << "\n--- [MODUL 3: SIRALAMA VE ARAMA ALGORITMALARI] ---\n";
        std::cout << "1. Bubble Sort vs Insertion Sort (Sayfa Sayisina Gore)\n";
        std::cout << "2. Quick Sort (ID'ye Gore) ve Binary Search (Ikili Arama)\n";
        std::cout << "0. Ana Menuye Don\n";

        secim = sayiAl("Alt Seciminiz: ");

        switch (secim) {
        case 1: {
            int boyut = 0;
            Kitap* kaynak = modul3KatalogDiziyeAktar(*aktifKatalog, boyut);
            if (kaynak == nullptr || boyut == 0) {
                std::cout << "[!] Katalog bos, siralanacak kitap yok.\n";
                break;
            }

            modul3DiziYazdir(kaynak, boyut, "SIRALAMA ONCESI DIZI (BAGLI LISTEDEN AKTARILAN)");

            Kitap* bubbleDizi = modul3DiziKopyala(kaynak, boyut);
            Kitap* insertionDizi = modul3DiziKopyala(kaynak, boyut);

            BubbleSonuc bubbleSonuc = modul3BubbleSortSayfa(bubbleDizi, boyut);
            InsertionSonuc insertionSonuc = modul3InsertionSortSayfa(insertionDizi, boyut);

            modul3DiziYazdir(bubbleDizi, boyut, "BUBBLE SORT SONUCU (SAYFA SAYISINA GORE)");
            std::cout << "  Karsilastirma Sayisi: " << bubbleSonuc.karsilastirmaSayisi
                      << " | Takas Sayisi: " << bubbleSonuc.takasSayisi << "\n";

            modul3DiziYazdir(insertionDizi, boyut, "INSERTION SORT SONUCU (SAYFA SAYISINA GORE)");
            std::cout << "  Karsilastirma Sayisi: " << insertionSonuc.karsilastirmaSayisi
                      << " | Kaydirma Sayisi: " << insertionSonuc.kaydirmaSayisi << "\n";

            delete[] bubbleDizi;
            delete[] insertionDizi;
            delete[] kaynak;
            break;
        }
        case 2: {
            int boyut = 0;
            Kitap* siraliDizi = modul3KatalogDiziyeAktar(*aktifKatalog, boyut);
            if (siraliDizi == nullptr || boyut == 0) {
                std::cout << "[!] Katalog bos, siralanacak ve aranacak kitap yok.\n";
                break;
            }

            QuickSonuc quickSonuc = modul3QuickSortId(siraliDizi, boyut);
            modul3DiziYazdir(siraliDizi, boyut, "QUICK SORT SONUCU (ID DEGERINE GORE SIRALI)");
            std::cout << "  Karsilastirma Sayisi: " << quickSonuc.karsilastirmaSayisi
                      << " | Takas Sayisi: " << quickSonuc.takasSayisi << "\n";

            int arananId = sayiAl("Aranacak Kitap ID: ");
            BinaryAramaSonuc aramaSonuc = modul3BinarySearchId(siraliDizi, boyut, arananId);

            if (aramaSonuc.bulundu) {
                std::cout << "[+] Kitap bulundu! Indeks: " << aramaSonuc.indeks
                          << " | Adim Sayisi: " << aramaSonuc.adimSayisi
                          << " | Ad: " << aramaSonuc.kitap.ad
                          << " | Yazar: " << aramaSonuc.kitap.yazar
                          << " | Sayfa: " << aramaSonuc.kitap.sayfaSayisi << "\n";
            } else {
                std::cout << "[!] ID " << arananId << " bulunamadi."
                          << " | Arama Adim Sayisi: " << aramaSonuc.adimSayisi << "\n";
            }

            delete[] siraliDizi;
            break;
        }
        case 0:
            std::cout << "Ana menuye donuluyor...\n";
            break;
        default:
            std::cout << "[!] Gecersiz secim! 0 ile 2 arasinda bir deger girin.\n";
            break;
        }
    } while (secim != 0);

    modul3KatalogTemizle(yedekKatalog);
}

#ifndef ANA_PROJE_ENTEGRE
int main() {
    modul3Menu(nullptr);
    return 0;
}
#endif
