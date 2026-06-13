#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

const string NAMA_FILE = "inventori.csv";

// ─── Struct Barang ────────────────────────────────────────────────────────────
struct Barang {
    string nama;
    double hargaStokAwal;
    double hargaStokAkhir;
    double hpp;
    double hargaJual;
    double itr;
};

bool sudahDiSort = false;

// ─── Hitung ITR ───────────────────────────────────────────────────────────────
double hitungITR(double stokAwal, double stokAkhir, double hpp) {
    double rata = (stokAwal + stokAkhir) / 2.0;
    if (rata == 0) return 0;
    return hpp / rata;
}

// ─── Quick Sort ───────────────────────────────────────────────────────────────
int partition(vector<Barang>& v, int low, int high) {
    double pivot = v[high].itr;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (v[j].itr <= pivot) { i++; swap(v[i], v[j]); }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}
void quickSort(vector<Barang>& v, int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

// ─── Binary Search ────────────────────────────────────────────────────────────
int binarySearchBatas(const vector<Barang>& v, double threshold) {
    int low = 0, high = (int)v.size() - 1, hasil = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (v[mid].itr <= threshold) { hasil = mid; low = mid + 1; }
        else high = mid - 1;
    }
    return hasil;
}

// ─── Simpan CSV ───────────────────────────────────────────────────────────────
void simpanCSV(const vector<Barang>& daftarBarang) {
    ofstream file(NAMA_FILE);
    if (!file.is_open()) {
        cout << "  [!] Gagal menyimpan ke " << NAMA_FILE << "\n";
        return;
    }
    file << "No,Nama Barang,Harga Stok Awal,Harga Stok Akhir,HPP,Harga Jual,ITR\n";
    for (int i = 0; i < (int)daftarBarang.size(); i++) {
        file << (i + 1) << ","
             << "\"" << daftarBarang[i].nama << "\","
             << fixed << setprecision(2) << daftarBarang[i].hargaStokAwal << ","
             << daftarBarang[i].hargaStokAkhir << ","
             << daftarBarang[i].hpp << ","
             << daftarBarang[i].hargaJual << ","
             << setprecision(4) << daftarBarang[i].itr << "\n";
    }
    file.close();
}

// ─── Muat CSV ─────────────────────────────────────────────────────────────────
void muatCSV(vector<Barang>& daftarBarang) {
    ifstream file(NAMA_FILE);
    if (!file.is_open()) return;

    string baris;
    getline(file, baris); // lewati header

    int jumlah = 0;
    while (getline(file, baris)) {
        if (baris.empty()) continue;
        Barang b;
        istringstream ss(baris);
        string token;

        getline(ss, token, ','); // No (skip)

        getline(ss, token, ',');
        if (!token.empty() && token[0] == '"') {
            while (token.size() < 2 || token.back() != '"') {
                string lanjut;
                if (!getline(ss, lanjut, ',')) break;
                token += "," + lanjut;
            }
            b.nama = token.substr(1, token.size() - 2);
        } else {
            b.nama = token;
        }

        getline(ss, token, ','); b.hargaStokAwal  = stod(token);
        getline(ss, token, ','); b.hargaStokAkhir = stod(token);
        getline(ss, token, ','); b.hpp            = stod(token);
        getline(ss, token, ','); b.hargaJual      = stod(token);
        getline(ss, token);     b.itr             = stod(token);

        daftarBarang.push_back(b);
        jumlah++;
    }
    file.close();
    if (jumlah > 0)
        cout << "  [INFO] " << jumlah << " barang dimuat dari " << NAMA_FILE << "\n";
}

