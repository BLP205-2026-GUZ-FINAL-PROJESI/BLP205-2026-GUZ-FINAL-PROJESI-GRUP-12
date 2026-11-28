#include "modul4.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {

const int BIRIM_SAYISI = 5;

struct KampusGrafi {
    std::string birimler[BIRIM_SAYISI];
    int mesafe[BIRIM_SAYISI][BIRIM_SAYISI];
};

void yolEkle(KampusGrafi& graf, int birim1, int birim2, int metre) {
    graf.mesafe[birim1][birim2] = metre;
    graf.mesafe[birim2][birim1] = metre;
}

void matrisYazdir(const KampusGrafi& graf) {
    std::cout << "\n--- KOMSULUK MATRISI (metre) ---\n";
    std::cout << "0 dogrudan yol olmadigini gosterir.\n" << std::setw(18) << "";
    for (int i = 0; i < BIRIM_SAYISI; i++) {
        std::cout << std::setw(5) << i + 1;
    }
    std::cout << "\n";
    for (int i = 0; i < BIRIM_SAYISI; i++) {
        std::cout << i + 1 << ". " << std::setw(15) << graf.birimler[i];
        for (int j = 0; j < BIRIM_SAYISI; j++) {
            std::cout << std::setw(5) << graf.mesafe[i][j];
        }
        std::cout << "\n";
    }
}

void bfs(const KampusGrafi& graf, int baslangic) {
    bool ziyaret[BIRIM_SAYISI] = {};
    int kuyruk[BIRIM_SAYISI];
    int on = 0, son = 0;

    kuyruk[son++] = baslangic;
    ziyaret[baslangic] = true;
    std::cout << "\nBaslangic: " << graf.birimler[baslangic]
              << "\nBFS ziyaret sirasi (once en az yol gecerek ulasilan yerler):\n";
    while (on < son) {
        int birim = kuyruk[on++];
        std::cout << on << ". " << graf.birimler[birim] << "\n";
        for (int i = 0; i < BIRIM_SAYISI; i++) {
            if (graf.mesafe[birim][i] > 0 && !ziyaret[i]) {
                ziyaret[i] = true;
                kuyruk[son++] = i;
            }
        }
    }
}

void dfs(const KampusGrafi& graf, int birim, bool ziyaret[], int& sira) {
    ziyaret[birim] = true;
    std::cout << ++sira << ". " << graf.birimler[birim] << "\n";
    for (int i = 0; i < BIRIM_SAYISI; i++) {
        if (graf.mesafe[birim][i] > 0 && !ziyaret[i]) {
            dfs(graf, i, ziyaret, sira);
        }
    }
}

