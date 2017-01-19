//
// Created by Łukasz Niedźwiedź on 13/01/17.
//

#ifndef TKOM_JSPAIR_H
#define TKOM_JSPAIR_H
#include "JSValue.h"
#include "JSNode.h"
#include <string>

class JSPair : public JSNode {
public:
    JSPair();

    JSPair(const string &name);

    JSPair( const string &name, JSNode *value);

    void setName(const string &name);

    void setValue(JSNode *value);

    void print();

    void saveToFile(std::ofstream&);

private:
    string name;
    JSNode* value;

};


#endif //TKOM_JSPAIR_H
