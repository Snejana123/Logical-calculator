#include "calculatorwidget.h"
#include <QtWidgets>

#include "mainwindow.h"



MainWindow::MainWindow()
{
    calculatorW = new calculatorWidget;

    const QIcon calculator = QIcon::fromTheme("Calculator", QIcon(":/images/calculatorIcon.png"));

    setWindowIcon(calculator);

    setWindowTitle("Logical Calculator");
    setCentralWidget(calculatorW);

    createActions();
    createStatusBar();

    setUnifiedTitleAndToolBarOnMac(true);
}

/*
 * Создание меню и панели инструментов
 */
void MainWindow::createActions()
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("&New expression", QIcon(":/images/newExpression.png"));
    QAction *newAct = new QAction(newIcon, tr("&New expression"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("New expression"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newExpression);

    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));

    QIcon importIcon = QIcon::fromTheme("Import", QIcon(":/images/import.png"));
    QAction *importAct = new QAction(importIcon, tr("&Import"), this);
    importAct->setShortcut(tr("CTRL+I"));
    importAct->setStatusTip(tr("File import"));
    connect(importAct, &QAction::triggered, this, &MainWindow::import);

    fileMenu->addAction(importAct);
    fileToolBar->addAction(importAct);

    QIcon exportIcon = QIcon::fromTheme("Export", QIcon(":/images/export.png"));
    QAction *exportAct = new QAction(exportIcon, tr("&Export"), this);
    exportAct->setShortcut(tr("CTRL+E"));
    exportAct->setStatusTip(tr("File export"));
    connect(exportAct, &QAction::triggered, this, &MainWindow::exportSol);

    fileMenu->addAction(exportAct);
    fileToolBar->addAction(exportAct);

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


/*
 * Слот, очищающий виджеты перед вводом новых логических выражений
 */
void MainWindow::newExpression()
{
    calculatorW->clearCalc();
}


/*void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("<b>Calculator</b> provides the ability to solve "
               "logical expressions."
               "It is a modern GUI application using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}*/

/*
 * Импорт файла в приложение
 */
void MainWindow::import()
{
    calculatorW->import();
    statusBar()->showMessage(tr("File loaded"), 2000);
}

/*
 * Экспорт решения
 */
void MainWindow::exportSol(){
    calculatorW->exportSolution();
    statusBar()->showMessage(tr("File exported"), 2000);
}

/*
 * Импорт файла с именем fileName.
 * Функция используется при импорте файла через командную строку
 */
void MainWindow::loadFile(const QString fileName){
    calculatorW->importFile(fileName);
}


/*
 * Добавления строки.
 * Функция используется при вводе логических выражений через командную строку
 */
void MainWindow::pasteString(QString str){
    calculatorW->insertString(str);
}
