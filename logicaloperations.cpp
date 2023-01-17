//НАЧАЛО

#include "logicaloperations.h"
#include <cxxabi.h>

/*enum Operations{
    NO_OP,
    EQUAL_TO,
    NOT_EQUAL_TO,
    GREATER_THAN,
    LESS_THAN,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL,
    OR_OP,
    AND_OP
};*/


template <typename T> int applyOperation(int operation, T operand_1, T operand_2 ){
    return 0;
}

template <typename T> int isEqualTo(int operation, T operand_1, T operand_2 ){
    int status;
    if (( typeid(operand_1).name() ==  typeid(double).name()) && ( typeid(operand_2).name() == typeid(double).name())){
        if (operand_1 == operand_2) {
            return 1;
        }else{
            return 0;
        }
    }
    if (( typeid(operand_1).name() ==  typeid(QString).name()) && ( typeid(operand_2).name() ==  typeid(QString).name())){
        if (compare(operand_1,operand_2) == 0) {
            return 1;
        }else{
            return 0;
        }
    }
    logicalErrorMessage = "Logical error. It is impossible to compare %1 and %2";
    logicalErrorMessage.arg(abi::__cxa_demangle(typeid(operand_1).name(), 0, 0, &status)).arg(abi::__cxa_demangle(typeid(operand_2).name(), 0, 0, &status));
    return 2;
}
