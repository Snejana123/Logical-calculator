#ifndef PARAMETRSLIST_H
#define PARAMETRSLIST_H

#include <QString>
#include <sstream>
#include <string>


class parametrsList {
    public:

    QString parametrName ="";
    QString paramValue ="";
    parametrsList * next = 0;

    parametrsList();

    /*
     *  Добавить значение в хвост списка.
     *  p - указатель головы - начало списка
     *  возвращаем указатель на голову списка
     */
    parametrsList * addValueToTail(parametrsList *p, QString paramName, QString value);


    /*
     *  Удалить список
     *  p - указатель головы - начало списка
     */
    long deleteList(parametrsList *p);


    /*
     * Добавить элемент в начало списка
     * p- указатель головы, value - новое значение
     */
    parametrsList * addValueToHead(parametrsList *p, QString paramName, QString value);


    /*
     * Присвоить хранимое значение элементу списка по имени параметра
     * p - указатель головы - начало списка
     * value - новое значение
     */
    long setParametrsListValue(parametrsList *p, QString paramName, QString value) ;

    /*
     * Взять хранимое значение элемента списка по имени параметра
     * p - указатель головы - начало списка
     */
    QString getParametrsListValue(parametrsList *p, QString paramName, bool *ok);

    /*
     * Взять (посчитать) количество записей в списке
     */
    long getListSize(parametrsList *head);


    /*
     *получить строку значений списка с пробелами, "\n" и " = "
     */
    QString getAllValuesString(parametrsList *head);
};







#endif // PARAMETRSLIST_H
