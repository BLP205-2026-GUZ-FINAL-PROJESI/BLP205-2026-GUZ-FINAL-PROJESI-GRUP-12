#ifndef MODUL1_H
#define MODUL1_H

#include <string>

// ==========================================
// 1. CIFT YONLU DOGRUSAL BAGLI LISTE (KITAP)
// ==========================================
struct KitapNode {
    int kitapID;
    std::string kitapAdi;
    std::string yazar;
    int sayfaSayisi;
    KitapNode* next;
    KitapNode* prev;
};

bool kitapIDVarMi(KitapNode* basdugum, int id);
KitapNode* kitapBasaEkle(KitapNode* basdugum, int id, std::string ad, std::string yazar, int sayfa);
KitapNode* kitapSonaEkle(KitapNode* basdugum, int id, std::string ad, std::string yazar, int sayfa);
KitapNode* kitapArayaEkleOncesine(KitapNode* basdugum, int hedefID, int id, std::string ad, std::string yazar, int sayfa);
KitapNode* kitapSilID(KitapNode* basdugum, int id);
void kitaplariBastanSonaListele(KitapNode* basdugum);
void kitaplariSondanBasaListele(KitapNode* basdugum);
void katalogAnaliziYap(KitapNode* basdugum, int sayfaEsigi);
void kitapListesiniTemizle(KitapNode* basdugum);

// ==========================================
// 2. TEK YONLU DAIRESEL BAGLI LISTE (DUYURU)
// ==========================================
struct DuyuruNode {
    int duyuruNo;
    std::string baslik;
    DuyuruNode* next;
};

DuyuruNode* duyuruEkleDairesel(DuyuruNode* basdugum, int no, std::string baslik);
void duyuruTamTurYazdir(DuyuruNode* basdugum);

// ==========================================
// 3. DOSYA ISLEMLERI & MENU
// ==========================================
void kataloguDosyayaYaz(KitapNode* basdugum, const std::string& dosyaAdi);
void dosyadanOkuVeGoster(const std::string& dosyaAdi);
int sayiAl(const std::string& mesaj);
std::string metinAl(const std::string& mesaj);
void modul1Menu();

#endif