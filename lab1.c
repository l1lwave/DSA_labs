#include <iostream>
#include <cstdlib>
#include <ctime>

const int N = 100;

// Функція для знаходження мінімального елемента масиву та його індексу
int findMinElement(const int arr[], int size) {
    int minElement = arr[0];
    int minIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (arr[i] < minElement) {
            minElement = arr[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Функція для обчислення суми елементів з парними індексами перед мінімальним елементом
int calculateSumBeforeMin(const int arr[], int size) {
    int minIndex = findMinElement(arr, size);
    int sum = 0;

    for (int i = 0; i < minIndex; i += 2) {
        sum += arr[i];
    }

    return sum;
}

// Функція для додавання елемента в масив за певним індексом
bool insertElement(int arr[], int& size, int index, int value) {
    if (size >= N) {
        std::cout << "Неможливо додати елемент, масив вже заповнений." << std::endl;
        return false;
    }

    // Пересуваємо всі елементи праворуч, щоб зробити місце для нового елемента
    for (int i = size - 1; i >= index; --i) {
        arr[i + 1] = arr[i];
    }

    // Додаємо новий елемент
    arr[index] = value;
    size++;

    return true;
}

int main() {
    int arr[N];
    int n;

    std::cout << "Введiть нижню межу дiапазону: ";
    int lowerBound;
    std::cin >> lowerBound;

    std::cout << "Введiть верхню межу дiапазону: ";
    int upperBound;
    std::cin >> upperBound;

    std::cout << "Введiть кiлькiсть елементiв (n <= " << N << "): ";
    std::cin >> n;

    if (n > N) {
        std::cout << "Кiлькiсть елементiв n не може перевищувати " << N << std::endl;
        return 1;
    }

    // Заповнюємо масив випадковими числами
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
    }

    std::cout << "Масив до обробки:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    int sum = calculateSumBeforeMin(arr, n);
    std::cout << "Завдання 1" << std::endl;

    if (sum == 0) {
        std::cout << "Масив порожнiй пiсля обробки." << std::endl;
    }
    else {
        std::cout << "Сума елементiв з парними iндексами перед мiнiмальним елементом: " << sum << std::endl;
    }

    // Виконуємо завдання 2
    for (int i = n - 1; i >= 0; --i) {
        if (arr[i] % 2 == 0) {
            if (!insertElement(arr, n, i + 1, 0)) {
                break;
            }
        }
    }

   std::cout << "Завдання 2" << std::endl;
    std::cout << "Масив пiсля додавання елементiв зi значенням 0:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;


    return 0;}
