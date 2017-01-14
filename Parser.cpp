//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Parser.h"
#include "XMLAttribute.h"
#include <iostream>

Parser::Parser(Lexer &s) : scn(s) {}

Parser::~Parser() {

}
/**
 * Pobranie nastepnego tokena, bez uwzgledniania spacji
 * @return
 */
Atoms Parser::getNextToken() {
    token = scn.nextToken(false);
    cout << EnumStrings[tokenType()] << " " << token.getTokenField() << endl;
    return token.getTokenType();
}
/**
 * Pobranie nastepnego tokena, z uwzglednieniem bialych znakow
 * @return
 */
Atoms Parser::getNextTokenWithSpaces() {
    token = scn.nextToken(true);
    cout << EnumStrings[tokenType()] << " " << token.getTokenField() << endl;
    return token.getTokenType();
}
/**
 *
 * @return
 */
Atoms Parser::tokenType() {
    return token.getTokenType();
}

/**
 * Procedura ropozycznajaca parsowanie pliku XML.
 * Korzeniem drzewa XML musi byc element.
 * XML_TREE = Misc* Element Misc* ;
 * @return Korzen drzewa XML
 */
XMLElement* Parser::parse() {
    XMLElement* rootElement;
    while(parseMiscelanus());
    rootElement = parseElement();
    while(parseMiscelanus());
    if (tokenType()!=END_OF_FILE)
    {
        wrongTokenError(EnumStrings[END_OF_FILE]);
        return NULL;
    }
    return rootElement;
}
/**
 * Element = OpenBody ( END_EMPTY_TAG | END_TAG Content* CloseBody) ;
 * @return wskaznik na element
 */
XMLElement* Parser::parseElement() {
    XMLElement* element;
    element = parseOpenBody();
    switch(tokenType())
    {
        case(END_EMPTY_TAG):
        {
            return element;

        }
        case(END_TAG):
        {
            while(parseContent(element));
            if (tokenType()==START_CLOSE_TAG && parseCloseBody()) return element;
            else
            {
                // error
                delete element;
                throw ParserException();
                return NULL;
            }
        }
        case(START_CLOSE_TAG):
        {
            parseCloseBody();
            return element;
        }
        default:
        {
            throw ParserException();
            return NULL;
        }
    }
}
/**
 * OpenBody = START_TAG Name Atributte* ;
 * @param element
 * @return
 */
XMLElement* Parser::parseOpenBody()
{
    if (tokenType()!=START_TAG)
    {
        wrongTokenError(EnumStrings[START_TAG]);
    }
    if (getNextToken()!=ATTRIBUTE_NAME)
    {
        wrongTokenError(EnumStrings[ATTRIBUTE_NAME]);
    }
//    XMLTextNode *element = new XMLTextNode();
    XMLElement* element = new XMLElement(token.getTokenField());
    elementStack.push(token.getTokenField());
    element->setAttributesList(parseAttributes());
    return element;
}
/**
 * Content = Misc | CDATA_TAG | Text | Element ;
 * @param element
 * @return
 */
bool Parser::parseContent(XMLElement *element)
{
    switch(getNextTokenWithSpaces())
    {
        case(PROCESS_INST):
        case(DOCTYPE):
        case(COMMENT):
        {
            return true;
        }
        case(CDATA):
        {
            element->addAttribute(cdataToAttribute());
            return true;
        }
        case(SIMPLE_TEXT):
        {
            element->addTextNode(token.getTokenField());
            return true;
        }
        case(START_TAG):
        {
            XMLElement *child = parseElement();
            if(child!=NULL)
            {
                element->addChildElement(child);
                return true;
            }
            else
            {
                throw ParserException();
            }
            return true;
        }
        default: return false;
    }
}
/**
 * OpenBody = START_TAG Name Atributte* ;
 * @param element wskaznik na akutalny wezel
 * @return true - jezeli poprawnie wykonano parsowanie, false w przeciwnym wypadku
 */
bool Parser::parseCloseBody()
{
    if (tokenType()!=START_CLOSE_TAG)
    {
        wrongTokenError(EnumStrings[ATTRIBUTE_NAME]);
        return false;
    }
    if (getNextToken()!=ATTRIBUTE_NAME)
    {
        wrongTokenError(EnumStrings[ATTRIBUTE_NAME]);
        return false;
    }
    if (elementStack.top()!=token.getTokenField())
    {
        stackError(elementStack.top());
        return false;
    }
    elementStack.pop();
    if (getNextToken()!=END_TAG)
    {
        wrongTokenError(EnumStrings[ATTRIBUTE_NAME]);
        return false;
    }
    return true;
}
/**
 *
 * @return Vector of attributes. Could be empty if element dosen't have any
 */
vector<XMLAttribute*> Parser::parseAttributes() {
    vector<XMLAttribute*> attributes;
    XMLAttribute* attr;
    while((attr=parseSingleAttribute())!= nullptr) attributes.push_back(attr);
    return attributes;
}
/**
 * Atributte = AttributeName, EQUAL_TAG, ATTRIBUTE_VALUE ;
 * @return Attribute
 */
XMLAttribute* Parser::parseSingleAttribute() {
    if (getNextToken() != ATTRIBUTE_NAME) {
//        wrongTokenError(EnumStrings[ATTRIBUTE_NAME]);
        return nullptr;
    }
    string attributeName = token.getTokenField();
    if (getNextToken() != EQUAL_TAG) {
        wrongTokenError(EnumStrings[EQUAL_TAG]);
    }
    if (getNextToken() != QUOTED_TEXT) {
        wrongTokenError(EnumStrings[QUOTED_TEXT]);
    }
    return new XMLAttribute(attributeName,token.getTokenField());
}
/**
 * Misc = DOCTYPE_TAG | COMMENT_TAG | PROCESS_INST ;
 * @return
 */
bool Parser::parseMiscelanus()
{
    switch (getNextToken())
    {
        case(PROCESS_INST):
            return true;
        case(DOCTYPE):
            return true;
        case(COMMENT):
            return true;
        default:
            return false;
    }
}
/**
 *
 * @return
 */
XMLAttribute* Parser::cdataToAttribute()
{
    return new XMLAttribute("_cdata",token.getTokenField());
}

void Parser::wrongTokenError(string expected)
{
    throw WrongTokenTypeException(expected,token.getTokenTypeString(),token.getLine(),token.getColumn());
}
void Parser::stackError(string expected){
    throw NameStackException(expected,token.getTokenField(),token.getLine(),token.getColumn());
}