#include <iostream>
#include <string>
#include <cstdlib>
#include <print>
#include "GudangManager.cpp"

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
    GudangManager gudang(100); // Hash table dengan kapasitas 100
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
            system("pause");
            system("cls");
            break;
        }

        // Implementasi lengkap semua fitur
        switch (choice) {
            case 1: { // Tambah Barang
                int id, stok, prioritas;
                string nama, lokasiRak;

                system("cls");

                cout << "\n=== TAMBAH BARANG ==="<< endl;
                cout << "Masukkan ID Barang: ";
                cin >> id;
                cin.ignore();
                
                cout << "Masukkan Nama Barang: ";
                getline(cin, nama);
                
                cout << "Masukkan Stok: ";
                cin >> stok;
                cin.ignore();
                
                cout << "Masukkan Lokasi Rak: ";
                getline(cin, lokasiRak);
                
                cout << "Masukkan Prioritas (angka kecil = prioritas tinggi): ";
                cin >> prioritas;
                
                gudang.tambahBarang(id, nama, stok, lokasiRak, prioritas);
                break;
            }
            
            case 2: { // Cari Barang
                int id;

                system("cls");

                cout << "\n=== CARI BARANG ==="<< endl;
                cout << "Masukkan ID Barang yang dicari: ";
                cin >> id;
                gudang.cariBarang(id);
                break;
            }
            
            case 3: { // Tampilkan Semua Barang
                gudang.tampilkanSemuaBarang();
                break;
            }
            
            case 4: { // Tampilkan Barang Prioritas Tertinggi

                system("cls");

                cout << "\n=== BARANG PRIORITAS TERTINGGI ==="<< endl;
                gudang.lihatPrioritasTertinggi();
                break;
            }
            
            case 5: { // Keluarkan Barang

                system("cls");

                cout << "\n=== KELUARKAN BARANG ==="<< endl;
                gudang.keluarkanBarangPrioritas();
                break;
            }
            
            case 6: { // Tampilkan Antrian Prioritas

                system("cls");

                cout << "\n=== ANTRIAN PRIORITAS ==="<< endl;
                gudang.tampilkanAntrianPrioritas();
                break;
            }
            
            default: 
                cout << ("Pilihan tidak valid.\n"); 
                break;
        }
    }
    return 0;
}
