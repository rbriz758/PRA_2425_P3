#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root;  // Nodo raíz del ABB
    int nelem;        // Número de elementos en el ABB

    // Búsqueda recursiva
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw std::runtime_error("Element not found");
        } else if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    // Inserción recursiva
    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            ++nelem;
            return new BSNode<T>(e);
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw std::runtime_error("Duplicated element");
        }
        return n;
    }

    // Recorrido inorden
    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    // Eliminar el nodo con el elemento máximo
    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("Tree is empty");
        }
        while (n->right != nullptr) {
            n = n->right;
        }
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* left = n->left;
            delete n;
            return left;
        }
        n->right = remove_max(n->right);
        return n;
    }

    // Eliminación recursiva
    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw std::runtime_error("Element not found");
        } else if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
                delete n;
                return temp;
            }
        }
        return n;
    }

    // Liberación de memoria recursiva
    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    // Constructor
    BSTree() : root(nullptr), nelem(0) {}

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }

    // Tamaño
    int size() const {
        return nelem;
    }

    // Búsqueda
    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    // Sobrecarga del operador []
    T operator[](T e) const {
        return search(e);
    }

    // Inserción
    void insert(T e) {
        root = insert(root, e);
    }

    // Eliminación
    void remove(T e) {
        root = remove(root, e);
        --nelem;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif // BSTREE_H

