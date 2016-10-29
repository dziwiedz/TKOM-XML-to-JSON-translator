//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Scanner.h"


Scanner::~Scanner() {

}

Scanner::Scanner(Source &s) : src(s)
{
    nextc();
}

void Scanner::nextc()
{
    c=src.getNextChar();
}

bool Scanner::isWhiteSpace(char s) {
    if (s == ' ') return true;
    else return false;
}