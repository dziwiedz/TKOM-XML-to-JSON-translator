//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_ATOMS_H
#define TKOM_ATOMS_H

enum SymType
{

};

enum ScanErrors
{

};

enum Atoms
{
    COMMENT, // <!-- COMMENT -->
    PROLOG, // <?xml version="1.0" encoding="UTF-8"?>
    SIMPLE_TEXT,
    CDATA, // <![CDATA[ ... ]]>

    START_TAG, // '<'
    START_CLOSE_TAG, // '</'
    END_TAG, // '>'
    END_EMPTY_TAG, // '/>'

    QUOTED_TEXT, // <note ATTRIBUTE='12'> </note>

    EQUAL_TAG, // '='
    DOCTYPE, //
    END_OF_FILE
};
static const char * EnumStrings[] = { "COMMENT", "PROLOGG", "SIMPLE_TEXT","CDATA","START_TAG","START_CLOSE_TAG","END_TAG","END_EMPTY_TAG","QUOTED_TEXT","EQUAL_TAG","DOCTYPE","END_OF_FILE"};

#endif //TKOM_ATOMS_H
