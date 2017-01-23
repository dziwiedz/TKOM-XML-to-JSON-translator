//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H
#include <fstream>
#include "ErrorHandler.h"

using namespace std;

/**
struct TextPos
{
    unsigned int column_number;
    unsigned int line_number;

    TextPos(unsigned int l, unsigned int c) : line_number(l), column_number(c){};
};
 * Klasa reprezentujaca plik zrodlowy.
 * Udostepnia funkcje pobierania nastepnych znakow, cofniecia pozycji oraz pobranie aktualnej pozycji w pliku.
 */


class Source
{
public:
    Source(string fileName, ErrorHandler*);

    Source(ErrorHandler*);

    ~Source();

    void openFile(string filePath);

    char getNextChar();

    unsigned int getColumn_number() const;

    unsigned int getLine_number() const;

private:
    FILE* inputFile;
    unsigned int column_number;
    unsigned int line_number;
    ErrorHandler* errorHandler;
};


#endif //TKOM_SOURCE_H
