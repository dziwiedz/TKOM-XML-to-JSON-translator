//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Source.h"
#include <iostream>

Source::Source(string fileName)
{
    inputFile = fopen(fileName.c_str(),"r");

    if (inputFile)
    {
        column_number = 0;
        line_number = 1;

    }
    else
    {
        cout<< "Cannot read file " << fileName << endl;
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
    char s = getc(inputFile);
    charContainer.push(s);
}
/**
 * Pobieranie nastepnego znaku z pliku zrodlowego
 * @return Akutalny znak pliku zrodlowego
 */
char Source::getNextChar()
{

    if (charContainer.empty()) feedContainer();
    char c = charContainer.front();
    switch (c)
    {
        case '\t':
        {
            column_number+=8;
            break;
        }
        case '\n':
        {
            column_number=0;
            ++line_number;
            break;
        }
        default:
        {
            ++column_number;
            break;
        }
    }
    charContainer.pop();
    return c;
}
/**
 *
 * @return
 */
char Source::checkChar()
{
    if (charContainer.empty()) feedContainer();
    return charContainer.front();
}


unsigned int Source::getColumn_number() const {
    return column_number;
}

unsigned int Source::getLine_number() const {
    return line_number;
}
