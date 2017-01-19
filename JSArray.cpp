//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include <iostream>
#include "JSArray.h"



void JSArray::addNewElement(JSNode *val) { elements.push_back(val);}

void JSArray::print() {
    unsigned long size = elements.size();
    cout << "[";
    for (unsigned long i = 0 ; i < size-1 ; ++i)
    {
        elements[i]->print();
        cout << ",\n";
    }
    elements[size-1]->print();
    cout << "]";
}

JSArray::JSArray() : JSNode(JSType::Array) {}

void JSArray::saveToFile(std::ofstream& file) {
    unsigned long size = elements.size();
    file << "[";
    for (unsigned long i = 0 ; i < size-1 ; ++i)
    {
        elements[i]->saveToFile(file);
        file << ",\n";
    }
    elements[size-1]->saveToFile(file);
    file << "]";
}