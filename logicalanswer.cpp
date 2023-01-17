#include "logicalanswer.h"

logicalAnswer::logicalAnswer()
{

}

void logicalAnswer::setRevPolishNot(QString *pol){
    stack = "";
    answer = false;
    error = "";
    polish = *pol;
    answer = false;
}

bool logicalAnswer::getAnswer(){
    return answer;
}


QString logicalAnswer::getStringAnswer(){
    if (answer == true)
        return "TRUE";
    return "FALSE";
}

QString logicalAnswer::getError(){
    return error;
}


bool logicalAnswer::calculateAnswer(){
    int i = 0, leng = polish.length();
    QString currEl = "", firstOperand = "", secondOperand = "";
    float first, second;
    bool isFloat_1, isFloat_2, result;
    bool wasOperation = false;
    int isOperand = 0;
    while(i < leng){
        if (isDelimeter(polish[i])){
            i++;
            continue;
        }

        if (polish[i] == "["){
            error = "LOGICAL ERROR. Not all parametrs are defined";
            return false;
        }

        currEl = getElAtPosition(i);
        i += currEl.length();

        if (! isOperation(&currEl))
        {
            if (isOperand == 2){
                error = "LOGICAL ERROR. The expression has operands on which no operations are performed";
                return false;
            }
            stack.append(currEl).append(" ");
            isOperand++;
        }else{
            wasOperation = true;
            isOperand = 0;
            secondOperand = getDelTopFromStack();
            firstOperand = getDelTopFromStack();

            if ((firstOperand == "") || (secondOperand == "")){
                error = "LOGICAL ERROR. All operations are binary. Check the position and number of operands. ";
                return false;
            }


            if ((isBooleanConst(firstOperand)) && (isBooleanConst(secondOperand))){
                result = boolOperation(stringToBool(firstOperand), stringToBool(secondOperand), currEl);
                if (error != "")
                    return false;;
                if(result){
                    stack.append("TRUE").append(" ");
                }else{
                    stack.append("FALSE").append(" ");
                }
                continue;
            }
            if (((! isBooleanConst(firstOperand)) && (isBooleanConst(secondOperand)))
                    || ((isBooleanConst(firstOperand)) && (! isBooleanConst(secondOperand)))){
                error = QString("LOGICAL ERROR No operation can be applied to operands (%1,  %2)").arg(firstOperand, secondOperand);
                return false;
            }


            first = firstOperand.toFloat(&isFloat_1);
            second = secondOperand.toFloat(&isFloat_2);
            if ((isFloat_1) && (isFloat_2)){
                   result = compareFloat(first, second, currEl);
                   if(error != ""){
                       return false;;
                   }
                   if(result){
                       stack.append("TRUE").append(" ");
                   }else{
                       stack.append("FALSE").append(" ");
                   }
                   continue;
            }


            if ((! isFloat_1) && (! isFloat_2)){
                result = compareString(firstOperand, secondOperand, currEl);
                if(error != ""){
                    return false;;
                }
                if(result){
                    stack.append("TRUE").append(" ");
                }else{
                    stack.append("FALSE").append(" ");
                }
                continue;
            }

            if (((! isFloat_1) && (isFloat_2)) || (( isFloat_1) && (!isFloat_2))){
                error = QString("LOGICAL ERROR No operation can be applied to operands (%1,  %2)").arg(firstOperand, secondOperand);
                return false;
            }

        }
    }
    if  ((! wasOperation) && (error == "")){
        error = "No operations";
        return false;
    }
    stack.remove(" ");
    if (error != ""){
        answer = false;
        return false;
    }else{
        if (stack == "TRUE")
            answer = true;
        if (stack == "FALSE")
            answer = false;
        return true;
    }
}

bool logicalAnswer::isDelimeter(QChar symb){
    if ((symb == " ") || (symb == "\n") || (symb == "\t") || (symb == "\r"))
        return true;
    return false;
}

bool logicalAnswer::isOperation(QString * str){
    if ((str->compare("<") == 0)
            || (str->compare(">") == 0)
            || (str->compare("<=") == 0)
            || (str->compare(">=") == 0)
            || (str->compare("==") == 0)
            || (str->compare("!=") == 0)
            || (str->compare("OR", Qt::CaseInsensitive) == 0)
            || (str->compare("AND", Qt::CaseInsensitive) == 0)){
        return true;
    }
    return false;
}

QString logicalAnswer::getElAtPosition(int pos){
    int max = polish.length();
    QString el = "";
    int quoteCount = 0;
    for (int i = pos; i < max; i++){
        if (isDelimeter(polish.at(i)) && (quoteCount != 1)){
            return el;
        }else{
            if (polish[i] == "\"")
                quoteCount++;
            el.append(polish[i]);
        }
    }
    return el;
}

QString logicalAnswer::getDelTopFromStack(){
    int leng = stack.length(), pos = leng - 1;
    int quoteCount = 0;
    if (leng == 0)
        return "";
    QString top = "";
    for (int i = leng - 2; i >= 0; i--){
        if (isDelimeter(stack[i]) && (quoteCount != 1)){
            break;
        }
        if (stack[i] == "\"")
            ++quoteCount;
        --pos;
    }
    top = stack.mid(pos, leng - 1 - pos);
    stack.remove(pos, leng - pos);
    return top;
}

bool logicalAnswer::compareString(QString first, QString second, QString op){
    if (op == ">")
        return first > second;
    if (op == "<")
        return first < second;
    if (op == ">=")
        return first >= second;
    if (op == "<=")
        return first <= second;
    if (op == "==")
        return first == second;
    if (op == "!=")
        return first != second;
    error = QString("LOGICAL ERROR Operation %1 on operands %2 %3 cannot be applied")
            .arg(op, first, second);
    return false;
}

bool logicalAnswer::compareFloat(float first, float second, QString op){
    if (op == ">")
        return first > second;
    if (op == "<")
        return first < second;
    if (op == ">=")
        return first >= second;
    if (op == "<=")
        return first <= second;
    if (op == "==")
        return first == second;
    if (op == "!=")
        return first != second;
    QString firstOp, secondOp;
    error = QString("LOGICAL ERROR Operation %1 on operands %2 %3 cannot be applied")
            .arg(op, firstOp.setNum(first), secondOp.setNum(second));
    return false;
}

bool logicalAnswer::boolOperation(bool first, bool second, QString op){
    if (op == "OR")
        return first || second;
    if (op == "AND")
        return first && second;
    error = QString("LOGICAL ERROR Operation %1 cannot be applied to a boolean data type ").arg(op);
    return false;
}


bool logicalAnswer::isBooleanConst(QString operand){
    if ((operand.toUpper() == "TRUE") || (operand.toUpper() == "FALSE"))
        return true;
    return false;
}

bool logicalAnswer::stringToBool(QString operand){
    if (operand.toUpper() == "TRUE")
        return true;
    return false;
}

/*QString logicalAnswer::boolToString(bool operand){
    if (operand == true)
        return "TRUE";
    return ;
}*/
