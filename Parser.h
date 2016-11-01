//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_PARSER_H
#define TKOM_PARSER_H


#include "Scanner.h"

class Parser {
    Scanner& scn;
    Token token;
    Token backToken;

public:
    Parser(Scanner &s);

    virtual ~Parser();


};


#endif //TKOM_PARSER_H
