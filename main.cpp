#include <iostream>
#include <fstream>
#include "Source.h"
#include "Lexer.h"
#include "Parser.h"
#include "include/json/json.h"
#include "Translator.h"

int main() {
//    Source s("/Users/Dzwiedz/ClionProjects/TKOM/tests/simpleTests/namespaces.xml");
//    Lexer sc(s);
//    Parser parser(sc);
//    XMLElement *rootElement;
//    rootElement = parser.parse();
//    cout << "Done\n";
//    JSObject *jsonRoot = new JSObject();
//    jsonRoot->addNewPair(rootElement->convertToJs());
//    ofstream file;
//    file.open("/Users/Dzwiedz/ClionProjects/TKOM/example.json",ios::out | ios::in | ios::binary);
//    if (!file.is_open()) cout << "no open :(\n";
//    jsonRoot->print();
//    jsonRoot->saveToFile(file);
//    file.close();
//
//    std::ifstream jsonFile("/Users/Dzwiedz/ClionProjects/TKOM/example.json",std::ifstream::binary);
//    Json::Value root;
//    Json::Reader reader;
//    bool parsingSuccessful = reader.parse(jsonFile,root,false);
//    if (!parsingSuccessful) cout << "Parsing error" << reader.getFormatedErrorMessages();
//    else {
//        cout << "Parse Successful!\n";
//    }
//    jsonFile.close();

    Translator translator;
    translator.testFolder("/Users/Dzwiedz/ClionProjects/TKOM/tests/ParserErrorTests/");


  /*  do{
        vt.push_back(sc.nextToken(false));
        cout << EnumStrings[vt.back().getTokenType()] << " " << vt.back().getTokenField()  << endl;
    }while(vt.back().getTokenType()!=END_OF_FILE);*/

    return 0;
}