//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#include "XMLElement.h"

XMLElement::XMLElement(const string &elementName) : elementName(elementName) ,twin(NULL){}

void XMLElement::setAttributesList(vector<XMLAttribute*> list)
{
    attributes=list;
}
void XMLElement::addAttribute(XMLAttribute* a)
{
    attributes.push_back(a);
}
bool XMLElement::hasAttributes() {return attributes.size()>0;}
/**
 * Dodanie nowego elementu potomnego. W przypadku gdy wystapil juz element o takiej nazwie,
 * nowy element ustawiany jest jako blizniak juz istniejacego
 * @param child - nowy element
 */
void XMLElement::addChildElement(XMLElement* child){
    for (unsigned int i =0 ; i < childNodes.size() ; ++i) {
        if (childNodes[i]->getElementName() == child->getElementName()) {
            childNodes[i]->setTwin(child);
            break;
        }
    }
    childNodes.push_back(child);
}
bool XMLElement::hasChilds() {return childNodes.size()>0;}
void XMLElement::addTextNode(string textNode){
    textNodes.push_back(textNode);
}
/**
 * nowy element, jest zapisywany na koncu lancuha blizniakow, by zachowac kolejnosc kolejnych wezlow przy przetwarzaniu.
 * @param e - wskaznik na nowy element
 */
void XMLElement::setTwin(XMLElement* e){
    if (twin==NULL) twin = e;
    else twin->setTwin(e);
}
bool XMLElement::hasTwin(){return twin!=NULL;}

bool XMLElement::hasText() const{ return textNodes.size()>0;}

bool XMLElement::isProcessed() const { return processed;}

/**
 * Konwersja wezla XML na objekt pare nazwa_wezla : <zawartosc_wezla>
 * Wartosc pary jest zalezna od zawartosci danego wezla
 * @return Wskaznik na Pare "Nazwa Wezla" : "Zawartosc"
 */
JSPair* XMLElement::convertToJs()
{
    if (processed) return nullptr;
    JSPair* mainPair;
    if (!hasAttributes() && !hasChilds() ) { //Jezeli nie ma wezlow potomnych i atrybutow, przetwarzany jest tylko tekst
        if (textNodes.size()==0) return new JSPair(elementName,new JSValue("null"));
        else mainPair= processTextNodes(false); }
    else {                                  // W przeciwnym przypadku, przegladana jest zawartosc wezla
        JSObject* mainPairValue = processContent();
        mainPair = new JSPair(elementName,mainPairValue);
    }
    processed=true;
    return mainPair;
}
/**
 * Przetwarza tylko zawartosc wezla.
 * @return W zaleznosci od zawartosci wezla, moze zwrocic rozne typy obiektow JSON
 */
JSNode* XMLElement::convertAsArrayElement() {
    if (processed) return nullptr;
    if (!hasAttributes() && !hasChilds()) {
        if (textNodes.size()==0) return new JSValue("null");
        else if (textNodes.size()==1) return new JSValue(textNodes[0]);
        else {
            JSObject* object = new JSObject();
            object->addNewPair( processTextNodes(true));
            return object;
        }
    }
    processed=true;
    return processContent();
}
/**
 * Przetwarzanie dzieci wezla.
 * @param objectToWrite - Obiekt do ktorego zapisywane sa zawartosci wezlow-dzieci
 */
void XMLElement::processChildrens(JSObject* objectToWrite){
    for (unsigned int i = 0; i < childNodes.size(); ++i) {
        if(!childNodes[i]->isProcessed()) {
            if (childNodes[i]->hasTwin()) {
                JSPair *twinPair = new JSPair(childNodes[i]->getElementName());
                twinPair->setValue(childNodes[i]->convertTwinsAsArray(childNodes[i]));
                objectToWrite->addNewPair(twinPair);
            } else {
                JSPair *pair = childNodes[i]->convertToJs();
                if (pair != NULL) objectToWrite->addNewPair(pair);
            }
        }
    }
}
/**
 * Przetwarzanie atrybutow wezla. Atrybut jest przeksztalcany do pary "nazwa atrybutu" : "wartosc atrybutu"
 * @param o = obiekt do ktorego zapisywane sa pary
 */
void XMLElement::processAttributesToJS(JSObject *o) {
    for (unsigned int i =0 ; i < attributes.size() ; ++i) {
        o->addNewPair(attributes[i]->convertToJSPair());
    }
}
/**
 * Przetwarzanie wezlow-tekstow elementu
 * @param defaultText - Jezeli prawda - uzywa jako nazwa pary "#text", wpp pobiera nazwe elementu
 * @return JSPair - "nazwa" : "simple_text" lub "nazwa" : [ "simple text1"..."simple textN"]
 */
JSPair* XMLElement::processTextNodes(bool defaultText) {
    string pairName;
    if (defaultText) pairName = "#text";
    else pairName = elementName;
    if (textNodes.size()==1) return new JSPair(pairName,new JSValue(textNodes[0]));
    else if (textNodes.size()>1){
        JSArray* textArray = new JSArray();
        for (unsigned int i =0; i < textNodes.size() ; ++i) textArray->addNewElement(new JSValue(textNodes[i]));
        return new JSPair(pairName,textArray);
    }
    return NULL;
}
/**
 * Przeksztalca wezly o tej samej nazwie, jako tablica ich elementow
 * @param element - pierwszy z listy blizniakow
 * @return  - Tablica zawartosci elementow
 */
JSArray* XMLElement::convertTwinsAsArray(XMLElement* element) {
    JSArray* array = new JSArray();
    XMLElement* currentNode = element;
    while(currentNode!=NULL) {
        array->addNewElement(element->convertAsArrayElement());
        currentNode=currentNode->twin;
    }
    return array;
}
/**
 * Przeksztalcenie zawartosci wezlow
 * @return JSObject* - obiekt zawierajacy zawartosc wezlow
 */
JSObject* XMLElement::processContent() {
    JSObject* mainPairValue = new JSObject();
    processAttributesToJS(mainPairValue);
    JSPair* pair = processTextNodes(true);
    if (pair!=NULL) mainPairValue->addNewPair(pair);
    processChildrens(mainPairValue);
    return mainPairValue;
}

const string &XMLElement::getElementName() const {
    return elementName;
}


