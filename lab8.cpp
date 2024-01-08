#include <iostream>
#include <vector>
#include <algorithm>

// Функція сортування купою (heap sort)
void heapify(std::vector<double>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<double>& arr) {
    int n = arr.size();

    // Будуємо купу (heap) по масиву
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Використовуємо купу для сортування масиву
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Функція для бінарного пошуку
int binarySearch(const std::vector<double>& arr, double key) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid; // Знайдено елемент, повертаємо його позицію
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1; // Елемент не знайдено
}

int main() {
    int N, M;

    // Введення N та M
    std::cout << "Enter N and M (1 < N, M < 256): ";
    std::cin >> N >> M;

    // Введення послідовності N ключів
    std::vector<double> sequenceN(N);
    std::cout << "Enter sequence of " << N << " keys: ";
    for (int i = 0; i < N; ++i)
        std::cin >> sequenceN[i];

    // Сортування купою
    heapSort(sequenceN);

    // Введення послідовності M ключів
    std::vector<double> sequenceM(M);
    std::cout << "Enter sequence of " << M << " keys: ";
    for (int i = 0; i < M; ++i)
        std::cin >> sequenceM[i];

    // Бінарний пошук та виведення результатів
    for (int i = 0; i < M; ++i) {
        int position = binarySearch(sequenceN, sequenceM[i]);
        if (position != -1)
            std::cout << "Key " << sequenceM[i] << " found at position " << position + 1 << std::endl;
        else
            std::cout << "Key " << sequenceM[i] << " not found in the first sequence" << std::endl;
    }

    return 0;
}
