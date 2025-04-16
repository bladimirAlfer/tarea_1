#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
        void killSelf() {
            if (next) {
                next->killSelf();
                delete next;
                next = nullptr;
            }
        }
    };

    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : List<T>(), head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() {
        if (!head) throw "Lista vacía";
        return head->data;
    }

    T back() {
        if (!tail) throw "Lista vacía";
        return tail->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
        nodes++;
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
        nodes++;
    }

    T pop_front() {
        if (!head) throw "Lista vacía";
        T val = head->data;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        nodes--;
        return val;
    }

    T pop_back() {
        if (!tail) throw "Lista vacía";
        T val = tail->data;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        nodes--;
        return val;
    }

    bool insert(T data, int pos) {
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        } else if (pos == nodes) {
            push_back(data);
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; ++i) temp = temp->next;
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) return false;
        if (pos == 0) {
            pop_front();
            return true;
        } else if (pos == nodes - 1) {
            pop_back();
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos; ++i) temp = temp->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
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
        return nodes == 0;
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
                if (i->data > j->data) swap(i->data, j->data);
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
        Node* curr = head;
        Node* temp = nullptr;
        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        swap(head, tail);
    }

    std::string name() {
        return "DoubleList";
    }
};

#endif
