//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#ifndef TKOM_ATTRIBUTE_H
#define TKOM_ATTRIBUTE_H
#include <string>
#include "XMLNode.h"

using namespace std;
/**
 * Klasa reprezentujaca wezel atrybutu drzewa XML.
 * Name - nazwa atrybutu
 * AttributeValue - wartosc atrybutu
 */
class XMLAttribute: public XMLNode {
private:
    string attributeValue;

public:
    XMLAttribute(const string &name, const string &attributeValue);
    NodeType nodeType;


};


#endif //TKOM_ATTRIBUTE_H
