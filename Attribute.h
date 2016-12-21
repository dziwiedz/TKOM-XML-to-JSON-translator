//
// Created by Łukasz Niedźwiedź on 21/12/16.
//

#ifndef TKOM_ATTRIBUTE_H
#define TKOM_ATTRIBUTE_H
#include <string>
using namespace std;

class Attribute {
    string attributeName;
    string attributeValue;
public:
    const string &getAttributeName() const;

    void setAttributeName(const string &attributeName);

    const string &getAttributeValue() const;

    void setAttributeValue(const string &attributeValue);

    Attribute(const string &attributeName, const string &attributeValue);

    Attribute();

    void print();

};


#endif //TKOM_ATTRIBUTE_H
