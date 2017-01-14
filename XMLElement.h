//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_XMLELEMENT_H
#define TKOM_XMLELEMENT_H

#include "XMLAttribute.h"
#include "JSObject.h"
#include "JSArray.h"

/**
 * Klasa reprezentujaca wezel elementu drzewa XML.
 * Name - nazwa elemenetu
 * childNodes - wektor przechowujacy dzieci elemenetu.
 * twin - wskaznik na element majacy taka sama nazwe
 */
class XMLElement {
public:
    XMLElement(const string &elementName);


    void setAttributesList(vector<XMLAttribute*>);
    void addAttribute(XMLAttribute*);
    bool hasAttributes();

    void addChildElement(XMLElement* child);
    bool hasChilds();

    void addTextNode(string textNode);

    void setTwin(XMLElement*);
    bool hasTwin();

    bool hasText() const;

    bool isProcessed() const;

    JSPair* convertToJs();
    JSNode* convertAsArrayElement();

    const string &getElementName() const;

private:
    vector<XMLElement*> childNodes;
    vector<XMLAttribute*> attributes;
    vector<string> textNodes;
    XMLElement* twin;
    string elementName;
    bool processed;
    JSArray* convertTwinsAsArray(XMLElement*);
    void processAttributesToJS(JSObject*);
    void processChildrens(JSObject*);
    JSPair* processTextNodes(bool defaultText);
    JSObject* processContent();


};


#endif //TKOM_XMLELEMENT_H
