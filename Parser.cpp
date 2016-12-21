//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Parser.h"

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
    string text = "null";
    parseMiscelanus();
    XMLNode *rootElement = parseElement(NULL);
    parseMiscelanus();
    if (tokenType()!=END_OF_FILE)
    {
        //error
        return NULL;
    }
    return rootElement;
}
/**
 *
 * @return wskaznik na element
 */
XMLNode* Parser::parseElement(XMLNode* parent) {
    XMLNode* element;
    element = new XMLNode(parent);
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
    if (getNextToken()!=SIMPLE_TEXT)
    {
        //error
        return false;
    }
    elementStack.push(token.getTokenField());
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
            ;
            return true;
        }
        case(SIMPLE_TEXT):
        {
            element->setValue(token.getTokenField());
            return true;
        }
        case(START_TAG):
        {
            XMLNode *child = parseElement(element);
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
    if (getNextToken()!=SIMPLE_TEXT)
    {
        //error
        return false;
    }
    if (elementStack.top()!=token.getTokenField()
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
    if(getNextToken()!=SIMPLE_TEXT)
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
    return false;
}

Attribute Parser::cdataToAttribute()
{
    return Attribute("_cdata",token.getTokenField());
}