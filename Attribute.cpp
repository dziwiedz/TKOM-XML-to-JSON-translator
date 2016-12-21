//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#include "Attribute.h"
#include <iostream>

const string &Attribute::getAttributeName() const {
    return attributeName;
}

void Attribute::setAttributeName(const string &attributeName) {
    Attribute::attributeName = attributeName;
}

const string &Attribute::getAttributeValue() const {
    return attributeValue;
}

void Attribute::setAttributeValue(const string &attributeValue) {
    Attribute::attributeValue = attributeValue;
}

Attribute::Attribute(const string &attributeName, const string &attributeValue) : attributeName(attributeName),
                                                                                  attributeValue(attributeValue) {}

Attribute::Attribute() {}

void Attribute::print() {
    cout<< attributeName << ":" << attributeValue << ";";
}