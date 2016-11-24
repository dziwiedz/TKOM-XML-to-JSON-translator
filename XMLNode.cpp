//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include "XMLNode.h"

XMLNode::XMLNode() {



}

XMLNode::~XMLNode() {

}

bool XMLNode::isIsArg() const {
    return isArg;
}

const string &XMLNode::getValue() const {
    return value;
}
