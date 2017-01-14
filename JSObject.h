//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_JSONODE_H
#define TKOM_JSONODE_H
#include "JSNode.h"
#include "JSPair.h"

#include <vector>

using namespace std;

class JSObject : public JSNode  {
public:
    JSObject();

    void addNewPair(JSPair*);

    void print();
private:
    vector<JSPair*> members;

};


#endif //TKOM_JSONODE_H
