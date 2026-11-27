#ifndef MODUL3_H
#define MODUL3_H

#include <string>

#ifndef MODUL1_KITAP_TANIMLI
#define MODUL1_KITAP_TANIMLI

struct Kitap {
    int id;
    std::string ad;
    std::string yazar;
    int sayfaSayisi;
};

struct KitapDugum {
    Kitap veri;
    KitapDugum* prev;
    KitapDugum* next;
};

struct KitapKatalog {
    KitapDugum* head;
    KitapDugum* tail;
};

#endif

struct BubbleSonuc {
    long long karsilastirmaSayisi;
    long long takasSayisi;
};

struct InsertionSonuc {
    long long karsilastirmaSayisi;
    long long kaydirmaSayisi;
};

struct QuickSonuc {
    long long karsilastirmaSayisi;
    long long takasSayisi;
};

struct BinaryAramaSonuc {
    bool bulundu;
    int indeks;
    int adimSayisi;
    Kitap kitap;
};

Kitap* modul3KatalogDiziyeAktar(const KitapKatalog& katalog, int& boyut);
Kitap* modul3DiziKopyala(const Kitap* kaynak, int boyut);
void modul3DiziYazdir(const Kitap* dizi, int boyut, const std::string& baslik);

BubbleSonuc modul3BubbleSortSayfa(Kitap* dizi, int boyut);
InsertionSonuc modul3InsertionSortSayfa(Kitap* dizi, int boyut);
QuickSonuc modul3QuickSortId(Kitap* dizi, int boyut);
BinaryAramaSonuc modul3BinarySearchId(const Kitap* siraliDizi, int boyut, int arananId);

void modul3OrnekKatalogYukle(KitapKatalog& katalog);
void modul3KatalogTemizle(KitapKatalog& katalog);
void modul3Menu(const KitapKatalog* disKatalog = nullptr);

#endif
