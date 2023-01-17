


//Класс для перевода выражения в обратную польскую нотацию

#include "reversepolishnotation.h"
#include "parametrslist.h"

reversePolishNotation::reversePolishNotation()
{
    //Строка для записи выражения в обратной польской нотации
    reversePolish ="";
    errorMessage = "";
    stack = "";
    //указатель на строку QString с выражением
    expr = "";
    parametrsList * list = 0;
}

reversePolishNotation::~reversePolishNotation(){

}

/*
 * Через указатель устанавливается логическое выражение для перевода в обратную польлскую нотацию
 */
void reversePolishNotation::setExpression(QString expression){
    expr = expression;
    reversePolish ="";
    errorMessage = "";
    stack = "";
}


QString reversePolishNotation::getPolishNot(){
    return reversePolish;
}

QString reversePolishNotation::getError(){
    return errorMessage;
}

/*
 * Перевод выражения в польскую нотацию.
 */
bool reversePolishNotation::calculatePolishNot(){
    reversePolish ="";
    errorMessage = "";
    stack = "";
    QString currSym = "";
    QString op = "";
    bool ok;
    int i = 0, leng = expr.length();
    while(i < leng){

        if (isDelimeter(expr.at(i))){
            i++;
            continue;
        }

        if (expr[i] == "\""){
            reversePolish.append("\"");
            i++;
            while (expr[i] != "\""){
                if(i >= leng){
                    errorMessage = "ERROR No closing quote";
                    reversePolish = "";
                    return false;
                }
                reversePolish.append(expr[i]) ;
                i++;
            }
            reversePolish.append(expr[i]).append(" ");
            i++;
            continue;
        }

        if (expr[i] == "["){
            reversePolish.append("[");
            i++;
            while (expr[i] != "]"){
                if(i >= leng){
                    errorMessage = "ERROR No closing square parenthesis";
                    reversePolish = "";
                    return false;
                }
                reversePolish.append(expr[i]) ;
                i++;
            }
            reversePolish.append(expr[i]).append(" ");
            i++;
            continue;
        }


        if ((expr[i] >= "0") && (expr[i] <= "9")){
            currSym ="";
            while (((expr[i] >= "0") && (expr[i] <= "9")) || (expr[i] == ".")){
                if(i >= leng){
                    break;
                }
                currSym.append(expr[i]);
                i++;
            }
            currSym.toFloat(&ok);
            if (ok){
                reversePolish.append(currSym).append(" ");
                currSym ="";
                continue;
            }else{
                errorMessage = "ERROR Impossible to determine number ";
                errorMessage.append(currSym);
                reversePolish = "";
                return false;
            }
            continue;

        }

        if (expr[i] == "("){
            stack.append("(");
            i++;
            continue;
        }

        if (expr[i] == ")"){
            QString operation = getDelTopFromStack();
            if (! stack.contains("(")){
                errorMessage = "ERROR No opening parenthesis";
                reversePolish = "";
                return false;
            }
            while (operation != "("){
                reversePolish.append(operation).append(" ");
                operation = getDelTopFromStack();
            }
            i++;
            continue;
        }

        currSym = getStringAtPosition(i);
        if ((currSym.toUpper() == "TRUE") || (currSym.toUpper() == "FALSE")){
            reversePolish.append(currSym.toUpper()).append(" ");
            i += currSym.length();
            continue;
        }
        currSym = getOpAtPosition(i);
        if ((currSym =="") && (errorMessage != "")){
            reversePolish = "";
            return false;
        }
        if (currSym == ""){
            i++;
            continue;
        }
        if(isOperation(&currSym)){
            currSym = currSym.toUpper();
            while (getOperationPriority(getTopFromStack()) >= getOperationPriority(currSym))
                reversePolish.append(getDelTopFromStack()).append(" ");
            stack.append(currSym.toUpper());
            i += currSym.length();
        }else{
            errorMessage = "ERROR Impossible to determine symbols ";
            errorMessage.append(currSym);
            reversePolish = "";
            return false;
        }

    }

    if ( stack.contains("(")){
        errorMessage = "ERROR No closing parenthesis";
        reversePolish = "";
        return false;
    }
    while (stack != ""){
        op = getDelTopFromStack();
        reversePolish.append(op).append(" ");
    }
    return true;
}

