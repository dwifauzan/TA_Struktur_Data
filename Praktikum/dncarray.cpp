#include <iostream>
using namespace std;

//Fungsi untuk mengembalikan nilai terbesar
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

//Menghitung maksimum sum dari kedua sisi dan kemudian menjumlahkan keduanya
int maksCrossSum(int arr[], int kiri, int mid, int kanan) {
    //Variabel sementara untuk menyimpan elemen indeks terbesar
    int sum = 0;
    int sum_Kiri = -1;

    for (int i = mid; i >= kiri; i--) {
        sum = sum + arr[i];
        if (sum > sum_Kiri){
            sum_Kiri = sum;
        }
    }

    
    

    return sum_Kiri + sum_kanan;
}

//Fungsi untuk membagi dua array yang dimasukkan
int subArraySum(int arr[], int kiri, int kanan) {
    //Fungsi rekursi agar tidak berjalan terus-menerus
    if (kiri >= kanan)  { 
            return arr[kiri];
        }

    //Mencari titik tengah
    int mid = (kiri + kanan) / 2;

    return max(max(subArraySum(arr, kiri, mid), subArraySum(arr, mid+1, kanan)), maksCrossSum(arr, kiri, mid, kanan));
}

//program utama (input dan output)
int main() {
    //Input size array
    int arrSize, i;
    cout << "Masukkan ukuran array: ";
    cin >> arrSize;

    //Input array
    int arr[arrSize];
    
    for (i = 0; i < arrSize; i++){
        cout << "Elemen ke-"<<i+1<<": ";
        cin >> arr[i];
    }

    //Memanggil fungsi untuk menampilkan hasil
    cout << "maks sub-arraynya adalah: " << subArraySum(arr, 0, arrSize - 1);
    return 0;
}