//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H
#include <fstream>
#include <queue>
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

    FILE* inputFile;
    queue<char> charContainer;
    unsigned int column_number;
    unsigned int line_number;

    void feedContainer();


public:
    Source(string fileName);

    virtual ~Source();

    char getNextChar();

    char checkChar();

    unsigned int getColumn_number() const;

    unsigned int getLine_number() const;


};


#endif //TKOM_SOURCE_H
