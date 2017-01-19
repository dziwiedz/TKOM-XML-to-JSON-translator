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
class Translator {
public:
    Translator();

    ~Translator();

    void translateFile(string pathFile);
    void testFolder(string directoryPath);
    void testFile(string pathFile);

private:

};


#endif //TKOM_TRANSLATOR_H