QString reversePolishNotation::getStringAtPosition(int pos){
    int max = expr.length();
    QString str = "";
    for (int i = pos; i < max; i++){
        if (isDelimeter(expr.at(i)) || (expr[i] == ">")
                || (expr[i] == "<") || (expr[i] == ")")
                || (expr[i] == "(") || (expr.mid(i, 2) == ">=")
                || (expr.mid(i, 2) == "<=") || (expr.mid(i, 2) == "==")
                || (expr.mid(i, 2) == "!=") || (expr.mid(i, 2).toUpper() == "OR")
                || (expr.mid(i, 3).toUpper() == "AND")){
            return str;
        }else{
            str.append(expr[i]);
        }
    }
    return str;
}


QString reversePolishNotation::getOpAtPosition(int pos){
    int max = expr.length();
    QString op = "";
    for (int i = pos; i < max; i++){
        if ((isDelimeter(expr.at(i))) || (expr[i] == "\"") || (expr[i] == "[")
                || ((expr[i] <= "9") && (expr[i] >= "0"))
                || (expr.mid(i, 4).toUpper() == "TRUE") || (expr.mid(i, 5).toUpper() == "FALSE")){
            return op;
        }else{
            op.append(expr[i]);
            /*errorMessage = "Error. Impossible to determine symbol ";
            errorMessage.append(expression[i]);
            reversePolish = "";
            return "";*/
        }
    }
    return op;
}

QString reversePolishNotation::getDelTopFromStack(){
   QString sym =  stack.right(1);
   if  (sym == ">"){
       stack.remove(stack.length() - 1, 1);
       return ">";
   }
   if  (sym == "<"){
       stack.remove(stack.length() - 1, 1);
       return "<";
   }
   if  (sym == "("){
       stack.remove(stack.length() - 1, 1);
       return "(";
   }
   sym = stack.right(2);
   if  (sym == ">="){
       stack.remove(stack.length() - 2, 2);
       return ">=";
   }
   if  (sym == "<="){
       stack.remove(stack.length() - 2, 2);
       return "<=";
   }
   if  (sym == "=="){
       stack.remove(stack.length() - 2, 2);
       return "==";
   }
   if  (sym == "!="){
       stack.remove(stack.length() - 2, 2);
       return "!=";
   }
   if (sym.compare("OR", Qt::CaseInsensitive) == 0){
       stack.remove(stack.length() - 2, 2);
       return "OR";
   }
   if (stack.right(3).compare("AND", Qt::CaseInsensitive) == 0){
       stack.remove(stack.length() - 3, 3);
       return "AND";
   }
   if (stack == ""){
       return "";
   }else{
       errorMessage = "ERROR Unrecognised symbol";
       return "";
   }
}

QString reversePolishNotation::getTopFromStack(){
    QString sym =  stack.right(1);
    if  (sym == ">"){
        return ">";
    }
    if  (sym == "<"){
        return "<";
    }
    if  (sym == "("){
        return "(";
    }
    sym = stack.right(2);
    if  (sym == ">="){
        return ">=";
    }
    if  (sym == "<="){
        return "<=";
    }
    if  (sym == "=="){
        return "==";
    }
    if  (sym == "!="){
        return "!=";
    }
    if (sym.compare("OR", Qt::CaseInsensitive) == 0){
        return "OR";
    }
    if (stack.right(3).compare("AND", Qt::CaseInsensitive) == 0){
        return "AND";
    }
    if (stack == ""){
        return "";
    }else{
        errorMessage = "ERROR Unrecognised symbol";
        return "";
    }
}

bool reversePolishNotation::isDelimeter(QChar symb){
    if ((symb == " ") || (symb == "\n") || (symb == "\t") || (symb == "\r"))
        return true;
    return false;
}

bool reversePolishNotation::isOperation(QString * str){
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


int reversePolishNotation::getOperationPriority(QString op){
    if ((op == "<") || (op == ">") || (op == "<=") || (op == ">=") || (op == "!=") || (op == "=="))
        return 2;
    if ((op == "OR") || (op == "AND") )
        return 1;
    return 0;
}

void reversePolishNotation::replaceParametrsWithValues(){
    parametrsList * next = list;
    QString param;
    for (long i = 0; i < list->getListSize(list); i++){
        param = next->parametrName;
        param.prepend("[").append("]");
        reversePolish.replace(param, next->paramValue);
        next = next->next;
    }
}

void reversePolishNotation::setParametrList (parametrsList * currList){
    list = currList;
}
