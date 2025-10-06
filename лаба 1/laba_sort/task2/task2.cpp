#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
using namespace std;



// ================= Merge Sort =================
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for(int i=0;i<n1;i++) L[i]=arr[l+i];
    for(int i=0;i<n2;i++) R[i]=arr[m+1+i];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
}
void merge_sort(int arr[], int l, int r){
    if(l<r){
        int m = l + (r-l)/2;
        merge_sort(arr,l,m);
        merge_sort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

// ================= Quick Sort =================
int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}
void quick_sort(int arr[], int low, int high){
    if(low<high){
        int pi = partition(arr,low,high);
        quick_sort(arr,low,pi-1);
        quick_sort(arr,pi+1,high);
    }
}

// ================= Heap Sort =================
void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if(l<n && arr[l]>arr[largest]) largest=l;
    if(r<n && arr[r]>arr[largest]) largest=r;
    if(largest!=i){
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);
    }
}
void heap_sort(int arr[], int n){
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i);
    for(int i=n-1;i>0;i--){
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
    }
}

// ================= Main =================
int main(){
    cout << "=== Program started ===" << endl;
    ofstream f("results_task2.csv", ios::out);
    f << "size,merge_ms,quick_ms,heap_ms\n";

    int sizes[] = {1000,5000,10000,25000,50000, 75000};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);

    srand(time(0));

    for(int k=0;k<num_sizes;k++){
        int n = sizes[k];
        int arr1[100000], arr2[100000], arr3[100000];

        for(int i=0;i<n;i++){
            int val = rand()%10000;
            arr1[i]=arr2[i]=arr3[i]=val;
        }

        auto start = chrono::high_resolution_clock::now();
        merge_sort(arr1,0,n-1);
        auto end = chrono::high_resolution_clock::now();
        auto merge_time = chrono::duration_cast<chrono::milliseconds>(end-start).count();

        start = chrono::high_resolution_clock::now();
        quick_sort(arr2,0,n-1);
        end = chrono::high_resolution_clock::now();
        auto quick_time = chrono::duration_cast<chrono::milliseconds>(end-start).count();

        start = chrono::high_resolution_clock::now();
        heap_sort(arr3,n);
        end = chrono::high_resolution_clock::now();
        auto heap_time = chrono::duration_cast<chrono::milliseconds>(end-start).count();

        f << n << "," << merge_time << "," << quick_time << "," << heap_time << "\n";
        cout << "Size: " << n
             << " | Merge: " << merge_time
             << " ms, Quick: " << quick_time
             << " ms, Heap: " << heap_time << " ms\n";
    }
    f.close();
    return 0;

}
