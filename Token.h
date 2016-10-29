//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include "Atoms.h"

class Token {
    Atoms tokenType;
    int line;
    int column;


public:
    Token();
    Token(Atoms atom, int l, int c);
    virtual ~Token();

    Atoms getTokenType() const;

    int getLine() const;

    int getColumn() const;

};


#endif //TKOM_TOKEN_H
