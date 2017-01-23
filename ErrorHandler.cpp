//
// Created by Łukasz Niedźwiedź on 19/01/17.
//

#include <cstdlib>
#include <iostream>
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
    if (!errorOccured) {
        errorMessage = "Parser error at line: " + to_string(l) + ", column: " + to_string(c) + "\nError: " + message + "\n";
        errorOccured = true;
    }
}

void ErrorHandler::setSourceError(string message) {
    if (!errorOccured)
    {
        errorMessage = "Source error.\nCouldn't open file\nFile path: " + message + "\n";
        errorOccured = true;
    }
}

void ErrorHandler::setLexerError(string message, unsigned int l, unsigned int c) {
    if (!errorOccured) {
        errorMessage = "Lexer error at line: " + to_string(l) + ", column: " + to_string(c) + "\nMessage : " + message + "\n";
        errorOccured = true;
    }
}

void ErrorHandler::printErrorMessage() {
    cout << "\033[31m" <<  errorMessage << "\033[49m";

}