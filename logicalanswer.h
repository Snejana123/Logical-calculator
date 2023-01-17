#ifndef LOGICALANSWER_H
#define LOGICALANSWER_H

#include <QString>

class logicalAnswer
{
public:
    logicalAnswer();
    void setRevPolishNot(QString *pol);
    bool calculateAnswer();
    bool getAnswer();
    QString getStringAnswer();
    QString getError();

private:
    QString polish = "";
    QString stack = "";
    bool answer = false;
    QString error = "";
    bool isDelimeter(QChar symb);
    bool isOperation(QString * str);
    QString getElAtPosition(int pos);
    QString getDelTopFromStack();
    bool compareString(QString first, QString second, QString op);
    bool compareFloat(float first, float second, QString op);
    bool boolOperation(bool first, bool second, QString op);
    bool isBooleanConst(QString operand);
    bool stringToBool(QString operand);
};

#endif // LOGICALANSWER_H