// ─── Tampilkan Semua Barang ───────────────────────────────────────────────────
void tampilkanBarang(const vector<Barang>& v) {
    cout << "\n========================================\n";
    cout <<   "           DAFTAR BARANG                \n";
    cout <<   "========================================\n";
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Barang"
         << setw(15) << "Stok Awal"
         << setw(15) << "Stok Akhir"
         << setw(15) << "HPP"
         << setw(15) << "Harga Jual"
         << setw(10) << "ITR"
         << "\n";
    cout << string(95, '-') << "\n";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << left
             << setw(5)  << (i+1)
             << setw(20) << v[i].nama
             << setw(15) << fixed << setprecision(2) << v[i].hargaStokAwal
             << setw(15) << v[i].hargaStokAkhir
             << setw(15) << v[i].hpp
             << setw(15) << v[i].hargaJual
             << setw(10) << setprecision(4) << v[i].itr
             << "\n";
    }
    cout << string(95, '-') << "\n";
}

// ─── Input Barang ─────────────────────────────────────────────────────────────
void inputBarang(vector<Barang>& daftarBarang) {
    Barang b;

    cout << "\n---------------------------------\n";
    cout <<   "       INPUT BARANG BARU         \n";
    cout <<   "---------------------------------\n";

    string input;

    cout << "  Nama barang        : "; cin.ignore(); getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.nama)) {
        cout << " [!] Input harus berupa angka. Harga stok awal: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }
    cout << "  Harga stok awal    : "; getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaStokAwal)) {
        cout << " [!] Input harus berupa angka. Harga stok awal: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    cout << "  Harga stok akhir   : "; getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaStokAkhir)) {
        cout << " [!] Input harus berupa angka. Harga stok akhir: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }
    
    cout << "  HPP (Harga Pokok)  : "; getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hpp)) {
        cout << " [!] Input harus berupa angka. HPP: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    cout << "  Harga jual         : "; getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaJual)) {
        cout << " [!] Input harus berupa angka. Harga jual: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }
    
    b.itr = hitungITR(b.hargaStokAwal, b.hargaStokAkhir, b.hpp);
    daftarBarang.push_back(b);
    sudahDiSort = false;
    
    simpanCSV(daftarBarang);
    
    system("cls");
    cout << "\n  [OK] Barang \"" << b.nama << "\" berhasil ditambahkan!\n";
    cout << "  [OK] ITR           : " << fixed << setprecision(4) << b.itr << "\n";
    cout << "       ITR = HPP / rata-rata stok\n";
    cout << "           = " << b.hpp << " / "
         << (b.hargaStokAwal + b.hargaStokAkhir) / 2.0
         << " = " << b.itr << "\n";
    cout << "  [OK] Data tersimpan ke " << NAMA_FILE << "\n";
}

// ─── Hapus Barang ─────────────────────────────────────────────────────────────
void hapusBarang(vector<Barang>& daftarBarang) {
    if (daftarBarang.empty()) {
        cout << "\n  [!] Belum ada barang yang diinput!\n";
        return;
    }

    tampilkanBarang(daftarBarang);

    cout << "  Masukkan nomor barang yang ingin dihapus (0 untuk batal): ";
    int nomor;
    cin >> nomor;
    // Cek apakah input merupakan selain angka
    if (cin.fail()) {
        cout << " [!] Input harus berupa angka! Silakan coba lagi.\n";
        
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        
        return hapusBarang(daftarBarang);
    }

    if (nomor == 0) {
        cout << "  [INFO] Penghapusan dibatalkan.\n";
        return;
    }
    if (nomor < 1 || nomor > (int)daftarBarang.size()) {
        cout << "  [!] Nomor tidak valid!\n";
        return hapusBarang(daftarBarang);
    }
    

    string namaHapus = daftarBarang[nomor - 1].nama;
    daftarBarang.erase(daftarBarang.begin() + (nomor - 1));
    sudahDiSort = false;

    simpanCSV(daftarBarang);

    system("cls");
    cout << "  [OK] Barang \"" << namaHapus << "\" berhasil dihapus!\n";
    cout << "  [OK] Data tersimpan ke " << NAMA_FILE << "\n";
}

