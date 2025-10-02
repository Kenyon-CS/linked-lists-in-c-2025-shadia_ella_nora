#include <iostream>

template <typename T>
class node {
  public:
    T data;           // Data of generic type T
    node* next;       // Pointer to the next node in the list

    node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
  private:
    node<T>* head;  // Pointer to the first node of the list

  public:
    LinkedList() : head(nullptr) {}

    // Insert at the end
    void append(T value) {
        node<T>* newNode = new node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Insert at the beginning
    void prepend(T value) {
        node<T>* newNode = new node<T>(value);
        newNode->next = head;
        head = newNode;
    }

    // Remove first occurrence of value
    void remove(T value) {
        if (head == nullptr) return;

        if (head->data == value) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) return;

        node<T>* nodeToRemove = temp->next;
        temp->next = temp->next->next;
        delete nodeToRemove;
    }

    //remove and return first element in list
    T lfirst() {
        if (head != nullptr) {
            node<T>* temp = head;
            head = head->next;
            T save = temp->data;
            delete temp;
            return save;
        }
        T junk;
        return junk;
    }

    //remove and return last element in list
    T last() {
        node<T>* cur = head;
        node<T>* penult;
        while (cur->next != nullptr) {
            if (cur->next->next == nullptr) {
                penult = cur;
            }
            cur = cur->next;
        }
        penult->next = nullptr;
        node<T>* foundLast = cur;
        delete cur;
        return foundLast->data;
    }

    //add element in sorted order
    void addOrder(T value) {
        node<T>* newNode = new node<T>(value);
        if (head == nullptr) {
            head = newNode;
            return;
        } else if (value < head->data) {
                newNode->next = head;
                head = newNode;
                return;
        } else {
            for (node<T>* cur = head; cur != nullptr; cur = cur->next){
                if (value >= cur->data) {
                    if (cur->next == nullptr) { //at the end of linkedlist
                        cur->next = newNode;
                        return;
                    } else if (value <= cur->next->data) { //not at the end
                        newNode->next = cur->next;
                        cur->next = newNode;
                        return;
                    }
                }
            }
        }
    }
    

    // Print the list
    void print() {
        node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        while (head != nullptr) {
            node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList<int> list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);
    list.append(8);
    list.append(10);

    std::cout << "Linked List: ";
    list.print();

    list.remove(2);
    std::cout << "After removing 2: ";
    list.print();

    int x = list.lfirst();
    std::cout << "Removed head: " << x << std::endl;

    x = list.last();
    std::cout << "Removed end: " << x << std::endl;

    LinkedList<int> myList;
    myList.addOrder(40);
    myList.addOrder(50);
    myList.addOrder(60);
    myList.addOrder(30);

    std::cout << "Ordered Linked List: ";
    myList.print();

    return 0;
}
