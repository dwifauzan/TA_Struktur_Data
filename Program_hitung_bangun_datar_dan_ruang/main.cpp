#include <iostream>
#include <string>
#include "menu.h"
#include "bangun_datar/segitiga.h"
#include "bangun_datar/lingkaran.h"
#include "bangun_ruang/kubus.h"
#include "bangun_ruang/balok.h"
using namespace std;


string show_menu();


int main()
{
    while (true)
    {
        string selected_menu = show_menu();
    if (selected_menu == "1")
    {
        float a, b, c, t;
        cout << "Masukkan alas: ";
        cin >> a;
        cout << "Masukkan tinggi: ";
        cin >> t;
        cout << "Masukkan sisi b dan c: ";
        cin >> b >> c;


        cout << "Luas Segitiga = " << bangun_datar::luas_segitiga(a, t) << endl;
        cout << "Keliling Segitiga = " << bangun_datar::keliling_segitiga(a, b, c) << endl;
    }
    else if (selected_menu == "2")
    {
        float r;
        cout << "Masukkan jari-jari: ";
        cin >> r;


        cout << "Luas Lingkaran = " << bangun_datar::luas_lingkaran(r) << endl;
        cout << "Keliling Lingkaran = " << bangun_datar::keliling_lingkaran(r) << endl;
    }
    else if (selected_menu == "3")
    {
        float sisi;
        cout << "Masukkan sisi kubus: ";
        cin >> sisi;


        cout << "Volume Kubus = " << bangun_ruang::volume_kubus(sisi) << endl;
        cout << "Luas Permukaan Kubus = " << bangun_ruang::luas_permukaan_kubus(sisi) << endl;
    }
    else if (selected_menu == "4")
    {
        float p, l, t;
        cout << "Masukkan panjang, lebar, dan tinggi balok: ";
        cin >> p >> l >> t;


        cout << "Volume Balok = " << bangun_ruang::volume_balok(p, l, t) << endl;
        cout << "Luas Permukaan Balok = " << bangun_ruang::luas_permukaan_balok(p, l, t) << endl;
    }
    else
    {
        cout << "Pilihan tidak valid." << endl;
    }
}
}
