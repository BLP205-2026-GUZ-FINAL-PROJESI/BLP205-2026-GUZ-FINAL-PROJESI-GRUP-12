#include "modul2.h"
#include <iomanip>
#include <iostream>
#include <limits>

namespace {

int sayiAl(const std::string& mesaj) {
    int secim;
    while (true) {
        std::cout << mesaj;
        if (std::cin >> secim) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return secim;
        }
        std::cout << "[!] Gecersiz giris, lutfen sayi girin.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string metinAl(const std::string& mesaj) {
    std::string satir;
    while (true) {
        std::cout << mesaj;
        std::getline(std::cin, satir);
        if (!satir.empty()) {
            return satir;
        }
        std::cout << "[!] Bu alan bos birakilamaz.\n";
    }
}

} // namespace

void yiginBaslat(YiginDugum*& top) {
    top = nullptr;
}

void yiginPush(YiginDugum*& top, const std::string& aciklama) {
    YiginDugum* yeni = new YiginDugum{aciklama, top};
    top = yeni;
}

bool yiginPop(YiginDugum*& top, std::string& cikarilan) {
    if (top == nullptr) {
        std::cout << "[UYARI] Islem gecmisi yigini bos! Geri alinacak islem yok.\n";
        return false;
    }
    YiginDugum* silinecek = top;
    cikarilan = silinecek->islemAciklamasi;
    top = top->next;
    delete silinecek;
    return true;
}

void yiginPeek(const YiginDugum* top) {
    if (top == nullptr) {
        std::cout << "[BILGI] Islem gecmisi yigini su anda bos.\n";
        return;
    }
    std::cout << "[PEEK / TOP] En son yapilan islem: " << top->islemAciklamasi << "\n";
}

void yiginListele(const YiginDugum* top) {
    if (top == nullptr) {
        std::cout << "[BILGI] Islem gecmisi yigini su anda bos.\n";
        return;
    }
    std::cout << "\n--- ISLEM GECMISI YIGINI (STACK - LIFO) ---\n";
    const YiginDugum* curr = top;
    int sira = 1;
    while (curr != nullptr) {
        std::cout << "  " << sira++ << ". " << curr->islemAciklamasi << "\n";
        curr = curr->next;
    }
}

void yiginTemizle(YiginDugum*& top) {
    while (top != nullptr) {
        YiginDugum* silinecek = top;
        top = top->next;
        delete silinecek;
    }
}

