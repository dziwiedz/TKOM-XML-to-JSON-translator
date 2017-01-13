//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#include "XMLAttribute.h"
#include <iostream>

XMLAttribute::XMLAttribute(const string &name, const string &attributeValue) :
        XMLNode(name),
        attributeValue(attributeValue),
        nodeType(AttributeNode)
{}