// ─── Tampilkan kategori dan terapkan diskon ─────────────────────────────────────
void tampilkanDiskon(vector<Barang>& v, int dari, int sampai, double persen) {
    cout << "  " << left << setw(5) << "No" << setw(20) << "Nama Barang"
         << setw(12) << "ITR" << setw(18) << "Harga Asal"
         << setw(10) << "Diskon" << setw(20) << "Harga Setelah Diskon" << "\n";
    cout << "  " << string(85, '-') << "\n";
    int no = 1;
    for (int i = dari; i <= sampai; i++, no++) {
        double asal = v[i].hargaJual;
        double baru = asal * (1.0 - persen / 100.0);
        v[i].hargaJual = baru;
        cout << "  " << left << setw(5) << no << setw(20) << v[i].nama
             << setw(12) << fixed << setprecision(4) << v[i].itr
             << setw(18) << setprecision(2) << asal
             << setw(10) << (to_string((int)persen) + "%")
             << setw(20) << baru << "\n";
    }
}

// ─── Analisis Batas ITR ───────────────────────────────────────────────────────
void analisisBatas(vector<Barang>& daftarBarang) {
    if (daftarBarang.empty()) {
        cout << "\n  [!] Belum ada barang. Pilih 'a' dulu.\n"; return;
    }
    if (!sudahDiSort) {
        quickSort(daftarBarang, 0, (int)daftarBarang.size() - 1);
        sudahDiSort = true;
        cout << "\n  [INFO] Data diurutkan otomatis.\n";
    }

    double batasKuning, batasMerah;
    cout << "\n---------------------------------\n";
    cout <<   "   ANALISIS BATAS ITR            \n";
    cout <<   "---------------------------------\n";
    cout << "  Batas KUNING (ITR <= x) : "; cin >> batasKuning;
    cout << "  Batas MERAH  (ITR <= x) : "; cin >> batasMerah;

    if (cin.fail()) {
        cout << " [!] Input harus berupa angka! Silakan coba lagi.\n";
        
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        
        return analisisBatas(daftarBarang);}
    
    if (batasMerah > batasKuning){ 
        cout << "\n  [!] Batas merah tidak boleh lebih besar dari batas kuning!\n";
        return analisisBatas(daftarBarang);
    }

    int idxMerah    = binarySearchBatas(daftarBarang, batasMerah);
    int idxKuning   = binarySearchBatas(daftarBarang, batasKuning);
    int startKuning = idxMerah + 1;
    int startHijau  = idxKuning + 1;

    cout << "\n========================================\n";
    cout <<   "     HASIL ANALISIS STATUS ITR          \n";
    cout <<   "========================================\n";

    auto cetakHeader = [&]() {
        cout << "  " << left << setw(5) << "No" << setw(20) << "Nama Barang"
             << setw(12) << "ITR" << setw(15) << "Harga Jual" << "\n";
        cout << "  " << string(52, '-') << "\n";
    };
    auto cetakBaris = [&](int no, const Barang& b) {
        cout << "  " << left << setw(5) << no << setw(20) << b.nama
             << setw(12) << fixed << setprecision(4) << b.itr
             << setw(15) << setprecision(2) << b.hargaJual << "\n";
    };

    // MERAH
    cout << "\n  [MERAH] ITR <= " << batasMerah << "\n";
    cout << "  " << string(52, '-') << "\n";
    if (idxMerah == -1) cout << "  Tidak ada barang dalam kategori MERAH.\n";
    else { cetakHeader(); for (int i = 0; i <= idxMerah; i++) cetakBaris(i+1, daftarBarang[i]); }

    // KUNING
    cout << "\n  [KUNING] " << batasMerah << " < ITR <= " << batasKuning << "\n";
    cout << "  " << string(52, '-') << "\n";
    if (startKuning > idxKuning) cout << "  Tidak ada barang dalam kategori KUNING.\n";
    else {
        cetakHeader();
        int no = 1;
        for (int i = startKuning; i <= idxKuning; i++, no++) cetakBaris(no, daftarBarang[i]);
    }

    // HIJAU
    cout << "\n  [HIJAU] ITR > " << batasKuning << "\n";
    cout << "  " << string(52, '-') << "\n";
    if (startHijau >= (int)daftarBarang.size()) cout << "  Tidak ada barang dalam kategori HIJAU.\n";
    else {
        cetakHeader();
        int no = 1;
        for (int i = startHijau; i < (int)daftarBarang.size(); i++, no++) cetakBaris(no, daftarBarang[i]);
    }

    // Diskon
    cout << "\n========================================\n";
    cout <<   "        PEMBERIAN DISKON                \n";
    cout <<   "========================================\n";

    double diskonKuning = 0, diskonMerah = 0;
    if (startKuning <= idxKuning) {
        cout << "  Diskon barang KUNING (%): "; cin >> diskonKuning;
    } else cout << "  [INFO] Tidak ada barang KUNING, dilewati.\n";

    if (idxMerah >= 0) {
        cout << "  Diskon barang MERAH  (%): "; cin >> diskonMerah;
    } else cout << "  [INFO] Tidak ada barang MERAH, dilewati.\n";
    system("cls");
    cout << "\n========================================\n";
    cout <<   "     HARGA JUAL SETELAH DISKON          \n";
    cout <<   "========================================\n";

    if (idxMerah >= 0) {
        cout << "\n  [MERAH] Diskon " << diskonMerah << "%\n";
        cout << "  " << string(85, '-') << "\n";
        tampilkanDiskon(daftarBarang, 0, idxMerah, diskonMerah);
    }
    if (startKuning <= idxKuning) {
        cout << "\n  [KUNING] Diskon " << diskonKuning << "%\n";
        cout << "  " << string(85, '-') << "\n";
        tampilkanDiskon(daftarBarang, startKuning, idxKuning, diskonKuning);
    }
    if (startHijau < (int)daftarBarang.size()) {
        cout << "\n  [HIJAU] Tidak ada diskon\n";
        cout << "  " << string(52, '-') << "\n";
        cetakHeader();
        int no = 1;
        for (int i = startHijau; i < (int)daftarBarang.size(); i++, no++)
            cetakBaris(no, daftarBarang[i]);
    }

    simpanCSV(daftarBarang);
    cout << "\n  [OK] Harga jual setelah diskon tersimpan ke " << NAMA_FILE << "\n";
    cout << string(40, '=') << "\n";
}

