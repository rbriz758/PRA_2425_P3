#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V>
class TableEntry {
	public:
        	std::string key;
        	V value;

       		TableEntry(std::string key, V value) : key(key), value(value) {}
		TableEntry(std::string key) : key(key), value() {}
        	TableEntry() : key(""), value() {}

        	friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            		return te1.key == te2.key && te1.value == te2.value;
        	}

        	friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            		return !(te1 == te2);
        	}

        	friend std::ostream &operator<<(std::ostream &out, const TableEntry<V> &te) {
            		out << "Key: " << te.key << ", Value: " << te.value;
            		return out;
		}
		// Añadidos operadores < y >
		friend bool operator<(const TableEntry<V>& te1, const TableEntry<V>& te2) {
   			 return te1.key < te2.key;
		}

		friend bool operator>(const TableEntry<V>& te1, const TableEntry<V>& te2) {
   			 return te1.key > te2.key;
		}

};

#endif

