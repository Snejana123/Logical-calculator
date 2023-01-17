#ifndef LOGICALOPERATIONS_H
#define LOGICALOPERATIONS_H

#include <typeinfo>
#include <QString>

enum Operations{
    NO_OP,
    EQUAL_TO,
    NOT_EQUAL_TO,
    GREATER_THAN,
    LESS_THAN,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL,
    OR_OP,
    AND_OP
};

QString logicalErrorMessage;
template <typename T> int applyOperation(int operation, T operand_1, T operand_2 );
template <typename T> int isEqualTo(int operation, T operand_1, T operand_2 );


#endif // LOGICALOPERATIONS_H
