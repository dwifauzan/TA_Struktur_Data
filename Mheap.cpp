#pragma once
#include <iostream>
#include <vector> 
#include "Barang.cpp"  
using namespace std;

class Mheap {
    private: 
        vector<Barang> heap;

        int bapak (int i) {
            return i/2;
        }

        int anak_kiri(int i) {
            return 2 * i;
        }

        int anak_kanan(int i) {
            return 2 * i + 1;
        }

        void ke_atas (int p) {
            while (p > 1 && heap[p].prioritas < heap[bapak(p)].prioritas){
                swap(heap[p], heap[bapak(p)]);
                p = bapak(p);
            }
        }

        void ke_bawah (int p) {
            int terkecil = p;
            int kiri = anak_kiri(p);
            int kanan = anak_kanan(p);

            if (kiri < heap.size() && heap[kiri].prioritas < heap[terkecil].prioritas) {
                terkecil = kiri;
            }

            if (kanan < heap.size() && heap[kanan].prioritas < heap[terkecil].prioritas){
                terkecil = kanan;
            }

            if (terkecil != p) {
                swap(heap[p], heap[terkecil]);
                ke_bawah(terkecil);
            }
        }
    public :
        Mheap() {
            heap.push_back(Barang()); 
        }    

        void tambah_prioritas (Barang b) {
            heap.push_back(b);
            ke_atas (heap.size() - 1 );
            cout << b.nama << "telah masuk" << endl;
        } 

        void ambil_prioritas (){
            if (heap.size() <= 1){
                cout << "heap kosong" << endl;
                return;
            }

            Barang depan = heap[1];

            cout << "barang yang digunakan : " << depan.nama << "(prioritas : " << depan.prioritas << ")" << endl;
            heap[1] = heap.back();
            heap.pop_back();

            if (heap.size() > 1) {
                ke_bawah(1);
            }
        }

        void tampilkan_semua() {
            if (heap.size() <= 1) {
                cout << "heap sedang kosong coba lagi nanti" << endl; 
                return;
            }

            cout << "semua barang : " << endl;

            for (int i = 1; i < heap.size(); i++){
                cout << "id         : " << heap[i].id << endl; 
                cout << "nama       : " << heap[i].nama << endl; 
                cout << "stok       : " << heap[i].stok << endl; 
                cout << "lokasi rak : " << heap[i].lokasiRak << endl; 
                cout << "prioritas  : " << heap[i].prioritas << endl;
                cout << "-------------------------------------------";
            }
        }
    
};
