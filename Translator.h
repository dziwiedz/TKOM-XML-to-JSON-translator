//
// Created by Łukasz Niedźwiedź on 18/01/17.
//

#ifndef TKOM_TRANSLATOR_H
#define TKOM_TRANSLATOR_H

#include "Lexer.h"
#include "Parser.h"
#include "include/json/json.h"
/**
 * Glowna klasa translatora
 * Udostepnia uslugi konwersji zadanego pliku XML na json, oraz testowanie poprawnosci translaotra
 */
namespace Translator {

    extern const string XMLExtension;

    extern const string JSONExtension;

    void translateFile(string pathFile);

    void testFolder(string directoryPath);

    void testFile(string pathFile);

    string grepFileNameFromFilePath(string filePath);

    string grepDirectoryFromFilePath(string filePath);

    string convertToJsonPath(string filePath);

}

#endif //TKOM_TRANSLATOR_H
