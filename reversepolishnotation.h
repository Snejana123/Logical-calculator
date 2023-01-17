#ifndef REVERSEPOLISHNOTATION_H
#define REVERSEPOLISHNOTATION_H

#include <QString>
#include "parametrslist.h"

class reversePolishNotation
{
public:
    reversePolishNotation();
    ~reversePolishNotation();
    void setExpression(QString expression);
    void setParametrList (parametrsList * currList);
    bool calculatePolishNot();
    void replaceParametrsWithValues();
    QString getPolishNot();
    QString getError();
    QString expr;
    //struct parametrsList * list = 0;
private:
    QString reversePolish;
    QString errorMessage;
    QString stack;
    parametrsList * list;
    //QString expr;
    bool isDelimeter(QChar symb);
    QString getOpAtPosition(int pos);
    bool isOperation(QString * str);
    QString getTopFromStack();
    QString getDelTopFromStack();
    int getOperationPriority(QString op);
    QString getStringAtPosition(int pos);
};

#endif // REVERSEPOLISHNOTATION_H