// ─── Edit Barang ──────────────────────────────────────────────────────────────
void editBarang(vector<Barang>& daftarBarang) {
    if (daftarBarang.empty()) {
        cout << "\n  [!] Belum ada barang yang diinput!\n";
        return;
    }

    tampilkanBarang(daftarBarang);

    cout << "  Masukkan nomor barang yang ingin diedit (0 untuk batal): ";
    int nomor;
    cin >> nomor;

    if (cin.fail()) {
        cout << " [!] Input harus berupa angka! Silakan coba lagi.\n";
        
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        
        return editBarang(daftarBarang);
    }

    if (nomor == 0) {
        cout << "  [INFO] Edit dibatalkan.\n";
        return;
    }
    if (nomor < 1 || nomor > (int)daftarBarang.size()) {
        cout << "  [!] Nomor tidak valid!\n";
        return editBarang(daftarBarang);
    }

    Barang& b = daftarBarang[nomor - 1];

    cout << "\n  Edit barang: \"" << b.nama << "\"\n";
    cout << "  (Tekan Enter tanpa input untuk mempertahankan nilai lama)\n";
    cout << "\n---------------------------------\n";
    cout <<   "         EDIT BARANG             \n";
    cout <<   "---------------------------------\n";

    string input;
    cin.ignore();

    system("cls");
    cout << "  Harga stok awal   [" << fixed << setprecision(2) << b.hargaStokAwal << "] : ";
    getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaStokAwal)) {
        cout << " [!] Input harus berupa angka. Harga stok awal: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    cout << "  Harga stok akhir  [" << b.hargaStokAkhir << "] : ";
    getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaStokAkhir)) {
        cout << " [!] Input harus berupa angka. Harga stok akhir: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    cout << "  HPP               [" << b.hpp << "] : ";
    getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hpp)) {
        cout << " [!] Input harus berupa angka. HPP: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    cout << "  Harga jual        [" << b.hargaJual << "] : ";
    getline(cin, input);
    if (!input.empty()) {
    stringstream ss(input);
    while (!(ss >> b.hargaJual)) {
        cout << " [!] Input harus berupa angka. Harga jual: ";
        getline(cin, input);
        ss.clear(); 
        ss.str(input); 
        }
    }

    // Hitung ulang ITR dengan nilai baru
    b.itr = hitungITR(b.hargaStokAwal, b.hargaStokAkhir, b.hpp);
    sudahDiSort = false;

    simpanCSV(daftarBarang);

    cout << "\n  [OK] Barang \"" << b.nama << "\" berhasil diperbarui!\n";
    cout << "  [OK] ITR baru      : " << setprecision(4) << b.itr << "\n";
    cout << "       ITR = HPP / rata-rata stok\n";
    cout << "           = " << b.hpp << " / "
         << (b.hargaStokAwal + b.hargaStokAkhir) / 2.0
         << " = " << b.itr << "\n";
    cout << "  [OK] Data tersimpan ke " << NAMA_FILE << "\n";
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    vector<Barang> daftarBarang;
    char pilihan;

    cout << "========================================\n";
    cout << "   SISTEM MANAJEMEN INVENTORI + ITR     \n";
    cout << "========================================\n";

    muatCSV(daftarBarang);
    // Recalculate ITR untuk semua barang yang dimuat
if (!daftarBarang.empty()) {
    for (Barang& b : daftarBarang) {
        b.itr = hitungITR(b.hargaStokAwal, b.hargaStokAkhir, b.hpp);
    }
    simpanCSV(daftarBarang);  // simpan ulang supaya CSV sinkron
    cout << "  [INFO] ITR " << daftarBarang.size() << " barang berhasil dihitung ulang.\n";
}

    while (true) {
        cout << "\n----------------------------------\n";
        cout <<   "          MENU UTAMA              \n";
        cout <<   "----------------------------------\n";
        cout <<   "  a. Input barang                 \n";
        cout <<   "  b. Sorting barang (Quick Sort)  \n";
        cout <<   "  c. Analisis batas ITR            \n";
        cout <<   "  d. Hapus barang                 \n";
        cout <<   "  e. Edit barang                  \n";
        cout <<   "  f. Simpan ulang ke inventori.csv\n";
        cout <<   "  q. Keluar                       \n";
        cout <<   "----------------------------------\n";
        cout << "  Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 'a': case 'A': inputBarang(daftarBarang);  break;
            case 'b': case 'B':
                if (daftarBarang.empty()) {
                    cout << "\n  [!] Belum ada barang. Pilih 'a' dulu.\n";
                } else {
                    quickSort(daftarBarang, 0, (int)daftarBarang.size() - 1);
                    sudahDiSort = true;
                    system("cls");
                    cout << "\n  [OK] Barang berhasil diurutkan.\n";
                    tampilkanBarang(daftarBarang);
                }
                break;
            case 'c': case 'C': analisisBatas(daftarBarang); break;
            case 'd': case 'D': hapusBarang(daftarBarang);   break;
            case 'e': case 'E': editBarang(daftarBarang); break;
            case 'f': case 'F':
                if (daftarBarang.empty()) {
                    cout << "\n  [!] Belum ada data untuk disimpan.\n";
                } else {
                    simpanCSV(daftarBarang);
                    cout << "\n  [OK] Data disimpan ke " << NAMA_FILE << "\n";
                }
                system("cls");
                break;
            case 'q': case 'Q':
                cout << "\n  Terima kasih! Program selesai.\n\n";
                return 0;
            default:
                cout << "\n  [!] Pilihan tidak valid. Masukkan 'a'-'f' atau 'q'.\n";
        }
    }

    return 0;
}