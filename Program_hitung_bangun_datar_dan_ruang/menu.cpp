#include <iostream>
#include <string>
#include "menu.h"
using namespace std;


string show_menu()
{
    int menu_number = 4;
    string selected_menu = "";
    string menu[] = {
        "1. Luas dan Keliling Segitiga",
        "2. Luas dan Keliling Lingkaran",   
        "3. Volume dan Luas Permukaan Kubus",
        "4. Volume dan Luas Permukaan Balok"
    };


    while (selected_menu == "" || stoi(selected_menu) > menu_number)
    {
        cout << "Menu: " << endl;
        for (int i = 0; i < menu_number; i++)
        {
            cout << menu[i] << endl;
        }
        cout << "Pilih menu: ";
        cin >> selected_menu;
    }
    return selected_menu;
}

