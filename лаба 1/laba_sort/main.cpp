#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// пузырьковая сортировка
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// сортировка вставкой
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// шейкер-сортировка
void shaker_sort(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        for (int i = left; i < right; i++)
            if (arr[i] > arr[i + 1]) swap(arr[i], arr[i + 1]);
        right--;
        for (int i = right; i > left; i--)
            if (arr[i] < arr[i - 1]) swap(arr[i], arr[i - 1]);
        left++;
    }
}

int main() {
    ofstream f("results_o3.csv", ios::out);
    f << "size,bubble_ms,insertion_ms,shaker_ms\n";

    srand(time(0));

    int sizes[] = {1000, 5000, 10000, 25000, 50000, 75000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];

        int arr1[100000];
        int arr2[100000];
        int arr3[100000];

        for (int i = 0; i < n; i++) {
            int val = rand() % 10000;
            arr1[i] = val;
            arr2[i] = val;
            arr3[i] = val;
        }

        auto start = chrono::high_resolution_clock::now();
        bubble_sort(arr1, n);
        auto end = chrono::high_resolution_clock::now();
        auto bubble_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        insertion_sort(arr2, n);
        cout << arr2[0] << " " << arr2[n-1] << endl;
        end = chrono::high_resolution_clock::now();
        auto insertion_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        shaker_sort(arr3, n);
        end = chrono::high_resolution_clock::now();
        auto shaker_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        cout << "Size: " << n
             << " | Bubble: " << bubble_time
             << " ms, Insertion: " << insertion_time
             << " ms, Shaker: " << shaker_time << " ms" << endl;

        f << n << "," << bubble_time << "," << insertion_time << "," << shaker_time << "\n";
    }

    f.close();
    return 0;
}
