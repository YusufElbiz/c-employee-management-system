/**
* @file Proje1.h
* @description Bu dosya, çalışanlar ve birimlerin yönetimi için gerekli yapıların ve fonksiyonların tanımlarını içerir.
* @assignment 1.Proje
* @date 22 Aralik 2024
* @author Yusuf Elbiz yusuf.elbiz@stu.fsm.edu.tr
*/
#ifndef PROJE1_H
#define PROJE1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Birim structure
typedef struct Birim {
    char* birimAdi;            
    unsigned short int birimKodu;  
    struct Calisan* birimCalisanlar;  
    int calisanSayisi;         
} Birim;

// Calisan structure
typedef struct Calisan {
    char* calisanAdi;          
    char* calisanSoyadi;       
    unsigned short int birimKodu;  
    float maas;                
    int girisYili;             
} Calisan;

// BirimYonetici structure
typedef struct {
    Birim* birimler;
    int toplamBirimSayisi;
} BirimYonetici;

// CalisanYonetici structure
typedef struct {
    Calisan* calisanlar;
    int toplamCalisanSayisi;
} CalisanYonetici;


Birim* birimolustur(BirimYonetici* birimYonetici, const char* birimAdi, unsigned short int birimKodu);
Calisan* calisanolustur(CalisanYonetici* calisanYonetici, const char* ad, const char* soyad, unsigned short int birimKodu, float maas, int girisYili);
void birimecalisanekle(BirimYonetici* birimYonetici, Birim* birim, Calisan* calisan);
void tumbirimleriyazdir(const BirimYonetici* birimYonetici);
void tumcalisanlariyazdir(const CalisanYonetici* calisanYonetici);
void maaskontrol(CalisanYonetici* calisanYonetici, float Cmaas);
void dosyayazdir(const CalisanYonetici* calisanYonetici, const BirimYonetici* birimYonetici, char* calisanAdi, char* BirimlerAdi);
void temizle(BirimYonetici* birimYonetici, CalisanYonetici* calisanYonetici);
float ortalamamaashesapla(const Birim* birim);
void ortalamaninUstundeMaasAlanlariListele(const Birim* birim);
void enYuksekMaasAlanlariYazdir(const Birim* birim);
void dosyadanOku(BirimYonetici* birimYonetici, CalisanYonetici* calisanYonetici, const char* calisanlarDosyasi, const char* birimlerDosyasi);

#endif // PROJE1_H
