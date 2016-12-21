//
// Created by Łukasz Niedźwiedź on 01/11/16.
//
#include "XMLNode.h"
#include "Attribute.h"
#ifndef TKOM_XMLTREE_H
#define TKOM_XMLTREE_H


class XMLTree {

    XMLNode *rootElement;

public:
    virtual ~XMLTree();

    XMLTree();

    void writeToJS();


};


#endif //TKOM_XMLTREE_H
