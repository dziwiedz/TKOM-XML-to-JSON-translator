#include <iostream>
#include "Translator.h"

void standardTests();
void folderTest();
void fileTest();
void translateFile();
string pickPath();
void interface();
void actionCheck(int choice);
int main() {
    interface();
    return 0;
}

void interface()
{
    int choice;
    do {
        cout << "Translator XML - JSON\n";
        cout << "1. Standard tests.\n";
        cout << "2. Test all files in directory with xml extension\n";
        cout << "3. Test file\n";
        cout << "4. Translate file from XML to JSON.\n";
        cout << "5. Exit\n";
        cout << "~>";
        cin >> choice;
        actionCheck(choice);
    }while(choice!=5);
}

void actionCheck(int choice){
    switch (choice){
        case(1):{
            standardTests();
            break;
        }
        case(2):{
            folderTest();
            break;
        }
        case(3):{
            fileTest();
            break;
        }
        case (4):{
            translateFile();
            break;
        }
    }
}

void standardTests()
{
    cout << "Test poprawnosci zapisu plikow do JSON:\n";
    cout << "Cel testow: Wykazanie poprawnego przeksztalcania na format danowy typu JSON.\n";
    Translator::testFolder("/Users/Dzwiedz/ClionProjects/TKOM/tests/simpleTests");
    cout << "Nacisnij dowolny klawisz"; getchar(); getchar();

    cout << "\n\n\nTest poprawnosci dzialania parsera:\n";
    cout << "Cel testow: Wykazanie poprawnego dzialania analizatora skladniowego.\n";
    Translator::testFolder("/Users/Dzwiedz/ClionProjects/TKOM/tests/ParserErrorTests");
    cout << "Nacisnij dowolny klawisz"; getchar();

    cout << "\n\n\nTest poprawnosci dzialania lexera:\n";
    cout << "Cel testow: Wykazanie poprawnego dzialania analizatora leksykalnego.\n";
    Translator::testFolder("/Users/Dzwiedz/ClionProjects/TKOM/tests/LexerErrorTests");
    cout << "Nacisnij dowolny klawisz"; getchar();

    cout << "\n\n\nTest poprawnosci dzialania na duzych plikach XML:\n";
    cout << "Cel testow: Wykazanie poprawnego dzialania na duzych plikach XML.\n";
    Translator::testFolder("/Users/Dzwiedz/ClionProjects/TKOM/tests/bigDatasetsTests");
    cout << "Nacisnij dowolny klawisz"; getchar();
}

void folderTest()
{
    Translator::testFolder(pickPath());
}

void fileTest()
{
    Translator::testFile(pickPath());
}
void translateFile()
{
    Translator::translateFile(pickPath());
}

string pickPath()
{
    string path;
    cout << "Wprowadz sciezke: ";
    cin >> path;
    return path;
}