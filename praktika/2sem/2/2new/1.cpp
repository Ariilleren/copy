#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Node class for singly linked list
template <typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList class
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    string filename;
    
public:
    // Constructor
    LinkedList() : head(nullptr), filename("") {}
    
    // Copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), filename(other.filename) {
        Node<T>* current = other.head;
        Node<T>* last = nullptr;
        
        while (current != nullptr) {
            Node<T>* newNode = new Node<T>(current->data);
            
            if (last == nullptr) {
                head = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            current = current->next;
        }
    }
    
    // Destructor
    ~LinkedList() {
        clear();
    }
    
    // Clear list
    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    
    // Add element to the end
    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    // Display list
    void display() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Get list size
    int size() {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    // Get element by index
    T getAt(int index) {
        if (index < 0 || head == nullptr) {
            throw out_of_range("Index out of range");
        }
        
        Node<T>* current = head;
        int i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            i++;
        }
        
        if (current == nullptr) {
            throw out_of_range("Index out of range");
        }
        
        return current->data;
    }
    
    // Save list to file
    bool saveToFile(const string& fname) {
        ofstream file(fname);
        if (!file.is_open()) {
            return false;
        }
        
        Node<T>* current = head;
        while (current != nullptr) {
            file << current->data << endl;
            current = current->next;
        }
        
        file.close();
        filename = fname;
        return true;
    }
    
    // Load list from file
    bool loadFromFile(const string& fname) {
        ifstream file(fname);
        if (!file.is_open()) {
            return false;
        }
        
        clear();
        T value;
        while (file >> value) {
            pushBack(value);
        }
        
        file.close();
        filename = fname;
        return true;
    }
    
    // Check if this list contains all elements of list1 in the same order
    bool containsInOrder(LinkedList<T>& list1) {
        if (list1.head == nullptr) {
            return true;  // Empty list is always contained
        }
        
        if (head == nullptr) {
            return false;  // This list is empty but list1 is not
        }
        
        Node<T>* current1 = list1.head;
        Node<T>* current2 = head;
        
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data == current2->data) {
                // Match found, move both pointers
                current1 = current1->next;
                current2 = current2->next;
            } else {
                // No match, move only second list pointer
                current2 = current2->next;
            }
        }
        
        // If we reached the end of first list, all elements were found in order
        return current1 == nullptr;
    }
};

// Clear screen function

// Pause function
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Main menu
void showMenu() {
    cout << "======================================" << endl;
    cout << "    LIST CONTAINMENT CHECK            " << endl;
    cout << "======================================" << endl;
    cout << "1. Load data from files" << endl;
    cout << "2. Input data from keyboard" << endl;
    cout << "3. Select storage mode" << endl;
    cout << "4. Perform check" << endl;
    cout << "5. Show lists" << endl;
    cout << "0. Exit" << endl;
    cout << "======================================" << endl;
    cout << "Choose action: ";
}

// Storage mode selection menu
void showStorageMenu(int& storageMode) {
    cout << "======================================" << endl;
    cout << "    STORAGE MODE SELECTION            " << endl;
    cout << "======================================" << endl;
    cout << "Current mode: " << (storageMode == 0 ? "Memory storage" : "File storage") << endl;
    cout << "--------------------------------------" << endl;
    cout << "0. Memory storage" << endl;
    cout << "   (data exists only during program execution)" << endl;
    cout << "1. File storage" << endl;
    cout << "   (data is automatically saved/loaded from list1.txt and list2.txt)" << endl;
    cout << "======================================" << endl;
    cout << "Select mode (or any other key to cancel): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 0 || choice == 1) {
        storageMode = choice;
        cout << "Storage mode changed!" << endl;
    } else {
        cout << "Storage mode not changed." << endl;
    }
    pause();
}

