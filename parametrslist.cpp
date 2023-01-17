#include "parametrslist.h"

parametrsList::parametrsList(){
    QString parametrName = "";
    QString paramValue = "";
    parametrsList * next = 0;
}

parametrsList * parametrsList::addValueToTail(parametrsList *p, QString paramName, QString value) {
    parametrsList *head = p;
    parametrsList *next = p;
    long length = p->getListSize(p);
    if (0 != head)
        for (long i = 0; i < length; i++){
            if (next->parametrName == paramName){
                next->paramValue = value;
                return head;
            }
            next = next->next;
        }
    while (0 != next) {
        if (0 == next -> next)
            break;
        next = next -> next;
    }
    parametrsList * added;
    if (0 != next) {
        added = new parametrsList;
        added -> paramValue = value;
        added -> parametrName = paramName;
        added -> next = next -> next;
        next -> next = added;
    } else {
        added = new parametrsList;
        added -> paramValue = value;
        added -> parametrName = paramName;
        added -> next = 0;
        head = added;
    }
    return head;
}

parametrsList * parametrsList::addValueToHead(parametrsList *p, QString paramName, QString value) {
    parametrsList * head = p;
    parametrsList * next = p;
    parametrsList * added;
    long length = p->getListSize(p);
    if (0 != head) {
        for (long i = 0; i < length; i++){
            if (next->parametrName == paramName){
                next->paramValue = value;
                return head;
            }
            next = next->next;
        }
        added = new parametrsList;
        added -> paramValue = value;
        added -> parametrName = paramName;
        added -> next = head;
    } else {
        added = new parametrsList;
        added -> paramValue = value;
        added -> parametrName = paramName;
        added -> next = 0;
    }
    head = added;
    return head;
}



long parametrsList::deleteList(parametrsList *p) {
    parametrsList * head = p;
    parametrsList * next = p;
    parametrsList * tmpToDelete;
    long deletedNumber = 0;
    while(0 != next) {
        tmpToDelete = next;
        next = next -> next;
        delete tmpToDelete;
        deletedNumber ++;
        if (0 == next) {
            break;
        }
    }
    return deletedNumber;
}

long parametrsList::setParametrsListValue(parametrsList *p, QString paramName, QString value) {
    parametrsList * next = p;
    while(0 != next) {
        if (next -> parametrName == paramName) {
            next -> paramValue = value;
            return 0;
        }
        next = next -> next;
    }
    return 1;
}

QString parametrsList::getParametrsListValue(parametrsList *p, QString paramName, bool *ok) {
    parametrsList * next = p;
    while(0 != next) {
        if (next -> parametrName == paramName) {
            *ok = true;
            return next -> paramValue;
        }
        next = next -> next;
    }
    *ok = false;
    return "";
}

long parametrsList::getListSize(parametrsList *head) {
    long size = 0;
    parametrsList * next = head;
    while (0 != next) {
        size++;
        next = next -> next;
    }
    return size;
}



QString getAllValuesString(parametrsList *head) {
    QString outstr ="";
    parametrsList * next = head;
    while (0 != next) {
        outstr.append(next -> parametrName).append(" = ")
                .append(next -> paramValue).append("\n");
        next = next -> next;
    }
    return outstr;
}

