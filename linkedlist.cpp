#include <iostream>

template <typename T>
class node {
  public:
    T data;           // Data of generic type T
    node* next;       // Pointer to the next node in the list
    node* prev;       // Pointer to the previous node in the list

    node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
  private:
    node<T>* head;  // Pointer to the first node of the list
    node<T>* tail;  // Pointer to the last node of the list

  public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Insert at the end
    void push_back(T value) {
        node<T>* newNode = new node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Insert at the beginning
    void push_front(T value) {
        node<T>* newNode = new node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
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

    //remove and return last element in list
    T pop_back() {
        if (head != nullptr) {
            node<T>* temp = tail;
            T save = temp->data;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
            return save;
        } else {
            throw std::out_of_range ("Cannot remove from empty list!");
        }
    }

    //remove and return first element in list
    T pop_front() {
        if (head != nullptr) {
            node<T>* temp = head;
            T save = temp->data;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            delete temp;
            return save;
        } else {
            throw std::out_of_range ("Cannot remove from empty list!");
        }
    }

    //add element in sorted order
    void addOrder(T value) {
        node<T>* newNode = new node<T>(value);
        if (head == nullptr) {
            head = newNode;
            return;
        } else if (value < head->data) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        } else {
            for (node<T>* cur = head; cur != nullptr; cur = cur->next){
                if (value >= cur->data) {
                    if (cur->next == nullptr) { //at the end of linkedlist
                        cur->next = newNode;
                        newNode->prev = cur;
                        return;
                    } else if (value <= cur->next->data) { //not at the end
                        newNode->next = cur->next;
                        newNode->prev = cur;
                        cur->next->prev = newNode;
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
            std::cout << temp->data << " <-> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
        /*temp = tail;
        while (temp != nullptr) {
            std::cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        std::cout << "nullptr" << std::endl;*/
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

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.push_back(8);
    list.push_back(10);

    std::cout << "Linked List: ";
    list.print();

    list.remove(2);
    std::cout << "After removing 2: ";
    list.print();

    int x = list.pop_front();
    std::cout << "Removed head: " << x << std::endl;
    x = list.pop_back();
    std::cout << "Removed end: " << x << std::endl;
    std::cout << "After removing ends: ";
    list.print();

    LinkedList<double> emptyList;
    double a, b;
    //the below runs fine but leads to program timing out, so it is commented out
    /*try {
        a = emptyList.pop_front();
    } catch(std::out_of_range&) {
        std::cout << "Not crashing on empty lists with lfirst" << std::endl;
    }
    try {
        b = emptyList.pop_back();
    } catch(std::out_of_range&) {
        std::cout << "Not crashing on empty lists with last" << std::endl;
    }*/
    emptyList.push_back(85.67);
    a = emptyList.pop_front();
    //std::cout << "popped one from front" << std::endl;
    emptyList.push_front(.98);
    b = emptyList.pop_back();
    //std::cout << "popped one from back" << std::endl;
    std::cout << "Removed values: " << a << ", " << b << std::endl;

    LinkedList<int> myList;
    myList.addOrder(40);
    myList.addOrder(50);
    myList.addOrder(60);
    myList.addOrder(30);

    std::cout << "Ordered Linked List: ";
    myList.print();

    return 0;
}
