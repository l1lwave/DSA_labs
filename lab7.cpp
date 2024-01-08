#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_SIZE = 100;

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int A[MAX_SIZE][MAX_SIZE];
    int n;
    int m;

    std::cout << "Enter the size of the array (n x m): ";
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            A[i][j] = std::rand() % 100 - 50;
        }
    }

    std::cout << "Generated array A[" << n << "][" << m << "]:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << A[i][j] << "\t";
        }
        std::cout << "\n";
    }

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (A[i][j] < 0) {
                std::cout << "First negative element: " << A[i][j] << std::endl;
                std::cout << "Coordinates: row " << i << ", column " << j << std::endl;
                return 0;
            }
        }
    }

    std::cout << "There are no negative elements in the array." << std::endl;

    return 0;
}
