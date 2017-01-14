//
// Created by Łukasz Niedźwiedź on 14/01/17.
//

#ifndef TKOM_JSOBJECT_H
#define TKOM_JSOBJECT_H

enum JSType {Node, Array, Value, Pair};
/**
 * Klasa abstraykcyjna reprezentujaca obiekty JSON
 */
class JSNode {
public:
    JSNode(JSType type);

    virtual ~JSNode();

    virtual void print();

    JSType getType() const;

private:
    JSType type;


};


#endif //TKOM_JSOBJECT_H
