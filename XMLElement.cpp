//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include "XMLElement.h"

XMLElement::XMLElement(const string &name) : XMLNode(name), nodeType(ElementNode) {}
void XMLElement::addNewNode(XMLNode* node)
{
    if (node->getNodeType() == ElementNode)
    {
        for (vector<XMLNode*>::iterator it = childNodes.begin() ; it !=childNodes.end();++it){
            if ((*it)==node) {
                try {
                    XMLElement *twinElement = static_cast<XMLElement *>(*it);
                    twin->setTwin(twinElement);
                }catch (exception e) {e.what();}

            }
        }
    }
    childNodes.push_back(node);
}

void XMLElement::setTwin(XMLElement *e) {
    if (twin==NULL) twin = e;
    else {
        twin->setTwin(e);
    }
}