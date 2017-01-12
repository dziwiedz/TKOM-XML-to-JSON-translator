//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include "Source.h"
#include "Token.h"
#include "LexerExceptions.h"
/**
 * Skaner.
 */
class Lexer
{
public:
    Lexer(Source &s);

    virtual ~Lexer();

    Token nextToken(bool);

private:

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

    Token processText(bool);

//    @TODO Dodac przycinania SimpleText od prawej strony




};


#endif //TKOM_SCANNER_H
