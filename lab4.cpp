#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <sstream>
#include <cctype>

using namespace std;

deque<int> myDeque;

void printDeque() {
    if (myDeque.empty()) {
        cout << "Deque is empty." << endl;
    }
    else {
        cout << "Current state of the deque: ";
        for (int element : myDeque) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void firstEx() {

    while (true) {
        int choice;
        cout << "Choose an option:" << endl;
        cout << "1. Add an element to the front of the deque" << endl;
        cout << "2. Add an element to the end of the deque" << endl;
        cout << "3. Remove an element from the front of the deque" << endl;
        cout << "4. Remove an element from the end of the deque" << endl;
        cout << "5. Print the current state of the deque" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;
        int value;
        string input;

        switch (choice) {
        case 1:
            cout << "Enter an integer to add to the front of the deque: ";

            cin>>input;

            while (!(istringstream(input) >> value)) {
                cout << "Input is not an integer. Please try again: ";
                cin >> input;
            }
    
            myDeque.push_front(value);
            break;

        case 2:
            cout << "Enter an integer to add to the end of the deque: ";

            cin >> input;

            while (!(istringstream(input) >> value)) {
                cout << "Input is not an integer. Please try again: ";
                cin >> input;
            }

            myDeque.push_back(value);
            break;

        case 3:
            if (!myDeque.empty()) {
                myDeque.pop_front();
            }
            else {
                cout << "Error: The deque is empty; there are no elements to remove." << endl;
            }
            break;

        case 4:
            if (!myDeque.empty()) {
                myDeque.pop_back();
            }
            else {
                cout << "Error: The deque is empty; there are no elements to remove." << endl;
            }
            break;

        case 5:
            printDeque();
            break;

        case 6:
            cout << "Program exited." << endl;
            break;

        default:
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

bool isPalindrome(const std::string& str) {
    int left = 0;
    int right = str.length() - 1;

    while (left < right) {
        // Ignore non-letter characters
        while (left < right && !isalpha(str[left])) {
            left++;
        }
        while (left < right && !isalpha(str[right])) {
            right--;
        }

        // Compare characters, ignoring case
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

void seccondEx() {
    string input;
    cout << "Enter the string: ";
    cin >> input;

    if (isPalindrome(input)) {
        cout << "This string is a palindrome." << endl;
    }
    else {
        cout << "This string is not a palindrome." << endl;
    }
}


struct Date {
    int day;
    int month;
    int year;
};

struct Job {
    bool unemployed;
    int salary;
};

struct Person {
    string first_name;
    string last_name;
    Date birth_date;
    Job job;
};

struct FamilyMember {
    Person person;
};

struct Family {
    Person husband;
    Person wife;
    queue<FamilyMember> children; // Using queue instead of list
};

Family createFamilyFromInput() {
    Family newFamily;

    // Input information about husband
    cout << "Enter husband's first name: ";
    cin >> newFamily.husband.first_name;
    cout << "Enter husband's last name: ";
    cin >> newFamily.husband.last_name;
    cout << "Enter husband's birth date (day month year): ";
    cin >> newFamily.husband.birth_date.day >> newFamily.husband.birth_date.month >> newFamily.husband.birth_date.year;
    cout << "Is the husband unemployed? (1 for yes, 0 for no): ";
    cin >> newFamily.husband.job.unemployed;
    if (!newFamily.husband.job.unemployed) {
        cout << "Enter husband's salary: ";
        cin >> newFamily.husband.job.salary;
    }

    // Input information about wife
    cout << "Enter wife's first name: ";
    cin >> newFamily.wife.first_name;
    cout << "Enter wife's last name: ";
    cin >> newFamily.wife.last_name;
    cout << "Enter wife's birth date (day month year): ";
    cin >> newFamily.wife.birth_date.day >> newFamily.wife.birth_date.month >> newFamily.wife.birth_date.year;
    cout << "Is the wife unemployed? (1 for yes, 0 for no): ";
    cin >> newFamily.wife.job.unemployed;
    if (!newFamily.wife.job.unemployed) {
        cout << "Enter wife's salary: ";
        cin >> newFamily.wife.job.salary;
    }

    // Input information about children
    int numChildren;
    cout << "Enter the number of children: ";
    cin >> numChildren;

    for (int i = 0; i < numChildren; i++) {
        FamilyMember child;
        cout << "Enter child #" << i + 1 << "'s first name: ";
        cin >> child.person.first_name;
        cout << "Enter child #" << i + 1 << "'s last name: ";
        cin >> child.person.last_name;
        cout << "Enter child #" << i + 1 << "'s birth date (day month year): ";
        cin >> child.person.birth_date.day >> child.person.birth_date.month >> child.person.birth_date.year;
        child.person.job.unemployed = true; // Assuming children are unemployed
        newFamily.children.push(child);
    }

    return newFamily;
}

void removeHusbandByName(queue<Family>& families, const string& targetFirstName, const string& targetLastName) {
    bool found = false;

    // Temporary queue to store families that are not being modified
    queue<Family> tempQueue;

    // Search for the family with the specified husband's first and last names
    while (!families.empty()) {
        if (families.front().husband.first_name == targetFirstName &&
            families.front().husband.last_name == targetLastName) {
            // Family found, modify the family (remove husband)
            found = true;
            Family modifiedFamily = families.front();
            modifiedFamily.husband = {};  // Reset the husband's information
            tempQueue.push(modifiedFamily);
            cout << "Husband " << targetFirstName << " " << targetLastName << " removed from the family!" << endl;
        }
        else {
            // Family not found or found and modified, add it to tempQueue
            tempQueue.push(families.front());
        }

        // Move to the next family
        families.pop();
    }

    // Restore the families from tempQueue back to families
    while (!tempQueue.empty()) {
        families.push(tempQueue.front());
        tempQueue.pop();
    }

    if (!found) {
        cout << "Family with husband " << targetFirstName << " " << targetLastName << " not found." << endl;
    }
}

void removeWifeByName(queue<Family>& families, const string& targetFirstName, const string& targetLastName) {
    bool found = false;

    // Temporary queue to store families that are not being modified
    queue<Family> tempQueue;

    // Search for the family with the specified husband's first and last names
    while (!families.empty()) {
        if (families.front().wife.first_name == targetFirstName &&
            families.front().wife.last_name == targetLastName) {
            // Family found, modify the family (remove husband)
            found = true;
            Family modifiedFamily = families.front();
            modifiedFamily.wife = {};  // Reset the husband's information
            tempQueue.push(modifiedFamily);
            cout << "Wife " << targetFirstName << " " << targetLastName << " removed from the family!" << endl;
        }
        else {
            // Family not found or found and modified, add it to tempQueue
            tempQueue.push(families.front());
        }

        // Move to the next family
        families.pop();
    }

    // Restore the families from tempQueue back to families
    while (!tempQueue.empty()) {
        families.push(tempQueue.front());
        tempQueue.pop();
    }

    if (!found) {
        cout << "Family with wife " << targetFirstName << " " << targetLastName << " not found." << endl;
    }
}

void removeChildFromFamily(queue<Family>& families, const string& targetFirstName, const string& targetLastName) {
    bool found = false;

    // Temporary queue to store families that are not being modified
    queue<Family> tempQueue;

    // Search for the family with the specified child's first and last names
    while (!families.empty()) {
        Family currentFamily = families.front();
        Family modifiedFamily;

        // Search for the child with the specified first and last names
        queue<FamilyMember> tempChildren;
        while (!currentFamily.children.empty()) {
            FamilyMember currentChild = currentFamily.children.front();
            if (currentChild.person.first_name == targetFirstName &&
                currentChild.person.last_name == targetLastName) {
                // Child found, skip this child
                found = true;
                cout << "Child " << targetFirstName << " " << targetLastName << " removed from the family!" << endl;
            }
            else {
                // Child not found, add it to tempChildren
                tempChildren.push(currentChild);
            }
            currentFamily.children.pop();
        }

        // Restore the children back to the family
        while (!tempChildren.empty()) {
            modifiedFamily.children.push(tempChildren.front());
            tempChildren.pop();
        }

        // Add the modified family to tempQueue
        modifiedFamily.husband = currentFamily.husband;
        modifiedFamily.wife = currentFamily.wife;
        tempQueue.push(modifiedFamily);

        // Move to the next family
        families.pop();
    }

    // Restore the families from tempQueue back to families
    while (!tempQueue.empty()) {
        families.push(tempQueue.front());
        tempQueue.pop();
    }

    if (!found) {
        cout << "Child " << targetFirstName << " " << targetLastName << " not found." << endl;
    }
}


void removeFamily(queue<Family>& families, int index) {
    if (index >= 0 && index < families.size()) {
        for (int i = 0; i < index; i++) {
            families.push(families.front());
            families.pop();
        }
        families.pop();
        cout << "Family at index " << index << " removed!" << endl;
    }
    else {
        cout << "Invalid index for family removal." << endl;
    }
}

void thirdEx() {
    // Creating a database of families
    queue<Family> families;

    Family newFamily1{
    {"Sergey", "Putintsev", {19, 06, 1956}, {false, 20000}},
    {"Anna", "Putintsev", {19, 9, 1954}, {false, 15000}}
    };
    newFamily1.children.push({ "Sergey", "Putintsev", {28, 8, 1975}, {false, 20000} });
    newFamily1.children.push({ "Alexandr", "Putintsev", {24, 1, 1972}, {true, 0} });

    Family newFamily2{
    {"Anatoliy", "Voronkov", {19, 06, 1956}, {false, 20000}},
    {"Olga", "Voronkova", {19, 9, 1954}, {false, 15000}}
    };
    newFamily2.children.push({ "Tatyana", "Voronkova", {8, 3, 1980}, {false, 20000} });
    newFamily2.children.push({ "Vera", "Voronkova", {24, 1, 1972}, {true, 0} });

    Family newFamily3{
    {"Sergey", "Putintsev", {19, 06, 1956}, {false, 20000}},
    { "Tatyana", "Voronkova", {8, 3, 1980}, {false, 20000} }
    };
    newFamily3.children.push({ "Kirill", "Putintsev", {22, 1, 2005}, {true, 0} });


    families.push(newFamily1);
    families.push(newFamily2);
    families.push(newFamily3);
 

    while (true) {
        int i = 0;
        cout << endl;
        cout << "Select:" << endl;
        cout << "0. Exit" << endl;
        cout << "1. Show all families" << endl;
        cout << "2. Add new family" << endl;
        cout << "3. Delete family" << endl;
        cout << "4. Delete husband from family" << endl;
        cout << "5. Delete wife from family" << endl;
        cout << "6. Delete child from family" << endl;
        cin >> i;

        if (i == 0) {
            break;
        }
        else if (i == 1) {
            int familyNumber = 1;
            queue<Family> tempFamilies = families; // Create a copy of the original queue
            while (!tempFamilies.empty()) {
                const Family& family = tempFamilies.front();
                // Output information about the family (husband, wife, children)
                cout << "Family #" << familyNumber << endl;
                cout << "Husband: " << family.husband.first_name << " " << family.husband.last_name << endl;
                cout << "Wife: " << family.wife.first_name << " " << family.wife.last_name << endl;
                cout << "Children:" << endl;
                queue<FamilyMember> tempChildren = family.children;
                while (!tempChildren.empty()) {
                    const FamilyMember& child = tempChildren.front();
                    cout << "  " << child.person.first_name << " " << child.person.last_name << endl;
                    tempChildren.pop();
                }
                cout << endl;
                familyNumber++;
                tempFamilies.pop();
            }
        }
        else if (i == 2) {
            Family newFamily = createFamilyFromInput();
            families.push(newFamily);
            cout << "New family added!" << endl;
        }
        else if (i == 3) {
            int indexToRemove;
            cout << "Enter the index of the family you want to remove: ";
            cin >> indexToRemove;

            removeFamily(families, indexToRemove);
        }
        else if (i == 4) {
            // Input information about the family to be removed
            string targetFirstName, targetLastName;
            cout << "Enter the first name of the father to remove: ";
            cin >> targetFirstName;
            cout << "Enter the last name of the father to remove: ";
            cin >> targetLastName;

            // Call the removeFamilyByName function
            removeHusbandByName(families, targetFirstName, targetLastName);
        }
        else if (i == 5) {
            // Input information about the family to be removed
            string targetFirstName, targetLastName;
            cout << "Enter the first name of the father to remove: ";
            cin >> targetFirstName;
            cout << "Enter the last name of the father to remove: ";
            cin >> targetLastName;

            // Call the removeFamilyByName function
            removeWifeByName(families, targetFirstName, targetLastName);
        }
        else if (i == 6) {
            string targetFirstName, targetLastName;
            cout << "Enter the first name of the child to remove: ";
            cin >> targetFirstName;
            cout << "Enter the last name of the child to remove: ";
            cin >> targetLastName;

            removeChildFromFamily(families, targetFirstName, targetLastName);
        }
        else {
            cout << "Error number";
        }
    }
}

// A structure to represent a queue element
struct QueueNode {
    int data;
    QueueNode* next;
};

// Class to represent the queue
class Queue {
public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Adding an element to the queue
    void enqueue(int value) {
        QueueNode* newNode = new QueueNode;
        newNode->data = value;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Display queue elements
    void display() {
        QueueNode* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

private:
    QueueNode* front;
    QueueNode* rear;
};

void fourthEx() {
    Queue queue;
    int numb;

    // Adding 5 elements to the queue
    for (int i = 1; i <= 5; i++) {
        cin >> numb;
        queue.enqueue(numb);
    }

    cout << "Queue elements: ";
    queue.display();
}

int main() {  
    int i = 0;
    cout << "Enter the exercise:";
    cin >> i;

    while (true) {
        switch (i) {
        case 1: firstEx();
        case 2: seccondEx();
        case 3: thirdEx();
        case 4: fourthEx();
        default:
            cout << "Error number";
            break;
        }
    }
    return 0;
}
