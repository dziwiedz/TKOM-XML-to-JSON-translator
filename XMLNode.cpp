//
// Created by Łukasz Niedźwiedź on 24/11/16.
//

#include "XMLNode.h"
#include <iostream>

XMLNode::XMLNode(XMLNode* p) : parent(p) {


}

XMLNode::~XMLNode() {

}

void XMLNode::addChild(XMLNode *newChild) {
    childrensList.push_back(newChild);
}

bool XMLNode::hasChild() { return !childrensList.empty();}

void XMLNode::addAttribute(Attribute arg) { argList.push_back(arg);}

void XMLNode::print()
{
    cout << "Element : " << name << " Text: " << text << endl;
    cout << "My args: ";
    for (int i = 0; i < argList.size() ; i++) argList[i].print();
    cout << '\n';
    for (int i = 0; i < childrensList.size() ; i++) childrensList[i]->print();
}

XMLNode::XMLNode() {}

const string &XMLNode::getText() const {
    return text;
}

void XMLNode::setText(const string &text) {
    XMLNode::text = text;
}

const string &XMLNode::getName() const {
    return name;
}

void XMLNode::setName(const string &name) {
    XMLNode::name = name;
}
