//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#ifndef TKOM_ATTRIBUTE_H
#define TKOM_ATTRIBUTE_H
#include <string>
#include "JSPair.h"

using namespace std;
/**
 * Klasa reprezentujaca wezel atrybutu drzewa XML.
 * Name - nazwa atrybutu
 * AttributeValue - wartosc atrybutu
 */
class XMLAttribute {
public:
    XMLAttribute(const string &name, const string &attributeValue);

    const string &getAttributeValue() const;

    const string &getName() const;

    JSPair* convertToJSPair();

private:
    string attributeValue;
    string name;


};


#endif //TKOM_ATTRIBUTE_H