// Input data from keyboard
void inputFromKeyboard(LinkedList<int>& list1, LinkedList<int>& list2, int storageMode) {
    cout << "======================================" << endl;
    cout << "        KEYBOARD INPUT                " << endl;
    cout << "======================================" << endl;
    
    list1.clear();
    list2.clear();
    
    int n, value;
    
    cout << "Enter number of elements for List1: ";
    cin >> n;
    cout << "Enter elements of List1 (space separated): ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        list1.pushBack(value);
    }
    
    cout << "Enter number of elements for List2: ";
    cin >> n;
    cout << "Enter elements of List2 (space separated): ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        list2.pushBack(value);
    }
    
    if (storageMode == 1) {
        list1.saveToFile("list1.txt");
        list2.saveToFile("list2.txt");
        cout << "\nData saved to files list1.txt and list2.txt" << endl;
    }
    
    cout << "\nData entered successfully!" << endl;
    pause();
}

// Input data from files
void inputFromFiles(LinkedList<int>& list1, LinkedList<int>& list2, int storageMode) {
    cout << "======================================" << endl;
    cout << "        FILE INPUT                    " << endl;
    cout << "======================================" << endl;
    
    list1.clear();
    list2.clear();
    
    bool loaded1 = list1.loadFromFile("list1.txt");
    bool loaded2 = list2.loadFromFile("list2.txt");
    
    if (loaded1 && loaded2) {
        cout << "Data successfully loaded from list1.txt and list2.txt" << endl;
        
        cout << "\nList1: ";
        list1.display();
        cout << "List2: ";
        list2.display();
    } else {
        cout << "Error loading files!" << endl;
        if (!loaded1) cout << "- file list1.txt not found" << endl;
        if (!loaded2) cout << "- file list2.txt not found" << endl;
    }
    
    pause();
}

// Perform containment check
void performCheck(LinkedList<int>& list1, LinkedList<int>& list2, int storageMode) {
    cout << "======================================" << endl;
    cout << "         CHECK RESULT                 " << endl;
    cout << "======================================" << endl;
    
    if (list1.size() == 0) {
        cout << "List1 is empty. Check cannot be performed." << endl;
        pause();
        return;
    }
    
    if (list2.size() == 0) {
        cout << "List2 is empty. Check cannot be performed." << endl;
        pause();
        return;
    }
    
    cout << "List1: ";
    list1.display();
    cout << "List2: ";
    list2.display();
    
    bool result = list2.containsInOrder(list1);
    
    cout << "\n--------------------------------------" << endl;
    cout << "RESULT: ";
    if (result) {
        cout << "YES, elements of List1 are contained in List2 in the same order!" << endl;
    } else {
        cout << "NO, elements of List1 are NOT contained in List2 in the same order!" << endl;
    }
    cout << "======================================" << endl;
    
    pause();
}

// Show current lists
void showLists(LinkedList<int>& list1, LinkedList<int>& list2, int storageMode) {
    cout << "======================================" << endl;
    cout << "         CURRENT LISTS                " << endl;
    cout << "======================================" << endl;
    
    cout << "Storage mode: " << (storageMode == 0 ? "Memory" : "File") << endl;
    
    if (storageMode == 1) {
        cout << "Files: list1.txt, list2.txt" << endl;
    }
    
    cout << "\nList1 (" << list1.size() << " elements): ";
    list1.display();
    
    cout << "List2 (" << list2.size() << " elements): ";
    list2.display();
    
    cout << "======================================" << endl;
    pause();
}

int main() {
    LinkedList<int> list1, list2;
    int storageMode = 0;  // 0 - memory storage, 1 - file storage
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                inputFromFiles(list1, list2, storageMode);
                break;
                
            case 2:
                inputFromKeyboard(list1, list2, storageMode);
                break;
                
            case 3:
                showStorageMenu(storageMode);
                break;
                
            case 4:
                performCheck(list1, list2, storageMode);
                break;
                
            case 5:
                showLists(list1, list2, storageMode);
                break;
                
            case 0:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice! Try again." << endl;
                pause();
        }
    } while (choice != 0);
    
    return 0;
}