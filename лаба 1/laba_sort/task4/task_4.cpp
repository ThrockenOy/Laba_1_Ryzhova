#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <algorithm>
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

//Merge
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[100000], R[100000];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick
int partition(int arr[], int low, int high) {
    int pivot = arr[rand() % (high - low + 1) + low];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Heap
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ================= MAIN =================
int main() {
    cout << "=== Program started ===" << endl;
    ofstream f("results_shaker.csv", ios::out);
    f << "size,case,shaker_ms\n";

    int sizes[] = {1000, 5000, 10000, 25000, 50000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(0));

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];
        int arr1[100000], arr2[100000], arr3[100000];

        // три типа входных данных
        for (int caseType = 0; caseType < 3; caseType++) {
            // Генерация
            for (int i = 0; i < n; i++) {
                arr1[i] = rand() % 10000;
                arr2[i] = arr1[i];
                arr3[i] = arr1[i];
            }

            if (caseType == 0) { // лучший случай
                sort(arr1, arr1 + n);
                sort(arr2, arr2 + n);
                sort(arr3, arr3 + n);
            } else if (caseType == 2) { // худший случай
                sort(arr1, arr1 + n, greater<int>());
                sort(arr2, arr2 + n, greater<int>());
                sort(arr3, arr3 + n, greater<int>());
            }
            string caseName = (caseType == 0) ? "best" : (caseType == 1) ? "average" : "worst";

            //
            auto start = chrono::high_resolution_clock::now();
            shaker_sort(arr1, n);
            auto end = chrono::high_resolution_clock::now();
            auto shaker_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();


            // ---------- Вывод ----------
            f << n << "," << caseName << "," << shaker_time << "\n";
            cout << "Size: " << n
                 << " | Case: " << caseName
                 << " | Shaker: " << shaker_time;

        }
    }
    f.close();
    cout << "\nResults saved to results_task4.csv\n";
    return 0;
}
