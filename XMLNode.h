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
    string text;
    string name;
    vector <XMLNode*> childrensList;
    vector<Attribute> argList;


public:
    XMLNode(XMLNode*);
    XMLNode();

    const string &getText() const;

    void setText(const string &text);

    const string &getName() const;

    void setName(const string &name);

    virtual ~XMLNode();
    bool hasChild();
    void addChild(XMLNode* newChild);
    void addAttribute(Attribute arg);
    void print();

};


#endif //TKOM_XMLNODE_H