void kuyrukBaslat(Kuyruk& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

void kuyrukEnqueue(Kuyruk& q, const std::string& ogrenciNo, const std::string& adSoyad, const std::string& kitapAdi) {
    KuyrukDugum* yeni = new KuyrukDugum{ogrenciNo, adSoyad, kitapAdi, nullptr};
    if (q.rear == nullptr) {
        q.front = yeni;
        q.rear = yeni;
    } else {
        q.rear->next = yeni;
        q.rear = yeni;
    }
}

bool kuyrukDequeue(Kuyruk& q, std::string& cikarilanBilgi) {
    if (q.front == nullptr) {
        std::cout << "[UYARI] Bekleyen ogrenci kuyrugu bos! Hizmet verilecek ogrenci yok.\n";
        return false;
    }
    KuyrukDugum* silinecek = q.front;
    cikarilanBilgi = silinecek->ogrenciNo + " - " + silinecek->adSoyad +
                     " (Talep: " + silinecek->talepEdilenKitap + ")";
    q.front = q.front->next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete silinecek;
    return true;
}

void kuyrukListele(const Kuyruk& q) {
    if (q.front == nullptr) {
        std::cout << "[BILGI] Odunc kitap bekleme kuyrugu su anda bos.\n";
        return;
    }
    std::cout << "\n--- BEKLEYEN OGRENCI KUYRUGU (QUEUE - FIFO) ---\n";
    std::cout << " " << std::left << std::setw(6) << "Sira"
              << std::setw(15) << "Ogrenci No"
              << std::setw(24) << "Ad Soyad"
              << std::setw(30) << "Talep Edilen Kitap" << "\n";
    std::cout << "-------------------------------------------------------------------------------\n";
    const KuyrukDugum* curr = q.front;
    int sira = 1;
    while (curr != nullptr) {
        std::cout << " " << std::left << std::setw(6) << sira++
                  << std::setw(15) << curr->ogrenciNo
                  << std::setw(24) << curr->adSoyad
                  << std::setw(30) << curr->talepEdilenKitap << "\n";
        curr = curr->next;
    }
}

void kuyrukTemizle(Kuyruk& q) {
    while (q.front != nullptr) {
        KuyrukDugum* silinecek = q.front;
        q.front = q.front->next;
        delete silinecek;
    }
    q.rear = nullptr;
}

void modul2OrnekVeriYukle(YiginDugum*& top, Kuyruk& q) {
    yiginPush(top, "Modul 2 yigin ve kuyruk yapisi baslatildi");
    yiginPush(top, "2401001 nolu ogrenci odunc sirasina alindi");

    kuyrukEnqueue(q, "2401001", "Ahmet Yilmaz", "Veri Yapilari ve Algoritmalar");
    kuyrukEnqueue(q, "2401002", "Elif Kaya", "Isletim Sistemleri");
    kuyrukEnqueue(q, "2401003", "Mert Demir", "Bilgisayar Aglari");
}

void modul2Menu(YiginDugum*& top, Kuyruk& q) {
    int secim;
    do {
        std::cout << "\n--- [MODUL 2: YIGIN (STACK) & KUYRUK (QUEUE)] ---\n";
        std::cout << "1. Odunc Sirasina Ogrenci Ekle (Queue Enqueue)\n";
        std::cout << "2. Siradaki Ogrenciye Kitap Ver ve Cikar (Queue Dequeue)\n";
        std::cout << "3. Bekleyen Ogrenci Kuyrugunu Listele (FIFO)\n";
        std::cout << "4. Islem Gecmisi Yiginini Goruntule (Stack LIFO)\n";
        std::cout << "5. En Son Yapilan Islemi Gor (Stack Peek/Top)\n";
        std::cout << "6. Son Islemi Geri Al / Yigindan Cikar (Stack Pop/Undo)\n";
        std::cout << "0. Geri / Ana Menuye Don\n";

        secim = sayiAl("Seciminiz: ");

        switch (secim) {
        case 1: {
            std::string ogrNo = metinAl("Ogrenci No: ");
            std::string adSoyad = metinAl("Ad Soyad: ");
            std::string kitapAdi = metinAl("Talep Edilen Kitap: ");
            kuyrukEnqueue(q, ogrNo, adSoyad, kitapAdi);
            yiginPush(top, "Kuyruga eklendi: " + ogrNo + " - " + kitapAdi);
            std::cout << "[OK] Ogrenci bekleme kuyruguna eklendi.\n";
            break;
        }
        case 2: {
            std::string cikan;
            if (kuyrukDequeue(q, cikan)) {
                std::cout << "[OK] Hizmet verildi ve kuyruktan cikarildi: " << cikan << "\n";
                yiginPush(top, "Odunc verildi: " + cikan);
            }
            break;
        }
        case 3:
            kuyrukListele(q);
            break;
        case 4:
            yiginListele(top);
            break;
        case 5:
            yiginPeek(top);
            break;
        case 6: {
            std::string geriAlinan;
            if (yiginPop(top, geriAlinan)) {
                std::cout << "[OK] Yigindan cikarilan islem: " << geriAlinan << "\n";
            }
            break;
        }
        case 0:
            std::cout << "Menuden cikiliyor...\n";
            break;
        default:
            std::cout << "[!] Gecersiz secim! 0-6 arasinda bir deger girin.\n";
            break;
        }
    } while (secim != 0);
}

void modul2Temizle(YiginDugum*& top, Kuyruk& q) {
    yiginTemizle(top);
    kuyrukTemizle(q);
}

#ifndef ANA_PROJE_ENTEGRE
int main() {
    YiginDugum* top = nullptr;
    Kuyruk kuyruk;

    yiginBaslat(top);
    kuyrukBaslat(kuyruk);
    modul2OrnekVeriYukle(top, kuyruk);

    modul2Menu(top, kuyruk);

    modul2Temizle(top, kuyruk);
    return 0;
}
#endif
