#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node() : next(nullptr) {}
        Node(T value) : data(value), next(nullptr) {}
        void killSelf() {
            if (next) {
                next->killSelf();
                delete next;
                next = nullptr;
            }
        }
    };

    Node* head;
    int nodes;

public:
    ForwardList() : List<T>(), head(nullptr), nodes(0) {}

    ~ForwardList() {
        clear();
    }

    T front() {
        if (!head) throw "Lista vacía";
        return head->data;
    }

    T back() {
        if (!head) throw "Lista vacía";
        Node* temp = head;
        while (temp->next) temp = temp->next;
        return temp->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        nodes++;
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        nodes++;
    }

    T pop_front() {
        if (!head) throw "Lista vacía";
        Node* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;
        nodes--;
        return val;
    }

    T pop_back() {
        if (!head) throw "Lista vacía";
        if (!head->next) {
            T val = head->data;
            delete head;
            head = nullptr;
            nodes--;
            return val;
        }
        Node* prev = nullptr;
        Node* curr = head;
        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }
        T val = curr->data;
        prev->next = nullptr;
        delete curr;
        nodes--;
        return val;
    }

    bool insert(T data, int pos) {
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        temp->next = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes || !head) return false;
        if (pos == 0) {
            pop_front();
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        nodes--;
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes) throw "fuera de rango";
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        return temp->data;
    }

    bool is_empty() {
        return head == nullptr;
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (!is_empty()) pop_front();
    }

    void sort() {
        if (nodes < 2) return;
        for (Node* i = head; i && i->next; i = i->next) {
            for (Node* j = i->next; j; j = j->next) {
                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
            }
        }
    }

    bool is_sorted() {
        if (nodes < 2) return true;
        Node* temp = head;
        while (temp && temp->next) {
            if (temp->data > temp->next->data) return false;
            temp = temp->next;
        }
        return true;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    std::string name() {
        return "ForwardList";
    }
};

#endif
