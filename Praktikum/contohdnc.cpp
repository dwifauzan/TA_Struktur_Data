#include <iostream>
using namespace std;

int max(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

int maksCrossSum(int arr[], int kiri, int mid, int kanan) {
	int sum = 0;
	int sum_kiri = -1;

	for (int i = mid; i >= kiri; i--) {
		sum = sum + arr[i];
		if (sum > sum_kiri) {
			sum_kiri = sum;
		}
	}

	sum = 0;
    int sum_kanan = -1;
    
    for (int i = mid + 1; i <= kanan; i++) {
		sum = sum + arr[i];
		if (sum > sum_kanan) {
			sum_kanan = sum;
		}

	}

	return sum_kiri + sum_kanan;
}

int subArraySum(int arr[], int kiri, int kanan) {
	if (kiri >= kanan) {
		return arr[kiri];
	}

	int mid = (kiri + kanan) / 2;

	return max(max(subArraySum(arr, kiri, mid), subArraySum(arr, mid + 1, kanan)), maksCrossSum(arr, kiri, mid, kanan));
}

int main() {
	//Input size array
	int arrSize, i;
	cout << "Masukkan ukuran array: ";
	cin >> arrSize;

	//Input array
	int arr[arrSize];

	for (i = 0; i < arrSize; i++){
		cout << "Elemen ke-" << i+1 << ": ";
		cin >> arr[i];
	}

	cout << "maks sub-arraynya adalah: " << subArraySum(arr, 0, arrSize - 1);
	return 0;
}