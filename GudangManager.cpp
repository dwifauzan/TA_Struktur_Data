#pragma once
#include "Hashing.cpp"
#include "Mheap.cpp"
#include "Barang.cpp"

using namespace std;

// Class untuk mengintegrasikan Hash Table dan Min Heap
class GudangManager {
private:
    Hashing* hashTable;
    Mheap* minHeap;

public:
    GudangManager(int kapasitas) {
        hashTable = new Hashing(kapasitas);
        minHeap = new Mheap();
    }

    ~GudangManager() {
        delete hashTable;
        delete minHeap;
    }

    // Menambah barang ke Hash Table dan Min Heap
    void tambahBarang(int id, string nama, int stok, string lokasiRak, int prioritas) {
        Barang barangBaru(id, nama, stok, lokasiRak, prioritas);
        hashTable->tambahBarang(barangBaru);
        minHeap->tambah_prioritas(barangBaru);
    }

    // Mencari barang berdasarkan ID menggunakan Hash Table
    void cariBarang(int id) {
        Barang* hasil = hashTable->cariBarang(id);
        if (hasil != nullptr) {
            cout << "\n=== BARANG DITEMUKAN ===" << endl;
            cout << "ID         : " << hasil->id << endl;
            cout << "Nama       : " << hasil->nama << endl;
            cout << "Stok       : " << hasil->stok << endl;
            cout << "Lokasi Rak : " << hasil->lokasiRak << endl;
            cout << "Prioritas  : " << hasil->prioritas << endl;
        } else {
            cout << "Barang dengan ID " << id << " tidak ditemukan." << endl;
        }
    }

    // Menampilkan semua barang dari Hash Table
    void tampilkanSemuaBarang() {
        hashTable->tampilkanSemuaBarang();
    }

    // Menampilkan dan mengeluarkan barang dengan prioritas tertinggi
    void keluarkanBarangPrioritas() {
        minHeap->ambil_prioritas();
    }

    // Menampilkan semua barang di antrian prioritas
    void tampilkanAntrianPrioritas() {
        minHeap->tampilkan_semua();
    }

    // Menampilkan barang dengan prioritas tertinggi tanpa mengeluarkannya
    void lihatPrioritasTertinggi() {
        minHeap->tampilkan_semua();
    }
};
