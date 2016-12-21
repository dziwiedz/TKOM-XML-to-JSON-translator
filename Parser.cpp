//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Parser.h"
#include <iostream>

Parser::Parser(Scanner &s) : scn(s) {}

Parser::~Parser() {

}
/**
 *
 *
 * @return
 */
Atoms Parser::getNextToken() {
    token = scn.nextToken(false);
    cout << EnumStrings[tokenType()] << " " << token.getTokenField() << endl;
    return token.getTokenType();
}

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
 * @return Korzen drzewa XML
 */
XMLNode* Parser::parse() {
    XMLNode* rootElement;
    parseMiscelanus();
    rootElement = parseElement();
    parseMiscelanus();
    cout << EnumStrings[tokenType()] << endl;
    if (tokenType()!=END_OF_FILE)
    {
        //error
        return NULL;
    }
    cout << EnumStrings[tokenType()] << endl;
    return rootElement;
}
/**
 *
 * @return wskaznik na element
 */
XMLNode* Parser::parseElement() {
    XMLNode* element = new XMLNode();
    if (!parseOpenBody(element))
    {
        delete element;
        // error
    }
    switch(tokenType())
    {
        case(END_EMPTY_TAG):
        {
            return element;

        }
        case(END_TAG):
        {
            while(parseContent(element));
            if (tokenType()==START_CLOSE_TAG && parseCloseBody(element)) return element;
            else
            {
                // error
                delete element;
                return NULL;
            }
        }
        case(START_CLOSE_TAG):
        {
            parseCloseBody(element);
            return element;
        }
        default:
        {
            //error
            return NULL;
        }
    }
}

bool Parser::parseOpenBody(XMLNode *element)
{
    if (tokenType()!=START_TAG)
    {
        //error
        return false;
    }
    if (getNextToken()!=ATTRIBUTE_NAME)
    {
        //error
        return false;
    }
    elementStack.push(token.getTokenField());
    element->setName(token.getTokenField());
    while (parseAttributes(element));
    return true;
}

bool Parser::parseContent(XMLNode *element)
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
            element->setText(token.getTokenField());
            return true;
        }
        case(START_TAG):
        {
            XMLNode *child = parseElement();
            if(child!=NULL)
            {
                element->addChild(child);
                return true;
            }
            else
            {
                //error
                return false;
            }
        }
        default: return false;
    }
}

bool Parser::parseCloseBody(XMLNode *element)
{
    if (tokenType()!=START_CLOSE_TAG)
    {
        //error
        return false;
    }
    if (getNextToken()!=ATTRIBUTE_NAME)
    {
        //error
        return false;
    }
    if (elementStack.top()!=token.getTokenField())
    {
        //error
        return false;
    }
    elementStack.pop();
    if (getNextToken()!=END_TAG)
    {
        //error
        return false;
    }
    return true;
}

bool Parser::parseAttributes(XMLNode *element) {
    Attribute attr;
    if(getNextToken()!=ATTRIBUTE_NAME)
    {
        //error
        return false;
    }
    attr.setAttributeName(token.getTokenField());
    if (getNextToken()!=EQUAL_TAG)
    {
        //error
        return false;
    }
    if(getNextToken()!=QUOTED_TEXT)
    {
        //error
        return false;
    }
    attr.setAttributeValue(token.getTokenField());
    element->addAttribute(attr);
    return true;
}
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

Attribute Parser::cdataToAttribute()
{
    return Attribute("_cdata",token.getTokenField());
}
