//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#ifndef TKOM_ATOMS_H
#define TKOM_ATOMS_H


enum Atoms
{
    COMMENT, // <!-- COMMENT -->
    PROLOG_INST, // <?xml version="1.0" encoding="UTF-8"?>
    PROCESS_INST,
    SIMPLE_TEXT,
    ATTRIBUTE_NAME,
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
static const char * EnumStrings[] = { "COMMENT",
                                      "PROLOG_INST",
                                      "PROCESS_INST",
                                      "SIMPLE_TEXT",
                                      "ATTRIBUTE_NAME" ,
                                      "CDATA",
                                      "START_TAG",
                                      "START_CLOSE_TAG",
                                      "END_TAG",
                                      "END_EMPTY_TAG",
                                      "QUOTED_TEXT",
                                      "EQUAL_TAG",
                                      "DOCTYPE",
                                      "END_OF_FILE"
};

#endif //TKOM_ATOMS_H
