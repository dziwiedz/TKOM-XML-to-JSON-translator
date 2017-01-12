//
// Created by Łukasz Niedźwiedź on 12/01/17.
//

#ifndef TKOM_PARSEREXCEPTIONS_H
#define TKOM_PARSEREXCEPTIONS_H
#include <exception>
#include <string>

using namespace std;

class ParserException : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Parser Exception";
    }
};

class WrongTokenTypeException : public ParserException
{
    string errorMessage;
public: // Parser Error at (line,column):
    WrongTokenTypeException(const string& expected, const string& found, const int& line, const int&column)
            : errorMessage(string("Parser error at("+to_string(line)+","+to_string(column)+"): Expected token type: "+expected+", but get: "+found))
    {}

    virtual const char* what() const throw()
    {
        return errorMessage.c_str();
    }
};

class NameStackException : public ParserException
{
    string errorMessage;
public:
    NameStackException(const string& expected, const string& found, const int& line, const int&column)
            : errorMessage(string("Parser error at("+to_string(line)+","+to_string(column)+"): Expected element name: "+expected+", but get: "+found))
            {}

    virtual const char* what() const throw()
    {
        return errorMessage.c_str();
    }
};
#endif //TKOM_PARSEREXCEPTIONS_H
