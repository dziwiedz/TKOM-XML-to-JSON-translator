//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include "Atoms.h"
#include <string>
using namespace std;
class Token {
private:
    Atoms tokenType;
    string tokenField;
    int line;
    int column;
public:
    const string &getTokenField() const;

    Token();
    Token(Atoms a, std::string s, int l, int c);
    virtual ~Token();

    Atoms getTokenType() const;

    const string getTokenTypeString();

    int getLine() const;

    int getColumn() const;

};


#endif //TKOM_TOKEN_H
