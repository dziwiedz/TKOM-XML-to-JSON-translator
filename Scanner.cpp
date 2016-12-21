//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Scanner.h"
#include <iostream>


Scanner::~Scanner() {

}

Scanner::Scanner(Source &s) : src(s) {
    scanErrors = 0;
    nextc();
}
/**
 * Pobiera kolejny znak z zrodla
 */
void Scanner::nextc() {
    c = src.getNextChar();
}
/**
 * Wyswietla komunikat o bledzie i numerze lini oraz wiersza w ktorym wystapil.
 * Konczy dzialanie programu.
 * @param errorMessage
 */
void Scanner::scanError(string errorMessage) {
    cout << "Lexer error (" << src.getLine_number() << "," << src.getColumn_number() << "). " << errorMessage << endl;
    scanErrors++;
    exit(1);
}

/**
 * Pobiera i zwraca kolejny znak z zrodla
 * @return
 */
char Scanner::getNextChar() {
    nextc();
    return c;
}

/**
 * Simple text cannot contain whitespace
 * @return True if current char isn't whitespace
 */
bool Scanner::isCorrectTextChar() {
    return (isalpha(c) || isdigit(c) || (ispunct(c) && c!='<' && c!='=' && c!='>')); //Powinno byc bez c!='=' ..., zrobione tylko do testow
}
/**
 * Check if current char is whitespace
 * @return True if current char is whitespace
 */
bool Scanner::isWhitespace() {
    return isspace(c);
}


/**
 * Podaje nastepny token.
 * Konwencja: Po znalezniu tokena, ustawia skaner na pierwszym nieprzeczytanym znaku.
 * @return Next token
 */
Token Scanner::nextToken(bool keepSpaces) {
    while (c!=EOF && isWhitespace() ) nextc();//Skipping whitespaces
    if (c == EOF) return Token(END_OF_FILE, "EOF", src.getLine_number(), src.getColumn_number());

    switch (c) {
        //open tag
        case '<': {
            nextc();
            return processLeftLessSign();
        }
            //end tag
        case '>': {
            nextc();
            return Token(END_TAG, ">", src.getLine_number(), src.getColumn_number());
        }
            //empty tag
        case '/': {
            nextc();
            if (c != '>') scanError("Missing '>' after '/'");
            return Token(END_EMPTY_TAG, "/>", src.getLine_number(), src.getColumn_number());
        }
            //equal tag
        case '=': {
            nextc();
            return Token(EQUAL_TAG, "=", src.getLine_number(), src.getColumn_number());
        }
            /*Atributtes can be opened by ' or " */
        case '\'': {
            return processQuotedText();
        }
        case '"': {
            return processQuotedText();
        }
        default: //Simple Text
        {
            return processText(keepSpaces);
        }
    }
}

Token Scanner::processText(bool keepSpaces) {
    string text = "";
    text+=c;
    while (getNextChar()!=EOF && (isCorrectTextChar() || (keepSpaces && isWhitespace())))
    {
        if (c=='&') text+=processCharacterEntity();
        else text+=c;
    }
    //if (c==EOF) scanError("Unexpected end of file");
    //nextc();
    if (keepSpaces) return Token(SIMPLE_TEXT, text, src.getLine_number(), src.getColumn_number());
    else return Token(ATTRIBUTE_NAME, text, src.getLine_number(), src.getColumn_number());
}

/**
 * Analiza znacznika rozpoczynajacego sie od znaku '<'
 * Analiza rozpoczyna sie na nastepnym znaku po wystapieniu '<'
 * @return
 */
Token Scanner::processLeftLessSign()
{
    switch (c)
    {
        case '/': // </ Close Tag
        {
            nextc(); //
            return Token(START_CLOSE_TAG,"</", src.getLine_number(), src.getColumn_number());
        }

        case '?': // Prolog <? PROLOG ?>
        {
            return processProlog();
        }
        case '!':
        {
            nextc();
            switch (c)
            {
                case '-': // <!-- Comment -->
                {
                    return processComment();
                }
                case '[': // <[CData[ ... ]]>
                {
                    return processCdata();
                }
                default: //<!Doctype ... >
                {
                    return processDoctype();
                }
            }
        }
        default: // <
        {
            return Token(START_TAG, "<", src.getLine_number(), src.getColumn_number());
        }

    }
}
/**
 * Analiza poprawnosci tokenu typu Prolog : <? ... ?>
 * Analiza rozpoczyna sie po pierwszym wsytapieniu znaku '?'
 * @return Token typu prolog
 */
Token Scanner::processProlog() {
    string text = "";
    while (getNextChar()!=EOF && c!='?') text+=c;
    if (c == EOF) scanError("Unexpected end of file.");
    else {
        if (getNextChar() != '>') scanError("Expected '>' after '?'.");

    }
    nextc();
    return Token(PROCESS_INST, text, src.getLine_number(), src.getColumn_number());

}
/**
 * Analiza poprawnosci tokenu typu Comment <!-- ... -->
 * Analiza rozpoczyna sie po pierwszym wystapieniu znaku '-'
 * @return
 */
