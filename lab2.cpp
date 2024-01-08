#include <iostream>
#include <string>
#include <list>
#include <sstream>

void firstEx() {
    std::list<int> numbers;
    int num;

    std::cout << "Enter whole numbers (enter 0 to complete the entry):\n";

    while (true) {
        std::cin >> num;
        if (num == 0) {
            break;
        }
        numbers.push_back(num);
    }

    std::cout << "List of numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
}

void seccondEx(){
    std::string input;
    std::cout << "Enter the line: ";
    std::cin >> input;

    std::list<char> charList(input.begin(), input.end());

    std::cout << "List of characters: ";
    for (const char& c : charList) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
}

void thirdEx(){
    std::string input;
    std::cout << "Enter the line: ";
    std::cin.ignore();
    std::getline(std::cin, input);

    std::list<std::string> atomList;
    std::istringstream iss(input);
    std::string atom;

    while (iss >> atom) {
        atomList.push_back(atom);
    }

    std::cout << "List of atoms: ";
    for (const std::string& a : atomList) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
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
        std::string first_name;
        std::string last_name;
        Date birth_date;
        Job job;
    };

    struct FamilyMember {
        Person person;
    };

    struct Family {
        Person husband;
        Person wife;
        std::list<FamilyMember> children;
    };

    Family createFamilyFromInput() {
        Family newFamily;

        // Ввод информации о муже
        std::cout << "Enter husband's first name: ";
        std::cin >> newFamily.husband.first_name;
        std::cout << "Enter husband's last name: ";
        std::cin >> newFamily.husband.last_name;
        std::cout << "Enter husband's birth date (day month year): ";
        std::cin >> newFamily.husband.birth_date.day >> newFamily.husband.birth_date.month >> newFamily.husband.birth_date.year;
        std::cout << "Is the husband unemployed? (1 for yes, 0 for no): ";
        std::cin >> newFamily.husband.job.unemployed;
        if (!newFamily.husband.job.unemployed) {
            std::cout << "Enter husband's salary: ";
            std::cin >> newFamily.husband.job.salary;
        }

        // Ввод информации о жене
        std::cout << "Enter wife's first name: ";
        std::cin >> newFamily.wife.first_name;
        std::cout << "Enter wife's last name: ";
        std::cin >> newFamily.wife.last_name;
        std::cout << "Enter wife's birth date (day month year): ";
        std::cin >> newFamily.wife.birth_date.day >> newFamily.wife.birth_date.month >> newFamily.wife.birth_date.year;
        std::cout << "Is the wife unemployed? (1 for yes, 0 for no): ";
        std::cin >> newFamily.wife.job.unemployed;
        if (!newFamily.wife.job.unemployed) {
            std::cout << "Enter wife's salary: ";
            std::cin >> newFamily.wife.job.salary;
        }

        // Ввод информации о детях
        int numChildren;
        std::cout << "Enter the number of children: ";
        std::cin >> numChildren;

        for (int i = 0; i < numChildren; i++) {
            FamilyMember child;
            std::cout << "Enter child #" << i + 1 << "'s first name: ";
            std::cin >> child.person.first_name;
            std::cout << "Enter child #" << i + 1 << "'s last name: ";
            std::cin >> child.person.last_name;
            std::cout << "Enter child #" << i + 1 << "'s birth date (day month year): ";
            std::cin >> child.person.birth_date.day >> child.person.birth_date.month >> child.person.birth_date.year;
            child.person.job.unemployed = true; // Предполагаем, что дети без работы
            newFamily.children.push_back(child);
        }

        return newFamily;
    }

    void removeFamily(std::list<Family>& families, int index) {
        if (index >= 0 && index < families.size()) {
            auto it = families.begin();
            std::advance(it, index);
            families.erase(it);
            std::cout << "Family at index " << index << " removed!" << std::endl;
        } else {
            std::cout << "Invalid index for family removal." << std::endl;
        }
    }

