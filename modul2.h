#ifndef MODUL2_H
#define MODUL2_H

#include <string>

struct YiginDugum {
    std::string islemAciklamasi;
    YiginDugum* next;
};

struct KuyrukDugum {
    std::string ogrenciNo;
    std::string adSoyad;
    std::string talepEdilenKitap;
    KuyrukDugum* next;
};

struct Kuyruk {
    KuyrukDugum* front;
    KuyrukDugum* rear;
};

void yiginBaslat(YiginDugum*& top);
void yiginPush(YiginDugum*& top, const std::string& aciklama);
bool yiginPop(YiginDugum*& top, std::string& cikarilan);
void yiginPeek(const YiginDugum* top);
void yiginListele(const YiginDugum* top);
void yiginTemizle(YiginDugum*& top);

void kuyrukBaslat(Kuyruk& q);
void kuyrukEnqueue(Kuyruk& q, const std::string& ogrenciNo, const std::string& adSoyad, const std::string& kitapAdi);
bool kuyrukDequeue(Kuyruk& q, std::string& cikarilanBilgi);
void kuyrukListele(const Kuyruk& q);
void kuyrukTemizle(Kuyruk& q);

void modul2OrnekVeriYukle(YiginDugum*& top, Kuyruk& q);
void modul2Menu(YiginDugum*& top, Kuyruk& q);
void modul2Temizle(YiginDugum*& top, Kuyruk& q);

#endif
