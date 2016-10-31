//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Scanner.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdio.h>

Scanner::~Scanner() {

}

Scanner::Scanner(Source &s) : src(s)
{
    scanErrors=0;
    nextc();
}

void Scanner::nextc()
{
    c=src.getNextChar();
}
char Scanner::getCharAfterCurrent()
{
    return src.checkChar();
}


void Scanner::scanError(string errorMessage)
{
    cout << "Lexer error (" << src.getLine_number() << "," << src.getColumn_number() << "). " << errorMessage << endl;
    scanErrors++;


}

bool Scanner::isWhitespace(char s) {
    if (s == ' ') return true;
    else return false;
}

bool Scanner::isCorrectTextChar()
{
    return (isalpha(c) || c=='_' || c=='-' || isdigit(c)) ;
}

Token Scanner::nextToken()
{
    string text = "";
    do{
        while(isWhitespace(c)) nextc();
        if (c==EOF) return Token(END_OF_FILE,"EOF",src.getLine_number(),src.getColumn_number());
        //@TODO if dla komenatrzy
        switch (c)
        {
            case '<':
            {
                nextc();
                if (c=='?') // prolog
                {
                    nextc();
                    while (c!=EOF && c!='?')
                    {
                        text +=c;
                        nextc();
                    }
                    if (c==EOF)
                    {
                        scanError("Unexpected end of file.");

                    }else
                    {
                        nextc();
                        if (c!='>') scanError("Expected '>' after '?'.");

                    }



                    return Token(PROLOG_TAG,text,src.getLine_number(),src.getColumn_number());
                } else if (c=='-') //comment
                {



                    return Token(COMMENT_TAG,"",src.getLine_number(),src.getColumn_number());
                }else if( c=='[') // CDATA
                {



                    return Token(CDATA_TAG,"",src.getLine_number(),src.getColumn_number());
                }

                return Token(START_TAG,"<",src.getLine_number(),src.getColumn_number());

            }

            case '>':
            {
                return Token(END_TAG,">",src.getLine_number(),src.getColumn_number());
            }

            case '/':
            {
                nextc();
                if (c!='>') scanError("Missing '>' after '/'");
                return Token(EMPTY_TAG,"/>",src.getLine_number(),src.getColumn_number());
            }

            case '=':
            {
                return Token(EQUAL_TAG,"=",src.getLine_number(),src.getColumn_number());
            }
            case '\'':
            {
                return processAtributte();
            }
            case '"':
            {
                return processAtributte();
            }
            default: //Simple Text
            {
                while (c!= EOF && isCorrectTextChar())
                {
                    text+=c;
                    nextc();
                }

                return Token(SIMPLE_TEXT,text,src.getLine_number(),src.getColumn_number());
            }


        }

    }while(isWhitespace(c));
}

Token Scanner::processAtributte()
{
    string s = "";
    char endQuote = c;
    nextc();
    while(c!= EOF && isWhitespace(c) && c!=endQuote)
    {
        s+=c;
        nextc();
    }
    if (c==EOF) scanError("Unexpected end of file.");
    if (isWhitespace(c)) scanError("Atributtes cant have whitespaces.");

    return Token(ATRIBBUTE, s, src.getLine_number(), src.getColumn_number());
}
