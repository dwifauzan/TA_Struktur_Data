#include <string>

using namespace std;

// Class Barang untuk menyimpan data dasar barang
class Barang {
public:
    int id;
    string nama;
    int stok;
    string lokasiRak;
    int prioritas;

    // Penanda slot kosong supaya bisa dipanggil
    Barang() : id(-1), nama(""), stok(0), lokasiRak(""), prioritas(0) {}
    // Constructor untuk inisialisasi data barang
    Barang(int id, string nama, int stok, string lokasiRak, int prioritas)
        : id(id), nama(nama), stok(stok), lokasiRak(lokasiRak), prioritas(prioritas) {}
};
