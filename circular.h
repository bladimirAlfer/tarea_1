#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() : next(this), prev(this) {}
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}

        void killSelf() {
        }
    };

private:
    Node* head;
    int nodes;

public:
    CircularList() : List<T>(), nodes(0) {
        head = new Node();
    }

    ~CircularList() {
        clear();
        delete head;
    }

    T front() {
        if (is_empty()) throw "Lista vacia";
        return head->next->data;
    }

    T back() {
        if (is_empty()) throw "Lista vacia";
        return head->prev->data;
    }

    void push_front(T data) {
        Node* nuevo = new Node(data);
        Node* primero = head->next;
        nuevo->next = primero;
        nuevo->prev = head;
        primero->prev = nuevo;
        head->next = nuevo;
        nodes++;
    }

    void push_back(T data) {
        Node* nuevo = new Node(data);
        Node* ultimo = head->prev;
        nuevo->next = head;
        nuevo->prev = ultimo;
        ultimo->next = nuevo;
        head->prev = nuevo;
        nodes++;
    }

    T pop_front() {
        if (is_empty()) throw "Lista vacia";
        Node* borrar = head->next;
        T val = borrar->data;
        head->next = borrar->next;
        borrar->next->prev = head;
        delete borrar;
        nodes--;
        return val;
    }

    T pop_back() {
        if (is_empty()) throw "Lista vacia";
        Node* borrar = head->prev;
        T val = borrar->data;
        head->prev = borrar->prev;
        borrar->prev->next = head;
        delete borrar;
        nodes--;
        return val;
    }

    bool insert(T data, int pos) {
        if (pos < 0 || pos > nodes) return false;

        Node* actual = head;
        for (int i = 0; i < pos; i++) actual = actual->next;

        Node* nuevo = new Node(data);
        nuevo->next = actual->next;
        nuevo->prev = actual;
        actual->next->prev = nuevo;
        actual->next = nuevo;
        nodes++;

        return true;
    }


    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) return false;
        Node* actual = head->next;
        for (int i = 0; i < pos; i++) actual = actual->next;
        actual->prev->next = actual->next;
        actual->next->prev = actual->prev;
        delete actual;
        nodes--;
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes) throw "fuera de rango";
        Node* actual = head->next;
        for (int i = 0; i < pos; i++) actual = actual->next;
        return actual->data;
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
        for (Node* i = head->next; i->next != head; i = i->next) {
            for (Node* j = i->next; j != head; j = j->next) {
                if (i->data > j->data) swap(i->data, j->data);
            }
        }
    }

    bool is_sorted() {
        if (nodes < 2) return true;
        Node* actual = head->next;
        while (actual->next != head) {
            if (actual->data > actual->next->data) return false;
            actual = actual->next;
        }
        return true;
    }

    void reverse() {
        if (nodes < 2) return;
        Node* current = head;
        do {
            swap(current->next, current->prev);
            current = current->prev;
        } while (current != head);
    }

    std::string name() {
        return "CircularList";
    }
};

#endif
