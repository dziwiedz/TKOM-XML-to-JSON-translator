//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H
#include <fstream>
#include <queue>
using namespace std;
class Source
{

    FILE* inputFile;

    queue<char> fifoSymbolContainer; // @TODO do poprawienia nazwa



    unsigned int column_number;
    unsigned int line_number;
    void feedContainer();
public:
    Source(string fileName);
    virtual ~Source();

    char getNextChar();

    unsigned int getColumn_number() const;

    unsigned int getLine_number() const;


};


#endif //TKOM_SOURCE_H
