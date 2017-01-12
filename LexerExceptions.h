//
// Created by Łukasz Niedźwiedź on 12/01/17.
//

#ifndef TKOM_LEXEREXCEPTIONS_H
#define TKOM_LEXEREXCEPTIONS_H
#include <exception>
#include <string>
using namespace std;

class LexerExceptions : public exception {
    string errorMessage;
public:
    LexerExceptions(int line, int column, const string& error)
            : errorMessage(string("Lexer error at("+to_string(line)+","+to_string(column)+") : " + error))
            {}

    virtual const char* what() const throw()
    {
        return errorMessage.c_str();
    }

};


#endif //TKOM_LEXEREXCEPTIONS_H
