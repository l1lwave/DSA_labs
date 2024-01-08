#include <iostream>
#include <climits>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <fstream>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        root = insertRec(root, val);
    }

    const TreeNode* search(int val) const {
        return searchRec(root, val);
    }

    int findMax() const {
        return findMaxRec(root);
    }

    void deleteNode(int val) {
        root = deleteNodeRec(root, val);
    }

    const TreeNode* getRoot() const {
        return root;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

private:
    TreeNode* insertRec(TreeNode* root, int val) {
        if (!root)
            return new TreeNode(val);

        if (val < root->data)
            root->left = insertRec(root->left, val);
        else if (val > root->data)
            root->right = insertRec(root->right, val);

        return root;
    }

    const TreeNode* searchRec(const TreeNode* root, int val) const {
        if (!root || root->data == val)
            return root;

        if (val < root->data)
            return searchRec(root->left, val);
        else
            return searchRec(root->right, val);
    }

    int findMaxRec(const TreeNode* root) const {
        if (!root)
            return INT_MIN;

        if (!root->right)
            return root->data;

        return findMaxRec(root->right);
    }

    TreeNode* deleteNodeRec(TreeNode* root, int val) {
        if (!root)
            return root;

        if (val < root->data)
            root->left = deleteNodeRec(root->left, val);
        else if (val > root->data)
            root->right = deleteNodeRec(root->right, val);
        else {
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNodeRec(root->right, temp->data);
        }

        return root;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }
};

// Функція для виведення дерева на екран
void printTree(const TreeNode* root, int space = 0) {
    if (!root)
        return;

    space += 5;

    printTree(root->right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++)
        std::cout << " ";
    std::cout << std::setw(2) << root->data << "\n";
    printTree(root->left, space);
}

