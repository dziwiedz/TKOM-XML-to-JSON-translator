//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include <string>
#include <list>

#ifndef TKOM_XMLNODE_H
#define TKOM_XMLNODE_H
#include "Attribute.h"
#include <vector>
using namespace std;
class XMLNode {

    XMLNode *parent;
    string value;
    list <XMLNode*> childrensList;
    vector<Attribute> argList;


public:
    XMLNode(XMLNode*);

    void setValue(const string &value);

    virtual ~XMLNode();
    bool hasChild();
    void addChild(XMLNode* newChild);
    const string &getValue() const;

};


#endif //TKOM_XMLNODE_H
