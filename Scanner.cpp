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

Scanner::Scanner(Source &s) : src(s) {
    scanErrors = 0;
    //nextc();
}

void Scanner::nextc() {
    c = src.getNextChar();
}

void Scanner::scanError(string errorMessage) {
    cout << "Lexer error (" << src.getLine_number() << "," << src.getColumn_number() << "). " << errorMessage << endl;
    scanErrors++;
}

void Scanner::skipChar(int number)
{
    for (int i=0; i<number && c!=EOF;++i)
    {
        nextc();
    }
}

char Scanner::getCharAfterCurrent() {
    return src.checkChar();
}

bool Scanner::checkCDATASpelling() {
    string cdata = "CDATA[";
    for (int i=0;i <6;++i)
    {
        nextc();
        if (c==EOF || c!=cdata[i]) return false;
    }
    return true;
}

bool Scanner::isCorrectTextChar(char s) {
    return (isalpha(s) || s == '_' || s == '-' || isdigit(s) || s =='\'');
}

bool Scanner::isWhitespace(char s) {
    return (s == ' ' || s=='\n' || s =='\t');
}



Token Scanner::nextToken() {
    string text = "";
    nextc();
    while (c!=EOF && isWhitespace(c) ) nextc();//Skipping whitespaces
    if (c == EOF) return Token(END_OF_FILE, "EOF", src.getLine_number(), src.getColumn_number());

    switch (c) {
        //open tag
        case '<': {
            //nextc();
            // Close Tag
            switch(getCharAfterCurrent())
            {
                case '/':
                {
                    nextc();
                    return Token(CLOSE_TAG,"</", src.getLine_number(), src.getColumn_number());
                }
                case '?':
                {
                    skipChar(2); // Skip to next position after "<?"
                    while (c != EOF && c != '?') {
                        text += c;
                        nextc();
                    }
                    if (c == EOF) {
                        scanError("Unexpected end of file.");
                    } else {
                        nextc();
                        if (c != '>') scanError("Expected '>' after '?'.");

                    }
                    return Token(PROLOG_TAG, text, src.getLine_number(), src.getColumn_number());
                }
                case '!':
                {
                    skipChar(2); //Skip to next position after "<!"
                    if (c == '-') //comment
                    {
                        nextc();
                        if (c != '-') scanError("Expected double '-'");
                        while (c != EOF && c != '-' && getCharAfterCurrent() != '-') {
                            text += c;
                            nextc();
                        }
                        if (c == EOF) scanError("Unexpected end of file.");
                        else {
                            skipChar(2);
                            if (c != '>') scanError("Expected '>' After '--'.");
                        }
                        return Token(COMMENT_TAG, "", src.getLine_number(), src.getColumn_number());
                    } else if (c == '[') // CDATA
                    {
                        if (!checkCDATASpelling()) {
                            if (c == EOF) scanError("Unexpected end of file.");
                            else scanError("CDATA spelling error");
                        } else {
                            while (c != EOF && c != '[' && getCharAfterCurrent() != '[') {
                                nextc();
                                text += c;
                            }
                            if (c == EOF) scanError("Unexpected end of file.");
                            else {
                                skipChar(2);
                                if (c == EOF) scanError("Unexpected end of file.");
                                else if (c != '>') scanError("Expected '>'.");
                            }
                        }
                        return Token(CDATA_TAG, "", src.getLine_number(), src.getColumn_number());
                    }
                    else
                    {
                        /*<! ....*/
                    }
                }
                default:
                {
                    return Token(START_TAG, "<", src.getLine_number(), src.getColumn_number());
                }
            }
        }
            //end tag
        case '>': {
            return Token(END_TAG, ">", src.getLine_number(), src.getColumn_number());
        }
            //empty tag
        case '/': {
            nextc();
            if (c != '>') scanError("Missing '>' after '/'");
            return Token(EMPTY_TAG, "/>", src.getLine_number(), src.getColumn_number());
        }
            //equal tag
        case '=': {
            return Token(EQUAL_TAG, "=", src.getLine_number(), src.getColumn_number());
        }
            /*Atributtes can be opened by ' or " */
        case '\'': {
            return processAtributte();
        }
        case '"': {
            return processAtributte();
        }
        default: //Simple Text
        {
            text+=c;
            while (getCharAfterCurrent()!=EOF && isCorrectTextChar(getCharAfterCurrent()))
            {
                nextc();
                text+=c;
            }
            //if (c==EOF) scanError("Unexpected end of file");
            return Token(SIMPLE_TEXT, text, src.getLine_number(), src.getColumn_number());
        }

    }
}

Token Scanner::processAtributte() {
    string s = "";
    char endQuote = c;
    nextc();
    while (c != EOF && !isWhitespace(c) && c != endQuote) {
        s += c;
        nextc();
    }
    if (c == EOF) scanError("Unexpected end of file.");
    if (isWhitespace(c)) scanError("Atributtes cant have whitespaces.");
    if (c!=endQuote) scanError("Atributtes must be closed by the same quote ");

    return Token(ATRIBBUTE, s, src.getLine_number(), src.getColumn_number());
}