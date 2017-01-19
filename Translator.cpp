//
// Created by Łukasz Niedźwiedź on 18/01/17.
//

#include "Translator.h"
#include <dirent.h>
#include <iostream>
#include <fstream>

Translator::Translator() {
}

Translator::~Translator() {
}

void Translator::translateFile(string pathFile){

}
void Translator::testFolder(string directoryPath){
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(directoryPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL ) {
//            printf("Name: %s, Path: %s \n", ent->d_name, directoryPath.c_str());
            string filePath(ent->d_name);
            if (filePath.substr(filePath.find_last_of(".")+1) == "xml")
            {
                filePath = directoryPath + "/" + filePath;
                testFile(filePath);
            }
        }
        closedir(dir);
    }
    else {
        perror("Could not open directory\n");
    }

}
void Translator::testFile(string pathFile){
    cout << pathFile << endl;
    ErrorHandler errorHandler;
    Source source(pathFile);
    Lexer lexer(source,&errorHandler);
    Parser parser(lexer,&errorHandler);
    XMLElement* xmlRoot;
    xmlRoot = parser.parse();
    if (errorHandler.isErrorOccured())
    {

    }
    else {
        JSObject *jsonRoot = new JSObject();
        jsonRoot->addNewPair(xmlRoot->convertToJs());
        ofstream file;
        file.open("/Users/Dzwiedz/ClionProjects/TKOM/tests/test.json", ios::out | ios::binary);
        if (file.is_open()) {
            jsonRoot->saveToFile(file);
            file.close();
            std::ifstream jsonFile("/Users/Dzwiedz/ClionProjects/TKOM/tests/test.json", std::ifstream::binary);
            Json::Value root;
            Json::Reader reader;
            bool parsingSuccessful = reader.parse(jsonFile, root, false);
            if (!parsingSuccessful) cout << "Parsing error" << reader.getFormatedErrorMessages();
            else {
                cout << "Parse Successful!\n";
            }
            jsonFile.close();
        } else { cout << "Couldn't create file.\n"; }
    }



}
