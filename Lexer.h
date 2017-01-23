//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SCANNER_H
#define TKOM_SCANNER_H


#include "Source.h"
#include "Token.h"
#include "ErrorHandler.h"

/**
 * Skaner.
 */
class Lexer
{
public:
    Lexer(Source &s, ErrorHandler* handler);

    virtual ~Lexer();

    Token nextToken(bool);

private:
    Source& src;
    char c;
    ErrorHandler* errorHandler;


    void nextc(); //ustawia wskaznik na nastepny znak

    Token scanError(string errorMessage); // wyswietlanie komunikatu o bledzie

    char getNextChar(); // ustawia wskaznik na nastepny znak i go zwraca

    char processCharacterEntity(); // rozpoznanie znakow specjalnych

    string processCharacter(bool processEntity);

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

    Token processArgumentName();

    Token processInstruction();

    static inline std::string &rtrim(std::string &s);



};


#endif //TKOM_SCANNER_H
