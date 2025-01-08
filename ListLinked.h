#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
class ListLinked : public List<T> {

private:
    Node<T>* first;
    int n;

public:
    // Constructor
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    // Destructor
    ~ListLinked() {
        Node<T>* current = first;
        Node<T>* aux;

        // Liberar memoria de cada nodo
        while (current != nullptr) {
            aux = current->next;
            delete current;
            current = aux;
        }
    }

    // Sobrecarga del operador [] Devuelve elemento situado en posicion pos
    T operator[](int pos){
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Sobrecarga del operador << Imprime una instancia de ListLinked
    friend ostream& operator<<(ostream &out, const ListLinked<T> &list) {
	out << "[";
        Node<T>* current = list.first;
        while (current != nullptr) {
            out << current->data << " ";
            current = current->next;
        }
	out << "]";
        return out;
    }

    // Implementación de los métodos heredados de List<T>

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw out_of_range("Posición inválida!");
        }

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            current->next = new Node<T>(e, current->next);
        } 
        ++n;
    }

    // Agrega un elemento al final
    void append(T e) override {
        insert(n, e);
    }

    // Agrega elemento al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Elimina un elemento de la posicion pos
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida!");
        }

        Node<T>* toDelete = first;

        if (pos == 0) {
            first = first->next;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            toDelete = current->next;
            current->next = current->next->next;
        }

        T removed = toDelete->data;
        delete toDelete;
        --n;
        return removed;
    }

    // Obtiene elemento de la posicion pos
    T get(int pos) override {
        return (*this)[pos];
    }

    // Busca  elemento y retorna su posicion   
    int search(T e) override {
        Node<T>* current = first;
        int pos = 0;
        while (current != nullptr) {
            if (current->data == e) {
                return pos;
            }
            current = current->next;
            ++pos;
        }
        return -1;
    }

    // Comprueba si la lista esta vacía
    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};

#endif

