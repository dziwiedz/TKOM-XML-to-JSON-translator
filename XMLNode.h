//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include <string>
#include <list>

#ifndef TKOM_XMLNODE_H
#define TKOM_XMLNODE_H
#include <vector>
enum NodeType {TextNode, ElementNode, AttributeNode};
using namespace std;



/**
 * Klasa reprezentujaca wezel drzewa XML.
 * Domyslnie reprezentuje Simple Text.
 * Name - Simple Text
 */
class XMLNode {
public:
    XMLNode(const string &name);

    bool operator==(const XMLNode& rhs);

    NodeType getNodeType();

private:
    string name;
    NodeType nodeType;


};


#endif //TKOM_XMLNODE_H
