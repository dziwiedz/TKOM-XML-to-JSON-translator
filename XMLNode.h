//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include <string>
#include <list>

#ifndef TKOM_XMLNODE_H
#define TKOM_XMLNODE_H

using namespace std;
class XMLNode {

    XMLNode *parent;
    string value;
    bool isArg;
    list <XMLNode*> childrensList;


public:
    XMLNode();

    virtual ~XMLNode();
    bool hasChild();
    void addChild(XMLNode* newChild);
    bool isIsArg() const;
    const string &getValue() const;

};


#endif //TKOM_XMLNODE_H
