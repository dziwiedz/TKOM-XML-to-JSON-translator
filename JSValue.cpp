//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include <iostream>
#include "JSValue.h"

void JSValue::print() {
    cout << "\"" << value << "\"";
}

JSValue::JSValue(const string &value) : JSNode(JSType::Value), value(value) {}

void JSValue::saveToFile(std::ofstream &file) {
    file << "\"" << value << "\"";
}
