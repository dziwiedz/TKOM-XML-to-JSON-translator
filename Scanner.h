//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include "Source.h"
#include "Token.h"
/**
 * Skaner.
 */
class Scanner
{
    Source& src;
    char c;

    void nextc();

public:
    Scanner(Source &s);

    virtual ~Scanner();

    bool isWhiteSpace(char s);

    Token nextToken();

};


#endif //TKOM_SCANNER_H
