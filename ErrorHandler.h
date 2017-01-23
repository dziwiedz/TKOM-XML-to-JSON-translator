//
// Created by Łukasz Niedźwiedź on 19/01/17.
//

#ifndef TKOM_ERRORHANDLER_H
#define TKOM_ERRORHANDLER_H
#include <string>
using namespace std;

class ErrorHandler {
public:
    void setParserError(string message, unsigned int l, unsigned int c);

    void setLexerError(string message, unsigned int l, unsigned int c);

    void setSourceError(string message);

    ErrorHandler();

    const string &getErrorMessage() const;

    void printErrorMessage();

    bool isErrorOccured() const;

private:
    string errorMessage;
    bool errorOccured;

};


#endif //TKOM_ERRORHANDLER_H
