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

    unsigned int scanErrors;

    void nextc();

    void skipChar(int number);

    void scanError(string errorMessage);

    char getCharAfterCurrent();

    bool checkCDATASpelling();

    bool isCorrectTextChar(char s);

    bool isWhitespace(char s);

    Token processAtributte();


public:
    Scanner(Source &s);

    virtual ~Scanner();


    Token nextToken();


};


#endif //TKOM_SCANNER_H