void dijkstra(const KampusGrafi& graf, int baslangic, int hedef) {
    const int sonsuz = std::numeric_limits<int>::max();
    int uzaklik[BIRIM_SAYISI];
    int onceki[BIRIM_SAYISI];
    bool ziyaret[BIRIM_SAYISI] = {};
    for (int i = 0; i < BIRIM_SAYISI; i++) {
        uzaklik[i] = sonsuz;
        onceki[i] = -1;
    }
    uzaklik[baslangic] = 0;

    for (int tur = 0; tur < BIRIM_SAYISI; tur++) {
        int enYakin = -1;
        int enKisa = sonsuz;
        for (int i = 0; i < BIRIM_SAYISI; i++) {
            if (!ziyaret[i] && uzaklik[i] < enKisa) {
                enYakin = i;
                enKisa = uzaklik[i];
            }
        }
        if (enYakin == -1 || enYakin == hedef) {
            break;
        }
        ziyaret[enYakin] = true;
        for (int i = 0; i < BIRIM_SAYISI; i++) {
            int yol = graf.mesafe[enYakin][i];
            if (yol > 0 && !ziyaret[i] && enKisa + yol < uzaklik[i]) {
                uzaklik[i] = enKisa + yol;
                onceki[i] = enYakin;
            }
        }
    }

    if (uzaklik[hedef] == sonsuz) {
        std::cout << "[!] Bu iki birim arasinda yol yok.\n";
        return;
    }
    // Hedeften geriye giderek rotayi bul, sonra bastan sona yazdir.
    int rota[BIRIM_SAYISI];
    int adet = 0;
    for (int i = hedef; i != -1; i = onceki[i]) {
        rota[adet++] = i;
    }
    std::cout << "En kisa rota: ";
    for (int i = adet - 1; i >= 0; i--) {
        std::cout << graf.birimler[rota[i]];
        if (i > 0) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nToplam mesafe: " << uzaklik[hedef] << " metre\n";
}

int secimAl(const std::string& mesaj, int alt, int ust) {
    int secim;
    while (true) {
        std::cout << mesaj;
        if (std::cin >> secim) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (secim >= alt && secim <= ust) {
                return secim;
            }
        } else {
            if (std::cin.eof() || std::cin.bad()) {
                return -1;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "[!] " << alt << " ile " << ust << " arasinda bir sayi girin.\n";
    }
}

void adimAdimGez(const KampusGrafi& graf, int konum) {
    while (true) {
        std::cout << "\nBulundugunuz yer: " << graf.birimler[konum] << "\n";
        std::cout << "Buradan dogrudan gidebileceginiz yerler:\n";
        int hedefler[BIRIM_SAYISI];
        int hedefSayisi = 0;
        for (int i = 0; i < BIRIM_SAYISI; i++) {
            if (graf.mesafe[konum][i] > 0) {
                hedefler[hedefSayisi] = i;
                hedefSayisi++;
                std::cout << hedefSayisi << ". " << graf.birimler[i]
                          << " (" << graf.mesafe[konum][i] << " metre)\n";
            }
        }
        std::cout << "0. Geziyi bitir\n";
        int secim = secimAl("Nereye gitmek istersiniz? ", 0, hedefSayisi);
        if (secim <= 0) {
            return;
        }
        konum = hedefler[secim - 1];
    }
}

} // namespace

void modul4Menu() {
    KampusGrafi graf = {{"Ana Kapi", "Kutuphane", "Fakulte", "Yemekhane", "Spor Salonu"}, {}};
    // Ornek kampus yollari ve metre cinsinden uzunluklari.
    yolEkle(graf, 0, 1, 120);
    yolEkle(graf, 0, 2, 300);
    yolEkle(graf, 1, 2, 80);
    yolEkle(graf, 1, 3, 200);
    yolEkle(graf, 2, 4, 150);
    yolEkle(graf, 3, 4, 90);

    while (true) {
        std::cout << "\n--- [MODUL 4: KAMPUS ROTALARI] ---\n";
        std::cout << "1. Hangi iki yer arasinda dogrudan yol var, kac metre?\n";
        std::cout << "2. Bir yer sec: komsularindan baslayip katman katman listelensin (BFS)\n";
        std::cout << "3. Bir yer sec: her adimda yeni bir komsuya gecerek yerleri listele (DFS)\n";
        std::cout << "4. Baslangic ve hedef sec: en kisa yolu ve toplam metreyi gor (Dijkstra)\n";
        std::cout << "5. Kampuste kendin gez: her durakta gidecegin bir sonraki yeri sec\n";
        std::cout << "0. Kampus rotalarindan cik\n";
        int secim = secimAl("Seciminiz: ", 0, 5);
        if (secim <= 0) {
            return;
        }
        if (secim == 1) {
            matrisYazdir(graf);
            continue;
        }

        std::cout << "\nKampusteki yerler:\n";
        for (int i = 0; i < BIRIM_SAYISI; i++) {
            std::cout << i + 1 << ". " << graf.birimler[i] << "\n";
        }
        int baslangic = secimAl("Nereden baslamak istersiniz? ", 1, BIRIM_SAYISI);
        if (baslangic == -1) {
            return;
        }
        switch (secim) {
        case 2:
            bfs(graf, baslangic - 1);
            break;
        case 3: {
            bool ziyaret[BIRIM_SAYISI] = {};
            int sira = 0;
            std::cout << "\nBaslangic: " << graf.birimler[baslangic - 1]
                      << "\nDFS ziyaret sirasi (yeni komsu kalmayinca bir onceki yere donulur):\n";
            dfs(graf, baslangic - 1, ziyaret, sira);
            break;
        }
        case 4: {
            std::cout << "Baslangic: " << graf.birimler[baslangic - 1] << "\n";
            int hedef = secimAl("Nereye gitmek istersiniz? ", 1, BIRIM_SAYISI);
            if (hedef == -1) {
                return;
            }
            dijkstra(graf, baslangic - 1, hedef - 1);
            break;
        }
        case 5:
            adimAdimGez(graf, baslangic - 1);
            break;
        }
    }
}

#ifndef ANA_PROJE_ENTEGRE
int main() {
    modul4Menu();
    return 0;
}
#endif
