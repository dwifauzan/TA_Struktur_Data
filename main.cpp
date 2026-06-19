#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <print>
#include "Mheap.cpp"
#include "Barang.cpp" // Menginclude file cpp secara langsung sesuai permintaan 2 file sederhana

using namespace std;

// Fungsi untuk menampilkan menu utama sistem
void showMenu() {
    cout << ("\n=== SISTEM MANAJEMEN GUDANG (C++26) ===\n");
    cout << ("1. Tambah Barang\n");
    cout << ("2. Cari Barang\n");
    cout << ("3. Tampilkan Semua Barang\n");
    cout << ("4. Tampilkan Barang Prioritas Tertinggi\n");
    cout << ("5. Keluarkan Barang\n");
    cout << ("6. Tampilkan Antrian Prioritas\n");
    cout << ("7. Keluar\n");
    cout << ("Pilih menu: ");
}

int main() {
    Mheap antrianGudang;

    vector<Barang> daftarBarang;

    int choice;
    while (true) {
        showMenu();
        
        // Input validasi sederhana untuk menu
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << ("Input harus angka.\n");
            continue;
        }
        
        if (choice == 7) {
            cout << ("Keluar dari program.\n");
            break;
        }

        // Logika menu (Fitur akan diimplementasikan pada req selanjutnya)
        switch (choice) {
            case 1: {
                int id, stok, prioritas;
                string nama, lokasiRak;

                cout << "ID Barang : "; cin >> id;
                cout << "Nama Barang : "; cin >> nama;
                cout << "Stok Barang : "; cin >> stok;
                cout << "Masukkan Lokasi Rak : "; cin >> lokasiRak;
                cout << "Skala Prioritas (Angka) : "; cin >> prioritas;

                Barang barangBaru(id, nama, stok, lokasiRak, prioritas);
                daftarBarang.push_back(barangBaru);

                cout << "Barang berhasil ditambahkan";
                break;
            }
            case 2: {
                
            break;}
            case 3: {
                antrianGudang.tampilkan_semua();
                break;
            }
            case 4: cout << ("Fitur Tampilkan Barang Prioritas Tertinggi (Coming Soon)\n"); break;
            case 5: cout << ("Fitur Keluarkan Barang (Coming Soon)\n"); break;
            case 6: cout << ("Fitur Tampilkan Antrian Prioritas (Coming Soon)\n"); break;
            default: cout << ("Pilihan tidak valid.\n"); break;
        }
    }
    return 0;
}
