//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include "XMLNode.h"

XMLNode::XMLNode(XMLNode* p) : parent(p) {


}

XMLNode::~XMLNode() {

}

bool XMLNode::isIsArg() const {
    return isArg;
}

const string &XMLNode::getValue() const {
    return value;
}

void XMLNode::setValue(const string &value) {
    XMLNode::value = value;
}
