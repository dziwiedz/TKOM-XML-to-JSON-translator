//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Source.h"
#include <iostream>

Source::Source(string fileName)
{
    openFile(fileName);
}

Source::~Source()
{
    if (!inputFile)
    {
        fclose(inputFile);
    }
}

/**
 * Pobieranie nastepnego znaku z pliku zrodlowego
 * @return Akutalny znak pliku zrodlowego
 */
char Source::getNextChar()
{
    char c = (char)getc(inputFile);
    switch (c)
    {
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
    return c;
}


unsigned int Source::getColumn_number() const {
    return column_number;
}

unsigned int Source::getLine_number() const {
    return line_number;
}

void Source::openFile(string filePath) {
    inputFile = fopen(filePath.c_str(),"r");
    if (inputFile)
    {
        column_number = 0;
        line_number = 1;
    }
    else
    {
        cout<< "Cannot read file " << filePath << endl;
    }
}

Source::Source() {


}