void familyEx() {
    // Створення бази даних родин
    std::list<Family> families;

    // Додавання родин до бази даних
    families.push_back({{"Ivan",  "Petrov",  {1,       5,         1980}, {false, 1234}},
                        {"Olena", "Petrova", {10,      9,         1982}, {true,  0}},
                        {{"Anna", "Petrova", {15, 3, 2005}, {0}},
                                  {"Pavlo", "Petrova", {20, 7, 2009}, {0}},
                                             {"Maria", "Petrova", {3, 12, 2014}, {0}}}});

    families.push_back({{"Maxim", "Ivanov",  {3,  8, 1975}, {false, 4567}},
                        {"Irina", "Ivanova", {18, 6, 1980}, {false, 3513}},
                        {{"Oleg", "Ivanov", {25, 2, 2008}, {0}},
                                  {"Darina", "Ivanova", {10, 11, 2012}, {0}}}});

    families.push_back({{"Alex",    "Volkov",  {3,        8,        1975}, {false, 4567}},
                        {"Natalia", "Volkova", {18,       6,        1980}, {true,  0}},
                        {{"Kirill", "Volkov", {25, 2, 2008}, {0}},
                                    {"Darina", "Volkov", {10, 11, 2012}, {0}},
                                               {"Nikita", "Volkov", {23, 5, 2015}, {0}}}});

    while (true) {
        int i = 0;
        std::cout << std::endl;
        std::cout << "Select:" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Show all families" << std::endl;
        std::cout << "2. Add new family" << std::endl;
        std::cout << "3. Delete family" << std::endl;
        std::cout << "4. Show families with three children" << std::endl;
        std::cout << "5. Show women with three children" << std::endl;
        std::cout << "6. Show names and surnames of all people from the database" << std::endl;
        std::cout << "7. Show working wifes" << std::endl;
        std::cout << "8. Show surnames of people with an income of less than 1000" << std::endl;
        std::cin >> i;
        if (i == 0){
            break;
        }
        else if (i == 1) {
            int familyNumber = 1;
            for (const Family &family: families) {
                // Вивід інформації о семье (муж, жена, діти)
                std::cout << "Family #" << familyNumber << std::endl;
                std::cout << "Husband: " << family.husband.first_name << " " << family.husband.last_name << std::endl;
                std::cout << "Wife: " << family.wife.first_name << " " << family.wife.last_name << std::endl;
                std::cout << "Children:" << std::endl;
                for (const FamilyMember &child: family.children) {
                    std::cout << "  " << child.person.first_name << " " << child.person.last_name << std::endl;
                }
                std::cout << std::endl;
                familyNumber++;
            }
        } else if (i == 2) {
            Family newFamily = createFamilyFromInput();
            families.push_back(newFamily);
            std::cout << "New family added!" << std::endl;
        } else if (i == 3) {
            int indexToRemove;
            std::cout << "Enter the index of the family you want to remove: ";
            std::cin >> indexToRemove;

            removeFamily(families, indexToRemove);
        } else if (i == 4) {
            // Запит A: Знайти всі родини з трьома дітьми
            std::cout << "Families with three children:" << std::endl;
            for (const Family &family: families) {
                if (family.children.size() == 3) {
                    std::cout << family.husband.first_name << " " << family.husband.last_name << " and "
                              << family.wife.first_name << " " << family.wife.last_name << std::endl;
                }
            }
            std::cout << std::endl;
        } else if (i == 5) {
            // Запит Б: Знайти імена і прізвища жінок з трьома дітьми
            std::cout << "Women with three children:" << std::endl;
            for (const Family &family: families) {
                if (family.children.size() == 3) {
                    std::cout << family.wife.first_name << " " << family.wife.last_name << std::endl;
                }
            }
            std::cout << std::endl;
        } else if (i == 6) {
            // Запит A: Знайти імена й прізвища всіх людей з бази даних
            std::cout << "Names and surnames of all people from the database:" << std::endl;
            for (const Family &family: families) {
                std::cout << family.husband.first_name << " " << family.husband.last_name << std::endl;
                std::cout << family.wife.first_name << " " << family.wife.last_name << std::endl;
                for (const FamilyMember &child: family.children) {
                    std::cout << child.person.first_name << " " << child.person.last_name << std::endl;
                }
            }
            std::cout << std::endl;
        } else if (i == 7) {
            // Запит Б: Знайти всіх працюючих дружин
            std::cout << "Working wifes:" << std::endl;
            for (const Family &family: families) {
                if (!family.wife.job.unemployed) {
                    std::cout << family.wife.first_name << " " << family.wife.last_name << std::endl;
                }
            }
            std::cout << std::endl;
        } else if (i == 8) {
            // Запит В: Знайти прізвища людей, чий дохід менше ніж 1000
            std::cout << "Surnames of people with an income of less than 1000:" << std::endl;
            for (const Family &family: families) {
                if (family.husband.job.salary < 1000) {
                    std::cout << family.husband.last_name << std::endl;
                }
                if (!family.wife.job.unemployed && family.wife.job.salary < 1000) {
                    std::cout << family.wife.last_name << std::endl;
                }
                for (const FamilyMember &child: family.children) {
                    if (child.person.job.salary < 1000) {
                        std::cout << child.person.last_name << std::endl;
                    }
                }
            }
        }
        else {
            std::cout << "Error number";
        }
    }
}
    struct TeamResult {
    std::string name;
    int points;
    };

void sixthEx(){
    std::list<TeamResult> results;

    // Додавання результатів команди
    results.push_back({"Shakhtar", 78});
    results.push_back({"Dynamo", 70});
    results.push_back({"Zorya", 65});
    results.push_back({"Dnipro", 61});
    results.push_back({"Vorskla", 56});
    results.push_back({"Carpathians", 54});
    results.push_back({"Olympic", 52});
    results.push_back({"Mariupol", 48});
    results.push_back({"Rostov", 45});
    results.push_back({"Dynamo2", 42});

    // Розрахунок суми балів
    int sum = 0;
    for (const TeamResult& result : results) {
        sum += result.points;
    }

    // Розрахунок середнього значення балів
    double average = static_cast<double>(sum) / results.size();

    // Display the results
    std::cout << "Sum of points of ten teams: " << sum << std::endl;
    std::cout << "Average points of ten teams: " << average << std::endl;
}


int main(){
    int i = 0;
    std::cout << "Enter the exercise:";
    std::cin >> i;
    while (true){
        if (i == 1){
            firstEx();
        }
        else if (i == 2){
            seccondEx();
        }
        else if (i == 3){
            thirdEx();
        }
        else if (i == 4){
            familyEx();
        }
        else if (i == 5){
            sixthEx();
        }
        else{
            std::cout << "Error number";
        }
    }
}
