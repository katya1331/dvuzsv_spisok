#include <iostream>
#include <stdexcept>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    size_t getSize() const { return size; }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        --size;
    }

    void pop_back() {
        if (!tail) throw std::out_of_range("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        --size;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void sort() {
        if (!head || !head->next) return;

        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) {
                    std::swap(i->data, j->data);
                }
            }
        }
    }

    void remove_duplicates() {
        if (!head) return;

        Node* current = head;
        while (current) {
            Node* runner = current->next;
            while (runner) {
                if (runner->data == current->data) {
                    Node* duplicate = runner;
                    runner = runner->next;
                    if (duplicate->prev) duplicate->prev->next = duplicate->next;
                    if (duplicate->next) duplicate->next->prev = duplicate->prev;
                    if (duplicate == tail) tail = duplicate->prev;
                    delete duplicate;
                    --size;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }
};

int main() {
    DoublyLinkedList list;

    list.push_front(10);
    list.push_front(20);
    list.push_back(30);
    list.push_back(20);
    list.push_back(10);

    std::cout << "List before operations: ";
    list.display();

    list.sort();
    std::cout << "List after sorting: ";
    list.display();

    list.remove_duplicates();
    std::cout << "List after removing duplicates: ";
    list.display();

    list.pop_front();
    list.pop_back();

    std::cout << "List after popping front and back: ";
    list.display();

    return 0;
}