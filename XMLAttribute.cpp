//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#include "XMLAttribute.h"




XMLAttribute::XMLAttribute(const string &name, const string &attributeValue) :
        name(name),
        attributeValue(attributeValue) {}

const string &XMLAttribute::getAttributeValue() const {
    return attributeValue;
}

const string &XMLAttribute::getName() const {
    return name;
}

JSPair* XMLAttribute::convertToJSPair() {
    return new JSPair("@"+name,new JSValue(attributeValue));
}
