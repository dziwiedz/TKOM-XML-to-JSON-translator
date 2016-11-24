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

    void nextc(); //ustawia wskaznik na nastepny znak

    void scanError(string errorMessage); // wyswietlanie komunikatu o bledzie

    char getNextChar(); // ustawia wskaznik na nastepny znak i go zwraca

    char processCharacterEntity(); // rozpoznanie znakow specjalnych

    bool checkCDATASpelling();

    bool checkDoctypeSpelling();

    bool isCorrectTextChar();

    bool isWhitespace();

    Token processQuotedText();

    Token processLeftLessSign();

    Token processProlog();

    Token processComment();

    Token processCdata();

    Token processDoctype();


public:
    Scanner(Source &s);

    virtual ~Scanner();

    Token nextToken();


};


#endif //TKOM_SCANNER_H
