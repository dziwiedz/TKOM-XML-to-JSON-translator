//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include <iostream>
#include "JSPair.h"


void JSPair::print(){
    cout << "\"" << name << "\" : ";
    if (value->getType()!=JSType::Value) cout << "\n";
    value->print();
}

void JSPair::saveToFile(std::ofstream &file) {
    file << "\"" << name << "\" : ";
    if (value->getType()!=JSType::Value) file << "\n";
    value->saveToFile(file);
}


void JSPair::setName(const string &name) {
    JSPair::name = name;
}

void JSPair::setValue(JSNode *value) {
    JSPair::value = value;
}

JSPair::JSPair() : JSNode(JSType::Pair) {}

JSPair::JSPair(const string &name) : JSNode(JSType::Pair), name(name) {}

JSPair::JSPair( const string &name, JSNode *value) : JSNode(JSType::Pair), name(name), value(value) {}
