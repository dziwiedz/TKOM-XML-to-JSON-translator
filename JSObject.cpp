//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include <iostream>
#include "JSObject.h"


void JSObject::addNewPair(JSPair* pair) { members.push_back(pair);}

void JSObject::print() {
    unsigned long size = members.size();
    cout << "{ ";
    for (unsigned long i = 0 ; i < size -1 ; ++i)
    {
        members[i]->print();
        cout << ",\n";
    }
    members[size-1]->print();
    cout << "}\n";
}

JSObject::JSObject() : JSNode(JSType::Node) {}

void JSObject::saveToFile(std::ofstream& file) {
    unsigned long size = members.size();
    file << "{ ";
    for (unsigned long i = 0 ; i < size -1 ; ++i)
    {
        members[i]->saveToFile(file);
        file << ",\n";
    }
    members[size-1]->saveToFile(file);
    file << "}\n";
}

