//name: Luke Christensen
//partners: Eli VanHaaren and Holt Heldebrand

#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <set>

using namespace std;

class Set {
private:
    int size = 0;
    int capacity = 10; 
    int* data = new int[capacity];

    void increaseCapacity() {
        int* newData = new int[capacity*2];
        for (int i = 0; i < size; i++) {
           newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = capacity*2;
    }

    int indexOf(int value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return i;
            }
            else {
                return -1;
            }
        }
    }

public:
    Set() {}

    void print() {
        cout << "{";
        for(int i = 0; i < size; i++){
            cout << data[i] << ", ";
        }
        cout << "}" << endl;
    }

    void add(int value) {
        bool addValue = true;
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                addValue = false;
            }
        }
        if (addValue) {
            if (size == capacity) {
                increaseCapacity();
            }
            data[size] = value;
            size++;
        }
    }

    void remove(int value) {
        bool remove = false;
        int removeIndex;
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                removeIndex = i;
                remove = true;
            } 
        }
        if (remove == true) {
            for(int i = removeIndex; i < size; i++) {
                data[i] = data[i+1];
            }
            size = size-1;
        }
    }

    bool contains(int value) {
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                return true;
            }
        }
        return false;
    }

    int getSize() {
        int returnSize = size;
        return returnSize;
    }

    void printAll() {
        print();
    }

    bool isEmpty() {
        if (size == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    Set unionSet(Set & otherSet) {
        Set resultSet;
        for (int i = 0; i < size; i++) {
            resultSet.add(data[i]);
        }
        for (int i = 0; i < otherSet.size; ++i) {
            resultSet.add(otherSet.data[i]);
        }
        return resultSet;
    }

    Set intersectionSet(Set & otherSet) {
        Set resultSet;
        for (int i = 0; i < size; i++) {
            if (otherSet.contains(data[i])) {
                resultSet.add(data[i]);
            }
        }
        return resultSet;
    }

    Set differenceSet(Set & otherSet) {
        Set resultSet;
        for (int i = 0; i < size; i++) {
            if (!otherSet.contains(data[i])) {
                resultSet.add(data[i]);
            }
        }
        return resultSet;
    }

    ~Set() {
        delete[] data;
    }
};

#endif
