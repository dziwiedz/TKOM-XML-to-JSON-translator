//
// Created by Łukasz Niedźwiedź on 01/11/16.
//
#include "XMLNode.h"
#include "XMLAttribute.h"
#ifndef TKOM_XMLTREE_H
#define TKOM_XMLTREE_H


class XMLTree {

    XMLNode *rootElement;

public:
    virtual ~XMLTree();

    XMLTree();

    void createJsonTree();


};


#endif //TKOM_XMLTREE_H
