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

    // Constructor untuk inisialisasi data barang
    Barang(int id, string nama, int stok, string lokasiRak, int prioritas)
        : id(id), nama(nama), stok(stok), lokasiRak(lokasiRak), prioritas(prioritas) {}
};
