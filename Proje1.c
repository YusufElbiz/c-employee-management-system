/**
* @file Proje1.c
* @description Bu dosya, çalışanlar ve birimlerin yönetimi için gerekli yapıların ve fonksiyonların içeriklerini içerir.
* @assignment 1.Proje
* @date 22 Aralik 2024
* @author Yusuf Elbiz yusuf.elbiz@stu.fsm.edu.tr
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Proje1.h"
// Birim verilerini oluştur 
Birim* birimolustur(BirimYonetici* birimYonetici, const char* birimAdi, unsigned short int birimKodu) {
    Birim* yeniBirim = (Birim*)malloc(sizeof(Birim));
    if (!yeniBirim) {
        printf("Hata bellek tahsisi başarisiz\n");
        exit(1);
    }
    // Birim adı için bellek ayır   
    yeniBirim->birimAdi = (char*)malloc(30 * sizeof(char));
    if (!yeniBirim->birimAdi) {
        printf("Hata bellek tahsisi başarisiz\n");
        free(yeniBirim);
        exit(1);
    }
    // Birim adını kopyala  
    strcpy(yeniBirim->birimAdi, birimAdi);
    yeniBirim->birimKodu = birimKodu;
    yeniBirim->birimCalisanlar = NULL;
    yeniBirim->calisanSayisi = 0;

    // BirimYonetici'yi güncelle
    birimYonetici->birimler = realloc(birimYonetici->birimler, 
        sizeof(Birim) * (birimYonetici->toplamBirimSayisi + 1));
    if (!birimYonetici->birimler) {
        printf("Hata bellek tahsisi başarisiz\n");
        exit(1);
    }
    birimYonetici->birimler[birimYonetici->toplamBirimSayisi++] = *yeniBirim;

    return yeniBirim;
}
// Calisan verilerini oluştur   
Calisan* calisanolustur(CalisanYonetici* calisanYonetici, const char* ad, const char* soyad, 
    unsigned short int birimKodu, float maas, int girisYili) {
    Calisan* yeniCalisan = (Calisan*)malloc(sizeof(Calisan));
    if (!yeniCalisan) {
        printf("Hata bellek tahsisi başarisiz\n");
        exit(1);
    }

    yeniCalisan->calisanAdi = (char*)malloc(30 * sizeof(char));
    yeniCalisan->calisanSoyadi = (char*)malloc(30 * sizeof(char));
    if (!yeniCalisan->calisanAdi || !yeniCalisan->calisanSoyadi) {
        printf("Hata bellek tahsisi başarisiz\n");
        free(yeniCalisan);
        exit(1);
    }

    strcpy(yeniCalisan->calisanAdi, ad);
    strcpy(yeniCalisan->calisanSoyadi, soyad);
    yeniCalisan->birimKodu = birimKodu;
    yeniCalisan->maas = maas;
    yeniCalisan->girisYili = girisYili;

    // CalisanYonetici'yi güncelle
    calisanYonetici->calisanlar = realloc(calisanYonetici->calisanlar, 
        sizeof(Calisan) * (calisanYonetici->toplamCalisanSayisi + 1));
    if (!calisanYonetici->calisanlar) {
        printf("Hata bellek tahsisi başarisiz\n");
        exit(1);
    }
    calisanYonetici->calisanlar[calisanYonetici->toplamCalisanSayisi++] = *yeniCalisan;

    return yeniCalisan;
}

void birimecalisanekle(BirimYonetici* birimYonetici, Birim* birim, Calisan* calisan) {
    // Calisan verilerini kopyala
    if (birim->calisanSayisi == 0) {
        birim->birimCalisanlar = malloc(sizeof(Calisan));
    } else {
        Calisan* temp = realloc(birim->birimCalisanlar, sizeof(Calisan) * (birim->calisanSayisi + 1));
        if (!temp) {
            printf("Hata bellek tahsisi başarisiz\n");
            exit(1);
        }
        birim->birimCalisanlar = temp;
    }
    
    // Calisan verilerini kopyala
    Calisan* yeniCalisan = &birim->birimCalisanlar[birim->calisanSayisi];
    yeniCalisan->calisanAdi = strdup(calisan->calisanAdi);
    yeniCalisan->calisanSoyadi = strdup(calisan->calisanSoyadi);
    yeniCalisan->birimKodu = calisan->birimKodu;
    yeniCalisan->maas = calisan->maas;
    yeniCalisan->girisYili = calisan->girisYili;

    birim->calisanSayisi++;
    
    // BirimYonetici'deki ilgili birimi güncelle
    for (int i = 0; i < birimYonetici->toplamBirimSayisi; i++) {
        if (birimYonetici->birimler[i].birimKodu == birim->birimKodu) {
            // Birimdeki çalışan sayısı 0 ise bellekte yer ayır 
            if (birimYonetici->birimler[i].calisanSayisi == 0) {
                birimYonetici->birimler[i].birimCalisanlar = malloc(sizeof(Calisan));
            } else {
                Calisan* temp = realloc(birimYonetici->birimler[i].birimCalisanlar, 
                    sizeof(Calisan) * (birim->calisanSayisi));
                if (!temp) {
                    printf("Hata bellek tahsisi başarisiz\n");
                    exit(1);
                }
                birimYonetici->birimler[i].birimCalisanlar = temp;
            }
            
            // Son eklenen çalışanı kopyala
            Calisan* lastEmployee = &birim->birimCalisanlar[birim->calisanSayisi - 1];
            Calisan* newEmployee = &birimYonetici->birimler[i].birimCalisanlar[birim->calisanSayisi - 1];
            
            newEmployee->calisanAdi = strdup(lastEmployee->calisanAdi);
            newEmployee->calisanSoyadi = strdup(lastEmployee->calisanSoyadi);
            newEmployee->birimKodu = lastEmployee->birimKodu;
            newEmployee->maas = lastEmployee->maas;
            newEmployee->girisYili = lastEmployee->girisYili;
            
            birimYonetici->birimler[i].calisanSayisi = birim->calisanSayisi;
            break;
        }
    }
}
// Calisan verilerini yazdır
void calisanYazdir(Calisan* calisan) {
    if (calisan != NULL) {
        printf("Calisan Adi: %s, Soyadi: %s, Maas: %.2f, Birim Kodu: %d, Giris Yili: %d\n", 
               calisan->calisanAdi, calisan->calisanSoyadi, calisan->maas, calisan->birimKodu, calisan->girisYili);
    } else {
        printf("Calisan geçerli değil.\n");
    }
}
// Birim verilerini yazdır
void birimYazdir(Birim* birim) {
    if (birim != NULL) {
        printf("Birim Adi: %s, Birim Kodu: %d, Calisan Sayisi: %d\n", 
               birim->birimAdi, birim->birimKodu, birim->calisanSayisi);
        
        if (birim->calisanSayisi > 0 && birim->birimCalisanlar != NULL) {
            for (int i = 0; i < birim->calisanSayisi; i++) {
                printf("    ");
                calisanYazdir(&birim->birimCalisanlar[i]);
            }
        }
    }
}

// Birimin ortalama maasını hesapla
float ortalamamaashesapla(const Birim* birim) {
    if (!birim || !birim->birimCalisanlar || birim->calisanSayisi <= 0) {
        return 0.0;
    }

    float toplamMaas = 0;
    for (int i = 0; i < birim->calisanSayisi; i++) {
        toplamMaas += birim->birimCalisanlar[i].maas;
    }
    return toplamMaas / birim->calisanSayisi;
}

// Ortalama maaşın üstünde maaş alanları yazdır
void ortalamaninUstundeMaasAlanlariListele(const Birim* birim) {
    float ortalamaMaas = ortalamamaashesapla(birim);
    printf("Birim ortalama maas: %.2f\n", ortalamaMaas);
    for (int i = 0; i < birim->calisanSayisi; i++) {
        if (birim->birimCalisanlar[i].maas > ortalamaMaas) {
            calisanYazdir(&birim->birimCalisanlar[i]);
        }
    }
}

// Birimdeki en yüksek maaş alan çalışanı yazdır
void enYuksekMaasAlanlariYazdir(const Birim* birim) {
    if (birim->calisanSayisi == 0) {
        printf("Birimde calisan yok.\n");
        return;
    }

    Calisan* enYuksekMaasCalisan = &birim->birimCalisanlar[0];
    for (int i = 1; i < birim->calisanSayisi; i++) {
        if (birim->birimCalisanlar[i].maas > enYuksekMaasCalisan->maas) {
            enYuksekMaasCalisan = &birim->birimCalisanlar[i];
        }
    }

    printf("Birim: %s, En Yuksek Maas Alan Calisan: \n", birim->birimAdi);
    calisanYazdir(enYuksekMaasCalisan);
}


// Maaş kontrolü    
void maaskontrol(CalisanYonetici* calisanYonetici, float Cmaas) {
    for (int i = 0; i < calisanYonetici->toplamCalisanSayisi; i++) {
        if (2024 - calisanYonetici->calisanlar[i].girisYili > 10 && 
            calisanYonetici->calisanlar[i].maas < Cmaas) {
            printf("%s calisaninin maasi %.2f den %.2f 'e guncellendi\n", 
                   calisanYonetici->calisanlar[i].calisanAdi, 
                   calisanYonetici->calisanlar[i].maas, 
                   Cmaas);
            calisanYonetici->calisanlar[i].maas = Cmaas;
        }
    }
}

// Dosyaları yazdır 
void dosyayazdir(const CalisanYonetici* calisanYonetici, const BirimYonetici* birimYonetici, char* calisanAdi, char* BirimlerAdi) {
    // Calisan verilerini yazdır
    FILE* Cdosya = fopen(calisanAdi, "w");
    if (Cdosya == NULL) {
        printf("Calisanlar Dosyasi acilamadi\n");
        return;
    }
 

    // Calisan verilerini yazdır
    for (int i = 0; i < calisanYonetici->toplamCalisanSayisi; i++) {
        // Birimdeki çalışanı bul
        float guncelMaas = calisanYonetici->calisanlar[i].maas;
        for (int j = 0; j < birimYonetici->toplamBirimSayisi; j++) {
            if (birimYonetici->birimler[j].birimKodu == calisanYonetici->calisanlar[i].birimKodu) {
                for (int k = 0; k < birimYonetici->birimler[j].calisanSayisi; k++) {
                    if (strcmp(birimYonetici->birimler[j].birimCalisanlar[k].calisanAdi, 
                             calisanYonetici->calisanlar[i].calisanAdi) == 0 &&
                        strcmp(birimYonetici->birimler[j].birimCalisanlar[k].calisanSoyadi, 
                             calisanYonetici->calisanlar[i].calisanSoyadi) == 0) {
                        guncelMaas = birimYonetici->birimler[j].birimCalisanlar[k].maas;
                        break;
                    }
                }
                break;
            }
        }
        
        fprintf(Cdosya, "%s,%s,%d,%.2f,%d\n", 
                calisanYonetici->calisanlar[i].calisanAdi,
                calisanYonetici->calisanlar[i].calisanSoyadi,
                calisanYonetici->calisanlar[i].birimKodu,
                guncelMaas,
                calisanYonetici->calisanlar[i].girisYili);
    }
    fclose(Cdosya);

    // Birim verilerini yazdır
    FILE* Bdosya = fopen(BirimlerAdi, "w");
    if (Bdosya == NULL) {
        printf("Birimler Dosyasi acilamadi\n");
        return;
    }
    
    for (int i = 0; i < birimYonetici->toplamBirimSayisi; i++) {
        fprintf(Bdosya, "%s,%d,%d\n",
                birimYonetici->birimler[i].birimAdi,
                birimYonetici->birimler[i].birimKodu,
                birimYonetici->birimler[i].calisanSayisi);
    }
    fclose(Bdosya);
    
    printf("Dosyalar basariyla yazildi.\n");
}


// Tüm birimleri yazdır
void tumbirimleriyazdir(const BirimYonetici* birimYonetici) {
    
    for (int i = 0; i < birimYonetici->toplamBirimSayisi; i++) {
        birimYazdir(&birimYonetici->birimler[i]);
    }
}
// Tüm çalışanları yazdır
void tumcalisanlariyazdir(const CalisanYonetici* calisanYonetici) {
    
    for (int i = 0; i < calisanYonetici->toplamCalisanSayisi; i++) {
        calisanYazdir(&calisanYonetici->calisanlar[i]);
    }
}
// Bellek temizle
void temizle(BirimYonetici* birimYonetici, CalisanYonetici* calisanYonetici) {
    
    if (birimYonetici->birimler) {
        for (int i = 0; i < birimYonetici->toplamBirimSayisi; i++) {
            free(birimYonetici->birimler[i].birimAdi);
            if (birimYonetici->birimler[i].birimCalisanlar) {
                for (int j = 0; j < birimYonetici->birimler[i].calisanSayisi; j++) {
                    free(birimYonetici->birimler[i].birimCalisanlar[j].calisanAdi);
                    free(birimYonetici->birimler[i].birimCalisanlar[j].calisanSoyadi);
                }
                free(birimYonetici->birimler[i].birimCalisanlar);
            }
        }
        free(birimYonetici->birimler);
    }

    // Calisan verilerini temizle
    if (calisanYonetici->calisanlar) {
        for (int i = 0; i < calisanYonetici->toplamCalisanSayisi; i++) {
            free(calisanYonetici->calisanlar[i].calisanAdi);
            free(calisanYonetici->calisanlar[i].calisanSoyadi);
        }
        free(calisanYonetici->calisanlar);
    }
}
// Birim listesini göster
void birimlistesigoster(Birim* birimler[], int boyut) {
    printf("\n=== Birim Listesi Detaylari ===\n");
    if (birimler == NULL || boyut <= 0) {
        printf("Birim listesi bos veya gecersiz!\n");
        return;
    }
    
    for (int i = 0; i < boyut; i++) {
        if (birimler[i] != NULL) {
            birimYazdir(birimler[i]);
        }
    }
}
// Dosyadan oku
void dosyadanOku(BirimYonetici* birimYonetici, CalisanYonetici* calisanYonetici, const char* calisanlarDosyasi, const char* birimlerDosyasi) {
    // Birimleri oku
    FILE* birimDosya = fopen(birimlerDosyasi, "r");
    if (birimDosya == NULL) {
        printf("Birimler dosyasi acilamadi!\n");
        return;
    }

    char satir[256];
    char birimAdi[30];
    unsigned short int birimKodu;
    int calisanSayisi;

    // Birimleri oku ve oluştur
    while (fgets(satir, sizeof(satir), birimDosya)) {
        if (sscanf(satir, "%[^,],%hu,%d", birimAdi, &birimKodu, &calisanSayisi) == 3) {
            birimolustur(birimYonetici, birimAdi, birimKodu);
        }
    }
    fclose(birimDosya);

    // Çalışanları oku
    FILE* calisanDosya = fopen(calisanlarDosyasi, "r");
    if (calisanDosya == NULL) {
        printf("Calisanlar dosyasi acilamadi!\n");
        return;
    }

    char ad[30], soyad[30];
    float maas;
    int girisYili;
    Calisan* yeniCalisan;
    Birim* ilgiliBirim;

    // Çalışanları oku ve oluştur
    while (fgets(satir, sizeof(satir), calisanDosya)) {
        if (sscanf(satir, "%[^,],%[^,],%hu,%f,%d", ad, soyad, &birimKodu, &maas, &girisYili) == 5) {
            // Önce çalışanı oluştur
            yeniCalisan = calisanolustur(calisanYonetici, ad, soyad, birimKodu, maas, girisYili);
            
            // İlgili birimi bul
            ilgiliBirim = NULL;
            for (int i = 0; i < birimYonetici->toplamBirimSayisi; i++) {
                if (birimYonetici->birimler[i].birimKodu == birimKodu) {
                    ilgiliBirim = &birimYonetici->birimler[i];
                    break;
                }
            }
            
            // Çalışanı birime ekle
            if (ilgiliBirim != NULL) {
                birimecalisanekle(birimYonetici, ilgiliBirim, yeniCalisan);
            }
        }
    }
    fclose(calisanDosya);
    
    printf("Dosyalardan okuma islemi tamamlandi.\n");
}
