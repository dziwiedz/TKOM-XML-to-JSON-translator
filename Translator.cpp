//
// Created by Łukasz Niedźwiedź on 18/01/17.
//

#include "Translator.h"
#include <dirent.h>
#include <iostream>
#include <fstream>
namespace Translator {
    const string JSONExtension = ".json";

    const string XMLExtension = ".xml";

    void translateFile(string filePath) {
        ErrorHandler errorHandler;
        Source source(filePath);
        Lexer lexer(source, &errorHandler);
        Parser parser(lexer, &errorHandler);
        XMLElement *xmlRoot;
        xmlRoot = parser.parse();
        cout << grepFileNameFromFilePath(filePath) << "\tPath: " << grepDirectoryFromFilePath(filePath) << endl;
        ofstream file;
        file.open(grepDirectoryFromFilePath(convertToJsonPath(filePath)), ios::out | ios::binary);
        if (file.is_open()) {
            if (errorHandler.isErrorOccured()) {
                file << errorHandler.getErrorMessage();
            } else {
                JSObject *jsonRoot = new JSObject();
                jsonRoot->addNewPair(xmlRoot->convertToJs());
                jsonRoot->saveToFile(file);
            }
            file.close();
        }

    }

    void testFolder(string directoryPath) {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(directoryPath.c_str())) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                string filePath(ent->d_name);
                if (filePath.substr(filePath.find_last_of(".") ) == XMLExtension) {
                    filePath = directoryPath + "/" + filePath;
                    testFile(filePath);
                }
            }
            closedir(dir);
        } else {
            perror("Could not open directory\n");
        }

    }

    void testFile(string pathFile) {
        cout << "\033[34m" << " \nFile path: " << "\033[39m" << grepDirectoryFromFilePath(pathFile) << endl;
        cout << "\033[34m" << "File name: " << "\033[39m" << grepFileNameFromFilePath(pathFile)<< XMLExtension << endl;
        ErrorHandler errorHandler;
        Source source(pathFile);
        Lexer lexer(source, &errorHandler);
        Parser parser(lexer, &errorHandler);
        XMLElement *xmlRoot;
        xmlRoot = parser.parse();
        if (errorHandler.isErrorOccured()) errorHandler.printErrorMessage();
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
                    cout << "\033[32mParse Successful!\033[39m\n";
                }
                jsonFile.close();
            } else { cout << "Couldn't create file.\n"; }
        }
    }

    string grepFileNameFromFilePath(string filePath){
        string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
        fileName = fileName.substr(0,fileName.find_last_of('.'));
        return fileName;
    }

    string grepDirectoryFromFilePath(string filePath){
        return filePath.substr(0, filePath.find_last_of("/\\"));
    }

    string convertToJsonPath(string filePath){
        return grepDirectoryFromFilePath(filePath)+grepFileNameFromFilePath(filePath)+JSONExtension;
    }

}