//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_JSARRAY_H
#define TKOM_JSARRAY_H



#include "JSValue.h"
#include <vector>
using namespace std;

class JSArray : public JSNode{
public:
    JSArray();

    void addNewElement(JSNode*);

    void print();
private:
    vector<JSNode*> elements;


};


#endif //TKOM_JSARRAY_H
