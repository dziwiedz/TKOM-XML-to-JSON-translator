//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Token.h"

Token::Token() {}

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
