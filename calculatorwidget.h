#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include "reversepolishnotation.h"
#include "logicalanswer.h"


class calculatorWidget : public QWidget
{
    Q_OBJECT

private:
    //void claculate();
    bool maybeExport(); //Проверка, есть ли решение, которое можно экспортироовать.
    bool loadFile(const QString &fileName); //Импорт текстового файла с именем fileName
    bool saveAs(const QString &fileName); //Экспорт решения в txt файл с именем fileName.
    QPlainTextEdit *displaySolution;
    QPlainTextEdit *textEdit;
    QPushButton *solveButton;
    QString curString;
    QVBoxLayout *calcLayout;
    QString errorMessage;

    reversePolishNotation * polish;
    logicalAnswer logAns;



public:
    calculatorWidget(QWidget *parent = 0);
    ~calculatorWidget();
    void setString(QString &insString); //Вставка строки в textEdit с удалением предыдущего текста
    void insertString(QString &insString); //Вставка строки в textEdit
    bool importFile(QString fileName); //Импорт файла с именем fileName
    QString getErrorMessage(); //Получение строки с информацией об ошибке
    //struct parametrsList * paramListHead;


public slots:
    void getSolution(); //Слот, который вызывается в ответ на сигнал о нажатии кнопки solveButton
    void clearCalc();  //Очистка виджетов перед вводом новых логических выражений
    bool import();  //Слот для получения имени файла через диалоговое окно QFileDialog
    bool exportSolution(); //Получение имени файла для экспорта решения через диалоговое окно.

};

#endif // CALCULATORWIDGET_H