void firstEx() {
    BinarySearchTree bst;

    std::cout << "How long is your Tree: ";
    int i;
    if (!(std::cin >> i)) {
        std::cout << "Error: Invalid input. Please enter only integers.\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
    }
    else {
        // Тест 1: Перевірка правильності введення і виведення даних
        std::cout << "Enter numbers to insert into the Binary Search Tree:\n";
        int num;
        bool inputError = true;


        for (int j = 0; j < i; j++) {
            if (!(std::cin >> num)) {
                std::cout << "Error: Invalid input. Please enter only integers.\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
            else {
                bst.insert(num);
                inputError = false;
            }

        }
        if (!inputError) {
            // Виведення дерева
            std::cout << "Binary Search Tree:\n";
            printTree(bst.getRoot());

            // Знаходження вершини з заданим числом
            int target;
            std::cout << "Enter a number to search in the tree: ";
            if (std::cin >> target) {
                const TreeNode* result = bst.search(target);
                if (result)
                    std::cout << "Node with value " << target << " found in the tree.\n";
                else
                    std::cout << "Node with value " << target << " not found in the tree.\n";
            }
            else {
                std::cerr << "Invalid input.\n";
            }

            // Знаходження максимального елемента
            std::cout << "Max element in the tree: " << bst.findMax() << std::endl;
        }
        else {
            std::cerr << "Tree is empty.\n";
        }
    }
}

    class CharTreeNode {
    public:
        char data;
        std::vector<char> duplicates;
        CharTreeNode* left;
        CharTreeNode* right;

        CharTreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
    };

    class CharBinarySearchTree {
    private:
        CharTreeNode* root;
        void findAndRemoveDuplicates(CharTreeNode* root);
    public:
        CharBinarySearchTree() : root(nullptr) {}

        void insert(char val) {
            root = insertRec(root, val);
        }

        const CharTreeNode* search(char val) const {
            return searchRec(root, val);
        }

        void deleteNode(char val) {
            root = deleteNodeRec(root, val);
        }

        const CharTreeNode* getRoot() const {
            return root;
        }

        bool isEmpty() const {
            return root == nullptr;
        }

        void printTree() const {
            printTree(root);
        }

        void printPostorder() const {
            printPostorder(root);
        }

        void findAndRemoveDuplicates() {
            findAndRemoveDuplicates(root);
        }

    private:
        CharTreeNode* insertRec(CharTreeNode* root, char val) {
            if (!root)
                return new CharTreeNode(val);

            if (val == root->data) {
                root->duplicates.push_back(val);
            }
            else if (val < root->data) {
                root->left = insertRec(root->left, val);
            }
            else {
                root->right = insertRec(root->right, val);
            }

            return root;
        }

        const CharTreeNode* searchRec(const CharTreeNode* root, char val) const {
            if (!root)
                return nullptr;

            if (val == root->data)
                return root;

            if (val < root->data)
                return searchRec(root->left, val);
            else
                return searchRec(root->right, val);
        }

        CharTreeNode* deleteNodeRec(CharTreeNode* root, char val) {
            if (!root)
                return root;

            if (val == root->data) {
                if (!root->duplicates.empty()) {
                    root->duplicates.pop_back();
                }
                else {
                    CharTreeNode* temp = minValueNode(root->right);
                    root->data = temp->data;
                    root->right = deleteNodeRec(root->right, temp->data);
                }
            }
            else if (val < root->data) {
                root->left = deleteNodeRec(root->left, val);
            }
            else {
                root->right = deleteNodeRec(root->right, val);
            }

            return root;
        }

        CharTreeNode* minValueNode(CharTreeNode* node) {
            CharTreeNode* current = node;
            while (current->left)
                current = current->left;
            return current;
        }

        void printTree(const CharTreeNode* root, int space = 0) const {
            if (!root)
                return;

            space += 5;

            printTree(root->right, space);
            std::cout << std::endl;
            for (int i = 5; i < space; i++)
                std::cout << " ";
            std::cout << std::setw(2) << root->data;
            if (!root->duplicates.empty()) {
                std::cout << " (";
                for (char ch : root->duplicates) {
                    std::cout << ch << " ";
                }
                std::cout << ")";
            }
            std::cout << "\n";
            printTree(root->left, space);
        }

        void printPostorder(const CharTreeNode* root) const {
            if (root) {
                printPostorder(root->left);
                printPostorder(root->right);
                std::cout << root->data << " ";
                for (char ch : root->duplicates) {
                    std::cout << ch << " ";
                }
            }
        }

    };

    void CharBinarySearchTree::findAndRemoveDuplicates(CharTreeNode* root) {
        if (root) {
            findAndRemoveDuplicates(root->left);
            findAndRemoveDuplicates(root->right);

            if (!root->duplicates.empty()) {
                // If duplicates are found, remove them from the tree
                for (char ch : root->duplicates) {
                    root = deleteNodeRec(root, ch);
                }
            }
        }
    }



    void seccondEx() {
        CharBinarySearchTree charBST;

        std::cout << "Enter a string of characters to build a Binary Search Tree:\n";

        std::cin >> std::ws; 
        std::string input;
        std::getline(std::cin, input);  

        for (char ch : input) {
            charBST.insert(ch);
        }

        std::cout << "Binary Search Tree:\n";
        charBST.printTree();

        std::cout << "\nCharacters that appear more than once:\n";
        charBST.findAndRemoveDuplicates();

        std::cout << "Binary Search Tree:\n";
        charBST.printTree();
        std::cout << std::endl;
    }


    class WordTreeNode {
    public:
        std::string data;
        WordTreeNode* left;
        WordTreeNode* right;
        WordTreeNode(const std::string& value) : data(value), left(nullptr), right(nullptr) {}
    };

    class WordSearchTree {
    public:
        WordSearchTree() : root(nullptr) {}

        void Insert(const std::string& value) {
            root = InsertRecursive(root, value);
        }

        void PrintTree() {
            PrintTreeRecursive(root, 0);
        }

        int CountWordsStartingWith(char letter) {
            return CountWordsStartingWithRecursive(root, letter);
        }

        void RemoveWordsStartingWith(char letter) {
            root = RemoveWordsStartingWithRecursive(root, letter);
        }

    private:
        WordTreeNode* root;

        WordTreeNode* InsertRecursive(WordTreeNode* node, const std::string& value) {
            if (node == nullptr) {
                return new WordTreeNode(value);
            }
            if (value < node->data) {
                node->left = InsertRecursive(node->left, value);
            }
            else if (value > node->data) {
                node->right = InsertRecursive(node->right, value);
            }
            return node;
        }

        void PrintTreeRecursive(WordTreeNode* node, int level) {
            if (node == nullptr) {
                return;
            }
            PrintTreeRecursive(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                std::cout << "    ";
            }
            std::cout << node->data << "\n";
            PrintTreeRecursive(node->left, level + 1);
        }

        int CountWordsStartingWithRecursive(WordTreeNode* node, char letter) {
            if (node == nullptr) {
                return 0;
            }
            int count = 0;
            if (node->data.front() == letter) {
                count = 1;
            }
            count += CountWordsStartingWithRecursive(node->left, letter);
            count += CountWordsStartingWithRecursive(node->right, letter);
            return count;
        }

        WordTreeNode* RemoveWordsStartingWithRecursive(WordTreeNode* node, char letter) {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->data.front() == letter) {
                // Remove this node and reorganize the tree
                WordTreeNode* left = node->left;
                WordTreeNode* right = node->right;
                delete node;

                if (right == nullptr) {
                    return left;
                }

                WordTreeNode* minNode = FindMin(right);
                minNode->right = RemoveMin(right);
                minNode->left = left;

                return BalanceTree(minNode);
            }

            if (node->data.front() < letter) {
                node->right = RemoveWordsStartingWithRecursive(node->right, letter);
            }
            else {
                node->left = RemoveWordsStartingWithRecursive(node->left, letter);
            }

            return BalanceTree(node);
        }

        WordTreeNode* FindMin(WordTreeNode* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        WordTreeNode* RemoveMin(WordTreeNode* node) {
            if (node->left == nullptr) {
                return node->right;
            }
            node->left = RemoveMin(node->left);
            return BalanceTree(node);
        }

        WordTreeNode* BalanceTree(WordTreeNode* node) {
            // Implement tree balancing logic here (e.g., AVL or Red-Black balancing)
            return node;
        }
    };

    void thirdEx() {
        std::ofstream file("words.txt");

        if (!file) {
            std::cerr << "Failed to open the file." << std::endl;
        }

        file << "Mother" << std::endl;
        file << "Father" << std::endl;
        file << "brother" << std::endl;
        file << "sister" << std::endl;
        file << "grandma" << std::endl;
        file << "grandpa" << std::endl;

        file.close();

        WordSearchTree tree;  // Change BinarySearchTree to WordSearchTree

        std::ifstream inputFile("words.txt");
        if (!inputFile) {
            std::cerr << "Failed to open the file." << std::endl;
        }

        std::string word;
        while (inputFile >> word) {
            tree.Insert(word);
        }

        std::cout << "Word Search Tree:" << std::endl;
        tree.PrintTree();

        char letterToSearch = 'b';
        int wordCount = tree.CountWordsStartingWith(letterToSearch);
        std::cout << "Number of words starting with '" << letterToSearch << "': " << wordCount << std::endl;

        tree.RemoveWordsStartingWith(letterToSearch);

        std::cout << "Updated tree after removing words starting with '" << letterToSearch << "':" << std::endl;
        tree.PrintTree();
    }

    int main() {
        int a;
        while (true)
        {
            std::cout << "Enter the exercise: ";
            if (!(std::cin >> a)) {
                std::cout << "Error: Invalid input. Please enter only integers.\n";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
            else {
                if (a == 1) {
                    firstEx();
                }
                else if (a == 2) {
                    seccondEx();
                }
                else if (a == 3) {
                    thirdEx();
                }
                else {
                    std::cout << "Error: Invalid input.\n";
                }
            }
        }
    }