Token Scanner::processComment() {
    if (getNextChar() != '-') scanError("Expected double '-'");
    bool dashAppeared = false;
    while (getNextChar() != EOF && !(c=='-' && dashAppeared)) {
        dashAppeared = (c=='-');
    }
    if (c == EOF) scanError("Unexpected end of file.");
    else if (getNextChar() != '>') scanError("Expected '>' After '--'.");
    nextc();
    return Token(COMMENT, "", src.getLine_number(), src.getColumn_number());
}
/**
 * Analiza tokenu typu CDATA
 * Analiza rozpoczyna sie od znaku '['.
 * @return
 */
Token Scanner::processCdata() {

    if (!checkCDATASpelling()) {
        if (c == EOF) scanError("Unexpected end of file.");
        else scanError("CDATA spelling error");
    }
    string value = "";
    bool squareBracketAppered = false;
    while (getNextChar()!=EOF && !(c==']' && squareBracketAppered)) {
        squareBracketAppered = (c==']');
        value += c;
    }
    if (c == EOF) scanError("Unexpected end of file.");
    if ( getNextChar() != '>') scanError("Expected '>' After ']]'.");
    nextc();
    return Token(CDATA, value, src.getLine_number(), src.getColumn_number());
}

/**
 * Check if CDATA is properly formated
 * @return True if properly formated, false if not
 */
bool Scanner::checkCDATASpelling() {
    string cdata = "CDATA[";
    for (int i=0;i <6;++i)
    {
        if (getNextChar()==EOF || c!=cdata[i]) return false;
    }
    return true;
}

/**
 * Analiza tokenu typu DOCTYPE
 * @return
 */
Token Scanner::processDoctype() {

    if (!checkDoctypeSpelling()) {
        if (c == EOF) scanError("Unexpected end of file.");
        else scanError("DOCTYPE spelling error");
    }

    while (c!=EOF && c!='>') nextc();
    if (c!='>') scanError("Unexpected end of file.");
    nextc();
    return Token(DOCTYPE, "", src.getLine_number(), src.getColumn_number());
}

/**
 * Check if DOCTYPE is properly formated
 * @return True if properly formated, false if not
 */
bool Scanner::checkDoctypeSpelling() {
    string doctype ="DOCTYPE";
    for (int i =0; i <7 ; ++i)
    {
        if (c==EOF || c!=doctype[i]) return false;
        nextc();
    }
    return true;
}

/**
 * Analiza tekstu cytowanego
 * @return
 */
Token Scanner::processQuotedText() {
    string s = "";
    char endQuote = c;
    while (getNextChar() != EOF && !isWhitespace() && c != endQuote) {
        if (c == '&') s+=processCharacterEntity();
        else s += c;
    }
    if (c == EOF) scanError("Unexpected end of file.");
    if (isWhitespace()) scanError("Quoted text can't have whitespaces.");
    if (c!=endQuote) scanError("Quoted text must be closed by the same quote ");
    nextc();
    return Token(QUOTED_TEXT, s, src.getLine_number(), src.getColumn_number());
}

/**
 * &lt;   change to <
 * &gt;   change to >
 * &amp;  change to  &
 * &apos; change to '
 * &quot; change to "
 * @return
 */
char Scanner::processCharacterEntity() {
    nextc();
    switch (c)
    {
        case 'l':
        {
            if ( getNextChar() == 't' && getNextChar() == ';') return '<';
            else scanError("Not properly formated \"&lt;\"");
        }
        case 'g':
        {
            if (getNextChar() == 't' && getNextChar() == ';') return '>';
            else scanError("Not properly formated \"&gt;\"");
        }
        case 'a':
        {
            nextc();
            switch (c)
            {
                case 'm': // &amp;
                {
                    if (   getNextChar() == 'p' &&
                           getNextChar() == ';')
                        return '&';
                    else scanError("Wrong formated \"&mp;\"");
                }
                case 'p': // &apos;
                {
                    if (    getNextChar() == 'o' &&
                            getNextChar() == 's' &&
                            getNextChar() == ';')
                        return '\'';
                    else scanError("Wrong formated \"apos;\"");
                }
                default :
                {
                    scanError("Not properly formated entity.");
                }
            }
        }
        case 'q':
        {
            if (    getNextChar() == 'u' &&
                    getNextChar() == 'o' &&
                    getNextChar() == 't' &&
                    getNextChar() == ';')
                return '"';
            else scanError("Wrong formated \"quot;\"");
        }
        default:
        {
            scanError("Expected name of entity after '&'");
            return '\0';
        }
    }
}