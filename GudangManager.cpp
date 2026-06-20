#pragma once
#include <fstream>
#include "Hashing.cpp"
#include "Mheap.cpp"
#include "Barang.cpp"

using namespace std;

string escapeCSV(const string& s) {
    bool needsQuotes = s.find(',') != string::npos || s.find('"') != string::npos;
    if (!needsQuotes) return s;
    string escaped;
    for (char c : s) {
        if (c == '"') escaped += "\"\"";
        else escaped += c;
    }
    return "\"" + escaped + "\"";
}

vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string current;
    bool inQuotes = false;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            fields.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

// Class untuk mengintegrasikan Hash Table dan Min Heap
class GudangManager {
private:
    Hashing* hashTable;
    Mheap* minHeap;
    string namaFileCSV;

    void simpanCSV() {
        vector<Barang> semua = hashTable->dapatkanSemuaBarang();
        ofstream file(namaFileCSV);
        if (!file.is_open()) {
            cout << "Gagal menyimpan file CSV!\n";
            return;
        }
        file << "id,nama,stok,lokasiRak,prioritas\n";
        for (const auto& b : semua) {
            file << b.id << ","
                 << escapeCSV(b.nama) << ","
                 << b.stok << ","
                 << escapeCSV(b.lokasiRak) << ","
                 << b.prioritas << "\n";
        }
        file.close();
    }

    void muatCSV() {
        ifstream file(namaFileCSV);
        if (!file.is_open()) return;

        string header;
        getline(file, header);

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            vector<string> fields = parseCSVLine(line);
            if (fields.size() >= 5) {
                int id = stoi(fields[0]);
                string nama = fields[1];
                int stok = stoi(fields[2]);
                string lokasiRak = fields[3];
                int prioritas = stoi(fields[4]);
                Barang barangBaru(id, nama, stok, lokasiRak, prioritas);
                hashTable->tambahBarang(barangBaru);
                minHeap->tambah_prioritas(barangBaru);
            }
        }
        file.close();
    }

public:
    GudangManager(int kapasitas, string csvFile = "gudang_data.csv") {
        namaFileCSV = csvFile;
        hashTable = new Hashing(kapasitas);
        minHeap = new Mheap();
        muatCSV();
    }

    ~GudangManager() {
        simpanCSV();
        delete hashTable;
        delete minHeap;
    }

    // Menambah barang ke Hash Table dan Min Heap
    void tambahBarang(int id, string nama, int stok, string lokasiRak, int prioritas) {
        Barang barangBaru(id, nama, stok, lokasiRak, prioritas);
        hashTable->tambahBarang(barangBaru);
        minHeap->tambah_prioritas(barangBaru);
        simpanCSV();
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
        Barang removed = minHeap->ambil_prioritas();
        if (removed.id != -1) {
            hashTable->hapusBarang(removed.id);
        }
        simpanCSV();
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
