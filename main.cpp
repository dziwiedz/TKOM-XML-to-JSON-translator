#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;

    Source s("/Users/Dzwiedz/ClionProjects/TKOM/test.xml");
    Scanner sc(s);
    vector<Token> vt;
    do{
        vt.push_back(sc.nextToken());
        cout << EnumStrings[vt.back().getTokenType()] << " " << vt.back().getTokenField()  << endl;
    }while(vt.back().getTokenType()!=END_OF_FILE);

    return 0;
}