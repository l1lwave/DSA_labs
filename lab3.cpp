#include <iostream>
#include <stack>

void firstEx(){
    std::stack<int> myStack;
    std::stack<int> evenStack; // Стек для парних чисел
    std::stack<int> oddStack;  // Стек для непарних чисел
    int n; // Кількість чисел, які ви хочете ввести
    int num; // Змінна для зберігання введеного числа
    std::cout << "Enter the number of numbers you want to enter: ";
    std::cin >> n;

    std::cout << "Put integers on stack:\n";

    for (int i = 0; i < n; i++) {
        std::cin >> num;
        myStack.push(num); // Додаємо число до стеку
        if (num % 2 == 0) {
            evenStack.push(num); // Додаємо парне число до стеку парних чисел
        } else {
            oddStack.push(num);  // Додаємо непарне число до стеку непарних чисел
        }
    }

    std::cout << "Numbers on stack in input order:\n";

    while (!myStack.empty()) {
        std::cout << myStack.top() << " "; // Виводимо верхній елемент стеку
        myStack.pop(); // Видаляємо верхній елемент стеку
    }

    std::cout << "\n";


    std::cout << "Even numbers in the stack:\n";
    while (!evenStack.empty()) {
        std::cout << evenStack.top() << " ";
        evenStack.pop();
    }
    std::cout << "\n";

    std::cout << "Odd numbers in the stack:\n";
    while (!oddStack.empty()) {
        std::cout << oddStack.top() << " ";
        oddStack.pop();
    }
    std::cout << "\n";

}

bool isBalanced(const std::string& sequence) {
    std::stack<char> charStack;

    for (char c : sequence) {
        if (c == '(' || c == '[') {
            charStack.push(c);
        } else if (c == ')' || c == ']') {
            if (charStack.empty()) {
                return false; // Дужка, яка закривається, без відповідної відкриваючої
            }

            char top = charStack.top();
            charStack.pop();

            if ((c == ')' && top != '(') || (c == ']' && top != '[')) {
                return false; // Неправильна парність дужок
            }
        }
    }

    return charStack.empty(); // Перевіряємо, чи стек порожній в кінці
}

void thirdEx(){
    std::string sequence;
    std::cout << "Enter a sequence of parentheses: ";
    std::cin >> sequence;

    if (isBalanced(sequence)) {
        std::cout << "The sequence is correct.\n";
    } else {
        std::cout << "The sequence is incorrect.\n";
    }
}

int main() {
    std::cout << "Enter number of exercise: ";
    int i;
    std::cin >> i;

    switch (i) {
        case 1:
            firstEx();
            break;
        case 2:
            thirdEx();
            break;
        default:
            std::cout << "Error numder" << std::endl;
    }

    return 0;
}

