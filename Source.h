//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H
#include <fstream>
using namespace std;

/**
 * Klasa reprezentujaca plik zrodlowy.
 * Udostepnia funkcje pobierania nastepnych znakow, cofniecia pozycji oraz pobranie aktualnej pozycji w pliku.
 */
class Source
{

    FILE* inputFile;



    unsigned int column_number;
    unsigned int line_number;

public:
    Source(string fileName);
    virtual ~Source();

    char getNextChar();
    void ungetChar(char c);

    unsigned int getColumn_number() const;

    unsigned int getLine_number() const;


};


#endif //TKOM_SOURCE_H
