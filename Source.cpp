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
    char c = getc(inputFile);
    ++line_number;
    
}

char Source::getNextChar()
{

    /*
    char c = getc(inputFile);
    ++column_number;

    if (c=='\n');
    {
        ++line_number;
        column_number=0;
    }
    return c;
     */
}


unsigned int Source::getColumn_number() const {
    return column_number;
}

unsigned int Source::getLine_number() const {
    return line_number;
}
