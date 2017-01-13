//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include "XMLNode.h"
#include <iostream>

XMLNode::XMLNode(const string &name) : name(name) , nodeType(TextNode){}

bool XMLNode::operator==(const XMLNode &rhs) {
   return (this->nodeType == rhs.nodeType && this->name == rhs.name);
}

NodeType XMLNode::getNodeType() {return nodeType;}
