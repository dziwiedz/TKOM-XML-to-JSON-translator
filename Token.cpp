//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Token.h"

Token::Token() {}
Token::Token(Atoms a, std::string s, int l, int c) : tokenType(a), tokenField(s), line(l), column(c)
{

}

Token::~Token() {

}

Atoms Token::getTokenType() const {
    return tokenType;
}

int Token::getLine() const {
    return line;
}

int Token::getColumn() const {
    return column;
}

const string &Token::getTokenField() const {
    return tokenField;
}
