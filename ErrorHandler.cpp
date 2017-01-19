//
// Created by Łukasz Niedźwiedź on 19/01/17.
//

#include "ErrorHandler.h"

ErrorHandler::ErrorHandler() : errorOccured(false)
{}

const string &ErrorHandler::getErrorMessage() const {
    return errorMessage;
}

bool ErrorHandler::isErrorOccured() const {
    return errorOccured;
}

void ErrorHandler::setParserError(string message, unsigned int l, unsigned int c) {
    errorMessage = "Patser error at line: " + to_string(l) +", column: "+to_string(c) +"\nError: "+ message;
    errorOccured=true;
}

void ErrorHandler::setLexerError(string message, unsigned int l, unsigned int c) {
    errorMessage = "Lexer error at line: " + to_string(l) +", column: "+to_string(c) +"\nError: "+ message;
    errorOccured=true;
}