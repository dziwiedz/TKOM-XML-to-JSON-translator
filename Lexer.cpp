//
// Created by Łukasz Niedźwiedź on 29/10/16.
//

#include "Lexer.h"
#include <iostream>


Lexer::~Lexer() {

}

Lexer::Lexer(Source &s, ErrorHandler* handler) : src(s), errorHandler(handler) {
    nextc();
}
/**
 * Pobiera kolejny znak z zrodla
 */
void Lexer::nextc() {
    c = src.getNextChar();
}
/**
 * Wyswietla komunikat o bledzie i numerze lini oraz wiersza w ktorym wystapil.
 * Konczy dzialanie programu.
 * @param errorMessage
 */
Token Lexer::scanError(string errorMessage) {
    errorHandler->setLexerError(errorMessage,src.getLine_number(),src.getColumn_number());
    return Token(END_OF_FILE,"",src.getLine_number(),src.getColumn_number());
}

/**
 * Pobiera i zwraca kolejny znak z zrodla
 * @return
 */
char Lexer::getNextChar() {
    nextc();
    return c;
}

/**
 * Simple text cannot contain whitespace
 * @return True if current char isn't whitespace
 */
bool Lexer::isCorrectTextChar() {
    return (isalpha(c) || isdigit(c) || (ispunct(c) && c!='<')); //Powinno byc bez c!='=' ..., zrobione tylko do testow
}
/**
 * Check if current char is whitespace
 * @return True if current char is whitespace
 */
bool Lexer::isWhitespace() {
    return isspace(c);
}


/**
 * Podaje nastepny token.
 * Konwencja: Po znalezniu tokena, ustawia skaner na pierwszym nieprzeczytanym znaku.
 * @return Next token
 */
Token Lexer::nextToken(bool keepSpaces) {
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
            if (c != '>') return scanError("Missing '>' after '/'");
            return Token(END_EMPTY_TAG, "/>", src.getLine_number(), src.getColumn_number());
        }
            //equal tag
        case '=': {
            nextc();
            return Token(EQUAL_TAG, "=", src.getLine_number(), src.getColumn_number());
        }
            /*Atributtes can be opened by ' or " */
        case '\'': {
            if (keepSpaces) return processText(keepSpaces);
            else return processQuotedText();
        }
        case '"': { /*Cytowany teskt nie moze zawierac spacji, a zwykly tekst moze zawierac spacje i moze rozpoczynac sie od "*/
            if (keepSpaces) return processText(keepSpaces);
            else return processQuotedText();
        }
        default: //Simple Text
        {
            if (keepSpaces) return processText(keepSpaces);
            else return processArgumentName();

        }
    }
}

Token Lexer::processText(bool keepSpaces) {
    string text = "";
    char entity;
    if (c=='"') text +='\\';
    text+=c;
    while (getNextChar()!=EOF  && (isCorrectTextChar() || (keepSpaces && isWhitespace())))
    {
        text+=processCharacter(true);
    }
    text = rtrim(text);
    if (keepSpaces) return Token(SIMPLE_TEXT, text, src.getLine_number(), src.getColumn_number());
    else return Token(ATTRIBUTE_NAME, text, src.getLine_number(), src.getColumn_number());
}

Token Lexer::processArgumentName() {
    string text = "";
    text+=c;
    while (getNextChar()!=EOF && c!='=' && c!='>' && c!='/' && (isCorrectTextChar()  || (!isWhitespace())))
    {
        text+=processCharacter(true);
    }
    return Token(ATTRIBUTE_NAME, text, src.getLine_number(), src.getColumn_number());
}

/**
 * Analiza znacznika rozpoczynajacego sie od znaku '<'
 * Analiza rozpoczyna sie na nastepnym znaku po wystapieniu '<'
 * @return
 */
Token Lexer::processLeftLessSign()
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
Token Lexer::processProlog() {
    string text = "";
    while (getNextChar()!=EOF && c!='?') text+=c;
    if (c == EOF) return scanError("Unexpected end of file.");
    else if (getNextChar() != '>') return scanError("Expected '>' after '?'.");
    nextc();
    return Token(PROCESS_INST, text, src.getLine_number(), src.getColumn_number());

}
/**
 * Analiza poprawnosci tokenu typu Comment <!-- ... -->
 * Analiza rozpoczyna sie po pierwszym wystapieniu znaku '-'
 * @return
 */
Token Lexer::processComment() {
    if (getNextChar() != '-') return scanError("Expected double '-'");
    bool dashAppeared = false;
    while (getNextChar() != EOF && !(c=='-' && dashAppeared)) {
        dashAppeared = (c=='-');
    }
    if (c == EOF) return scanError("Unexpected end of file.");
    else if (getNextChar() != '>') return scanError("Expected '>' After '--'.");
    nextc();
    return Token(COMMENT, "", src.getLine_number(), src.getColumn_number());
}
/**
 * Analiza tokenu typu CDATA
 * Analiza rozpoczyna sie od znaku '['.
 * @return
 */
Token Lexer::processCdata() {

    if (!checkCDATASpelling()) {
        if (c == EOF) return scanError("Unexpected end of file.");
        else return scanError("CDATA spelling error");
    }
    string value = "";
    bool squareBracketAppered = false;
    while (getNextChar()!=EOF && !(c==']' && squareBracketAppered)) {
        squareBracketAppered = (c==']');
        value +=processCharacter(false);
    }
    if (c == EOF) return scanError("Unexpected end of file.");
    if ( getNextChar() != '>') return scanError("Expected '>' After ']]'.");
    nextc();
    return Token(CDATA, value, src.getLine_number(), src.getColumn_number());
}

/**
 * Check if CDATA is properly formated
 * @return True if properly formated, false if not
 */
bool Lexer::checkCDATASpelling() {
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
Token Lexer::processDoctype() {

    if (!checkDoctypeSpelling()) {
        if (c == EOF) return scanError("Unexpected end of file.");
        else return scanError("DOCTYPE spelling error");
    }

    while (c!=EOF && c!='>') nextc();
    if (c!='>') return scanError("Unexpected end of file.");
    nextc();
    return Token(DOCTYPE, "", src.getLine_number(), src.getColumn_number());
}

/**
 * Check if DOCTYPE is properly formated
 * @return True if properly formated, false if not
 */
bool Lexer::checkDoctypeSpelling() {
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
Token Lexer::processQuotedText() {
    string text = "";
    char entity;
    char endQuote = c;
    while (getNextChar() != EOF && !isWhitespace() && c != endQuote) {
        text+=processCharacter(true);
        if (c=='\0') return Token(END_OF_FILE,"",src.getLine_number(),src.getColumn_number());
    }
    if (c == EOF) return scanError("Unexpected end of file.");
    if (isWhitespace()) return scanError("Quoted text can't have whitespaces.");
    if (c!=endQuote) return scanError("Quoted text must be closed by the same quote ");
    nextc();
    return Token(QUOTED_TEXT, text, src.getLine_number(), src.getColumn_number());
}

/**
 * &lt;   change to <
 * &gt;   change to >
 * &amp;  change to  &
 * &apos; change to '
 * &quot; change to "
 * @return
 */
char Lexer::processCharacterEntity() {
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
/**
 * Przycinanie od prawej strony
 * @param s
 * @return
 */
inline std::string &Lexer::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

string Lexer::processCharacter(bool processEntity) {
    string text;
    if (c=='&' && processEntity) c=processCharacterEntity();
    if (c=='"' || c=='\\') text+='\\';
    text+=c;
    return text;
}