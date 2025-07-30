/**
* @file main.c
* @description Bu dosya, çalışanlar ve birimlerin yönetimi için gerekli yapıların ve fonksiyonların test edilmesi için oluşturulan bir main dosyasidir.
* @assignment 1.Proje
* @date 22 Aralik 2024
* @author Yusuf Elbiz yusuf.elbiz@stu.fsm.edu.tr
*/
#include <stdio.h>
#include <stdlib.h>
#include "Proje1.h"

int main(int argc, char *argv[]) {
    
    BirimYonetici birimYonetici = {NULL, 0};
    CalisanYonetici calisanYonetici = {NULL, 0};
 Birim *birim0 = birimolustur(&birimYonetici,"KARMA", 1450);
     Birim *birim1 = birimolustur(&birimYonetici,"IT", 432);
    
    
   
    
     Calisan *Calisan0 = calisanolustur(&calisanYonetici,"Ali", "Yilmaz", 1450, 15000.00, 2000);
     birimecalisanekle(&birimYonetici, birim0, Calisan0);
     Calisan *Calisan1 = calisanolustur(&calisanYonetici,"Ayse", "Demir", 432, 18000.00, 2018);
     birimecalisanekle(&birimYonetici, birim1, Calisan1);
     Calisan *Calisan2 = calisanolustur(&calisanYonetici,"Mehmet", "Kaya", 432, 16500.00, 2020);
     birimecalisanekle(&birimYonetici, birim1, Calisan2);
     Calisan *Calisan3 = calisanolustur(&calisanYonetici,"Zeynep", "Celik", 432, 14000.00, 2019);
     birimecalisanekle(&birimYonetici, birim1, Calisan3);
     Calisan *Calisan4 = calisanolustur(&calisanYonetici,"Fatma", "Ozturk", 1450, 13500.00, 2021);
     birimecalisanekle(&birimYonetici, birim0, Calisan4);
     Calisan *Calisan5 = calisanolustur(&calisanYonetici,"Can", "Arslan", 1450, 12000.00, 2022);
     birimecalisanekle(&birimYonetici, birim0, Calisan5);
    // Argüman kontrolü
    if (argc != 3) {
        printf("Kullanim: %s <calisanlar_dosyasi> <birimler_dosyasi>\n", argv[0]);
        return 1;
    }
    

    // Dosyadan okuma

    printf("\n=== Dosyadan Veriler Okunuyor ===\n");
    dosyadanOku(&birimYonetici, &calisanYonetici, argv[1], argv[2]);

    // Birimleri yazdır
    printf("\n=== Birimler ===\n");
    tumbirimleriyazdir(&birimYonetici);

    // Çalışanları yazdır
    printf("\n=== Tum Calisanlar ===\n");
    tumcalisanlariyazdir(&calisanYonetici);

    // Birimlerin ortalama maaslarını yazdır
    printf("\n=== Birim Ortalama Maaslari ===\n");
    for (int i = 0; i < birimYonetici.toplamBirimSayisi; i++) {
        printf("%s ortalama maas: %.2f\n", 
               birimYonetici.birimler[i].birimAdi,
               ortalamamaashesapla(&birimYonetici.birimler[i]));
    }

    // Ortalama üstü maaş alanları yazdır
    printf("\n=== Ortalama Ustu Maas Alanlar ===\n");
    for (int i = 0; i < birimYonetici.toplamBirimSayisi; i++) {
        printf("\n%s Birimi:\n", birimYonetici.birimler[i].birimAdi);
        ortalamaninUstundeMaasAlanlariListele(&birimYonetici.birimler[i]);
    }

    // En yuksek maas alanları yazdır
    printf("\n=== En Yuksek Maas Alanlar ===\n");
    for (int i = 0; i < birimYonetici.toplamBirimSayisi; i++) {
        enYuksekMaasAlanlariYazdir(&birimYonetici.birimler[i]);
    }

    // Maaş kontrolü ve güncelleme 10 yıldan fazla çalışanlar için
    printf("\n=== Maas Kontrol ve Guncelleme (>10 yil) ===\n");
    maaskontrol(&calisanYonetici, 16000.0);

    // Dosyaya yazdır
    printf("\n=== Dosyaya Yaziliyor ===\n");
    dosyayazdir(&calisanYonetici, &birimYonetici, argv[1], argv[2]);
    //Belleği temizle
    printf("\nProgram basariyla tamamlandi.\n");
    temizle(&birimYonetici, &calisanYonetici);
    return 0;
}
