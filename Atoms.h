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
    COMMENT_TAG, // <!-- COMMENT -->
    PROLOG_TAG, // <?xml version="1.0" encoding="UTF-8"?>
    SIMPLE_TEXT,
    CDATA_TAG, // <![CDATA[ ... ]]>

    START_TAG, // '<'
    CLOSE_TAG, // '</'
    END_TAG, // '>'
    EMPTY_TAG, // '/>'

    ATRIBBUTE, // <note ATTRIBUTE='12'> </note>

    EQUAL_TAG, // '='
    PARAGRAPH_NAME, //
    END_OF_FILE
};
static const char * EnumStrings[] = { "COMMENT_TAG", "PROLOG_TAG", "SIMPLE_TEXT","CDATA_TAG","START_TAG","CLOSE_TAG","END_TAG","EMPTY_TAG","ATRIBBUTE","EQUAL_TAG","PARAGRAPH_NAME","END_OF_FILE"};

#endif //TKOM_ATOMS_H
