#ifndef NODE_H
#define NODE_H

#include <ostream> 

template <typename T>
class Node {
public:
    T data;          
    Node<T>* next;   

    // Constructor
    Node(T data, Node<T>* next = nullptr){
    	this->data = data;
	this->next = next;

    }

    // Sobrecarga del operador << para imprimir el valor de data  del nodo
    friend std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
        out << node.data; 
        return out;
    }
};

#endif 

