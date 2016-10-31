//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Source.h"
#include <iostream>

Source::Source(string fileName)
{
    inputFile = fopen(fileName.c_str(),"r");

    if (!inputFile)
    {
        column_number = 0;
        line_number = 1;

    }
    else
    {
        cerr << "Cannot read file " << fileName << endl;
    }

}

Source::~Source()
{
    if (!inputFile)
    {
        fclose(inputFile);
    }
}

void Source::feedContainer()
{
    charContainer.push(getc(inputFile));
}
/**
 * Pobieranie nastepnego znaku z pliku zrodlowego
 * @return Akutalny znak pliku zrodlowego
 */
char Source::getNextChar()
{

    if (charContainer.empty()) feedContainer();
    char c = charContainer.front();
    charContainer.pop();
    return c;
}
/**
 *
 * @return
 */
char Source::checkChar()
{
    feedContainer();
    return charContainer.back();
}
/**
 * Cofniecie pozycji w pliku zrodlowym.
 * @param c Aktualny znak
 */
void Source::ungetChar(char c)
{
    ungetc(c, inputFile);
}


unsigned int Source::getColumn_number() const {
    return column_number;
}

unsigned int Source::getLine_number() const {
    return line_number;
}
