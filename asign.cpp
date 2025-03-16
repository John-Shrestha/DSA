#include <iostream>
#include <chrono>  // For measuring time
using namespace std;
using namespace chrono;  // For convenience

// Binary Search Function
int binarySearch(int numbers[], int N, int target) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (numbers[mid] == target) return mid;
        if (numbers[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Interpolation Search Function
int interpolationSearch(int numbers[], int N, int target) {
    int left = 0, right = N - 1;
    while (left <= right && target >= numbers[left] && target <= numbers[right]) {
        int pos = left + ((target - numbers[left]) * (right - left)) / (numbers[right] - numbers[left]);
        if (numbers[pos] == target) return pos;
        if (numbers[pos] < target) left = pos + 1;
        else right = pos - 1;
    }
    return -1;
}

// Merge Sort and Merge Function
void merge(int numbers[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int leftArr[n1], rightArr[n2];
    for (int i = 0; i < n1; i++) leftArr[i] = numbers[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = numbers[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) numbers[k++] = leftArr[i++];
        else numbers[k++] = rightArr[j++];
    }
    while (i < n1) numbers[k++] = leftArr[i++];
    while (j < n2) numbers[k++] = rightArr[j++];
}
void mergeSort(int numbers[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);
        merge(numbers, left, mid, right);
    }
}

// Selection Sort
void selectionSort(int numbers[], int N) {
    for (int i = 0; i < N - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (numbers[j] < numbers[minIndex]) 
            minIndex = j;
        }
        swap(numbers[i], numbers[minIndex]);
    }
}

// Function to display array
void displayArray(const int numbers[], int N, const string& label) {
    cout << label << ": ";
    for (int i = 0; i < N; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Enter the number of integers: ";
    cin >> N;

    int numbers[N];
    cout << "Enter " << N << " integers:" << endl;
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    // Measure and display Selection Sort
    int selectionArr[N];
    copy(numbers, numbers + N, selectionArr);
    auto start = high_resolution_clock::now();
    selectionSort(selectionArr, N);
    auto end = high_resolution_clock::now();
    auto selectionDuration = duration_cast<milliseconds>(end - start).count();
    displayArray(selectionArr, N, "Array after Selection Sort");
    cout << "Selection Sort Time: " << selectionDuration << " ms" << endl;

    // Measure and display Merge Sort
    int mergeArr[N];
    copy(numbers, numbers + N, mergeArr);
    start = high_resolution_clock::now();
    mergeSort(mergeArr, 0, N - 1);
    end = high_resolution_clock::now();
    auto mergeDuration = duration_cast<milliseconds>(end - start).count();
    displayArray(mergeArr, N, "Array after Merge Sort");
    cout << "Merge Sort Time: " << mergeDuration << " ms" << endl;

    // Perform Binary Search (on Merge Sorted Array)
    int target;
    cout << "Enter the number to search using Binary Search: ";
    cin >> target;

    start = high_resolution_clock::now();
    int binaryResult = binarySearch(mergeArr, N, target);
    end = high_resolution_clock::now();
    auto binarySearchDuration = duration_cast<microseconds>(end - start).count();

    if (binaryResult != -1) {
        cout << "Binary Search: Element found at index " << binaryResult << endl;
    } else {
        cout << "Binary Search: Element not found" << endl;
    }
    cout << "Binary Search Time: " << binarySearchDuration << " microseconds" << endl;

    // Perform Interpolation Search (on Merge Sorted Array)
    cout << "Enter the number to search using Interpolation Search: ";
    cin >> target;

    start = high_resolution_clock::now();
    int interpolationResult = interpolationSearch(mergeArr, N, target);
    end = high_resolution_clock::now();
    auto interpolationSearchDuration = duration_cast<microseconds>(end - start).count();

    if (interpolationResult != -1) {
        cout << "Interpolation Search: Element found at index " << interpolationResult << endl;
    } else {
        cout << "Interpolation Search: Element not found" << endl;
    }
    cout << "Interpolation Search Time: " << interpolationSearchDuration << " microseconds" << endl;

    return 0;
}
