//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "Lexer.h"
#include "XMLTree.h"
#include "ParserExceptions.h"
#include <stack>
class Parser {
    Lexer& scn;
    Token token;
    Token backToken;
    stack<string> elementStack;

    XMLNode* parseElement();
    bool parseContent(XMLNode*);
    bool parseOpenBody(XMLNode*);
    bool parseCloseBody(XMLNode*);
    bool parseAttributes(XMLNode*);
    bool parseMiscelanus();
    Atoms getNextToken();
    Atoms getNextTokenWithSpaces();
    Atoms tokenType();
    Attribute cdataToAttribute();

//    Parse error functions
    void wrongTokenException(string);
    void stackException(string);


public:
    Parser(Lexer &s);

    virtual ~Parser();


    XMLNode* parse();






};


#endif //TKOM_PARSER_H
