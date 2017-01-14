//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_JSVALUE_H
#define TKOM_JSVALUE_H

#include <string>
#include "JSNode.h"


using namespace std;

class JSValue : public JSNode {
public:
    JSValue(const string &value);

    void print();


private:
    string value;
};


#endif //TKOM_JSVALUE_H
