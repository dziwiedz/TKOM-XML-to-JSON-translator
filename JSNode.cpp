//
// Created by Łukasz Niedźwiedź on 14/01/17.
//

#include "JSNode.h"

JSNode::~JSNode() {

}

JSNode::JSNode(JSType type) : type(type) {}

JSType JSNode::getType() const {
    return type;
}

void JSNode::print() {}