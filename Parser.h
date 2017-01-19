//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "Lexer.h"
#include "XMLElement.h"
#include "XMLAttribute.h"
#include "ErrorHandler.h"
#include <stack>
class Parser {
public:
    Parser(Lexer &s, ErrorHandler* handler);

    virtual ~Parser();


    XMLElement* parse();

private:
    Lexer& scn;
    Token token;
    stack<string> elementStack;
    ErrorHandler* errorHandler;

    XMLElement* parseElement();
    XMLElement* parseOpenBody();
    bool parseContent(XMLElement*);
    bool parseCloseBody();
    vector<XMLAttribute*> parseAttributes();
    XMLAttribute* parseSingleAttribute();
    bool parseMiscelanus();
    Atoms getNextToken();
    Atoms getNextTokenWithSpaces();
    Atoms tokenType();
    XMLAttribute* cdataToAttribute();

//    Parse error functions
    void wrongTokenError(string);
    void stackError(string);






};


#endif //TKOM_PARSER_H
