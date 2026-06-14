#include <iostream>
#include <string>
#include <vector>
#include "Barang.cpp"

using namespace std;

class Hashing {
private:
    int ukuranTabel;
    vector<Barang> tabel;
public:
    Hashing(int kapasitas) {
        ukuranTabel = kapasitas;
        tabel.resize(ukuranTabel);
    }

    int rumusHash(Barang &b){
        string namaBarang = b.nama;
        int hasilHasing = b.id;
        int perkalian = 1;

        for (int i = 0; i < namaBarang.size(); i++){
            int value = (int)namaBarang[i];
            hasilHasing = (hasilHasing + (value * perkalian)) % ukuranTabel;
            perkalian = (perkalian * 37) % ukuranTabel;

        }
        return hasilHasing;
    }

    void tambahBarang(Barang barangBaru) {
        int indeks = rumusHash(barangBaru);
        int indeksAwal = indeks;

        //Linear probing
        while (tabel[indeks].id != -1) {
            indeks = (indeks + 1) % ukuranTabel; 
            
            if (indeks == indeksAwal) {
                cout << "Tempat sudah penuh!\n";
                return;
            }
        }
        //Menamabahkan barang ke indeks baru
        tabel[indeks] = barangBaru;
        cout << "Berhasil menyimpan " << barangBaru.nama 
             <<  "di indeks vector: " << indeks << endl;
    }
};
