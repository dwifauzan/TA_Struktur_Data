#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int userInput() {
	ifstream myFile("Karyawan.txt");
	int pilihan;

		cout << "Sistem Data Karyawan" << endl;
		cout << "====================" << endl;
		cout << "1. Tampilkan data" << endl;
		cout << "2. Tambah Data" << endl;
		cout << "3. Ubah Data" << endl;
		cout << "4. Hapus data" << endl;
		cout << "5. Keluar" <<endl;

		cin >> pilihan;
	return pilihan;
}

void tampilkanDataKaryawan() {
	ifstream myFile("Karyawan.txt");

	if (!myFile) {
		cout << "Gagal menampilkan file" << endl;
		return;
	}

	string teks;

	while (getline(myFile, teks)) {
		stringstream ss(teks);
		int angkaNik;
		string nama, departemen, jabatan;

		ss >> angkaNik >> nama >> departemen >> jabatan;
		cout << "\nNIK : " << angkaNik << "\nNama : " << nama << "\nDepartemen : " << departemen << "\nJabatan : " << jabatan << endl;
	}
}

void tulisDataKaryawan(int nik, string nama, string dpt, string jbt) {
	ofstream myFile("Karyawan.txt", ios::app);

	if (!myFile) {
		cout << "Gagal membuat file!" << endl;
		return;
	}

	myFile << nik << " " << nama << " " << dpt << " " << jbt << endl;

	myFile.close();
}

void updateDataKaryawan() {
	ifstream myFile("Karyawan.txt");
	ofstream myFileTemp("temp_Karyawan.txt", ios::app);

	if (!myFile || !myFileTemp) {
		cout << "File tidak bisa dibuka" << endl;
		return;
	}

	vector<string> baris;
	string line;
	while (getline(myFile, line)) {
		baris.push_back(line);
	}
	myFile.close();

	if (baris.empty()) {
		cout << "Tidak ada data untuk diupdate" << endl;
		return;
	}

	cout << "\nData karyawan saat ini" << endl;
	for (size_t i = 0; i < baris.size(); ++i) {
		cout << i + 1 << ". " << baris[i] << endl;
	}

	int nmr;
	cout << "Pilih nomor yang ingin diupdate : ";
	cin >> nmr;

	if (nmr < 1 || nmr > (int)baris.size()) {
		cout << "Nomor tidak valid" << endl;
	}

	string nama, dpt, jbt;
	int nik;
	cout << "Massukkan data baru" << endl;
	cout << "NIK : ";
	cin >> nik;
	cout << "Masukkan nama : ";
	cin >> nama;
	cout << "Masukkan departemen : ";
	cin >> dpt;
	cout << "Masukkan jabatan : ";
	cin >> jbt;

	baris[nmr - 1] = to_string(nik) + " " + nama + " " + dpt + " " + jbt;

	for (auto &b : baris) {
		myFileTemp << b << endl;
	}

	myFileTemp.close();

	remove("Karyawan.txt");
	rename("temp_Karyawan.txt", "Karyawan.txt");

	cout << "Data berhasil disimpan!" << endl;
}

void hapusDataKaryawan() {
	ifstream myFile("Karyawan.txt");

	if (!myFile) {
		cout << "Belum menghapus data" << endl;
		return;
	}

	vector<string> baris;
    string line;
    while (getline(myFile, line)) {
        baris.push_back(line);
    }
    myFile.close();

    if (baris.empty()) {
        cout << "Data yang dipilih tidak ada!" << endl;
        return;
    }

    cout << "\nData saat ini : " << endl;
    for (size_t i = 0; i < baris.size(); ++i) {
        cout << i + 1 << ". " << baris[i] << endl;
    }

	int idx;
    cout << "\nPilih nomor data yang ingin dihapus: ";
    cin >> idx;

    if (idx < 1 || idx > (int)baris.size()) {
        cout << "Nomor tidak valid!" << endl;
        return;
    }

    baris.erase(baris.begin() + idx - 1);

    ofstream newHistory("history_karyawan.txt", ios::app);
    for (auto &b : baris) {
        newHistory << b << endl;
    }
    newHistory.close();

	remove("Karyawan.txt");
	rename("history_karyawan.txt", "Karyawan.txt");

    cout << "Data karyawan berhasil dihapus!" << endl;
}



int main() {
	int pilihan = userInput();

	if (pilihan == 1) {
		tampilkanDataKaryawan();
	} else if (pilihan == 2) {
		int nik;
		string nama, dpt, jbt;

		cout << "masukkan nik :";
		cin >> nik;
		cout << "masukkan nama :";
		cin >> nama;
		cout << "masukkan departemen :";
		cin >> dpt;
		cout << "masukkan jabatan :";
		cin >> jbt;

		tulisDataKaryawan(nik, nama, dpt, jbt);

	} else if (pilihan == 3) {
		updateDataKaryawan();

	} else if (pilihan == 4) {
		hapusDataKaryawan();

	} else if (pilihan == 5) {
		cout << "terimakasih telah menggunakan program ini^^" << endl;
		return 0;
	} else {
		cout << "Pilihan tidak valid" << endl;
	}
	
	

	return 0;

}