#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculatorwidget.h"
#include <QApplication>
#include <QMainWindow>
#include <QSessionManager>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void createActions(); //Создание меню и панели инструментов
    void createStatusBar();

    calculatorWidget *calculatorW;

public:
    MainWindow();

    void loadFile(const QString fileName); //Импорт файла с именем fileName.
    void pasteString(QString str); //Добавления строки. Функция используется при вводе логических выражений через командную строку


private slots:
    void newExpression(); //Слот, очищающий виджеты перед вводом новых логических выражений
    void import(); //Импорт файла в приложение
    void exportSol(); //Экспорт решения
    //void about();

};

#endif // MAINWINDOW_H
