//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_XMLELEMENT_H
#define TKOM_XMLELEMENT_H


#include "XMLNode.h"
/**
 * Klasa reprezentujaca wezel elementu drzewa XML.
 * Name - nazwa elemenetu
 * childNodes - wektor przechowujacy dzieci elemenetu.
 * twin - wskaznik na element majacy taka sama nazwe
 */
class XMLElement : public XMLNode {
public:
    XMLElement(const string &name);
    void addNewNode(XMLNode*);
    void setTwin(XMLElement*);

private:
    vector<XMLNode*> childNodes;
    XMLElement* twin;
    NodeType nodeType;


};


#endif //TKOM_XMLELEMENT_H
