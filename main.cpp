#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);
/*#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif*/

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Educational practice");
    QCoreApplication::setApplicationName("Logical calculator");
    QCoreApplication::setApplicationVersion("0.1");

    //Класс QCommandLineParser предоставляет средства для обработки параметров командной строки.
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();

    /*
     * Опция для импорта файла в приложение. Пользователь должен ввести в командную строку
     * любое из имен опции (например --txt ли -f) и имя файла (или полный путь к файлу)
     */
    QCommandLineOption importfile_option(QStringList() << "f" << "file" << "txt", "Import expressions from the file", "file");
    parser.addOption(importfile_option);

    /*
     * Опция импорта выражений через командную строку. Вводить выражения надо с учетом особенностей командной строки.
     * Например в Linux может быть следующая команда:
     * ./Calculator --exp "param = \"abc\" [param] <= \"abd\" or [param] >= \"asd\" "
     */
    QCommandLineOption solveexpressions_option(QStringList() << "exp" << "expressions", "Import expressions entered as arguments", "expressions");
    parser.addOption(solveexpressions_option);


    parser.process(app);

    //Проверяем, вводил ли пользователь названия опций
    bool isImoportFile = parser.isSet(importfile_option);
    bool isExpression = parser.isSet(solveexpressions_option);

    MainWindow mainWin;
   if (isImoportFile){
        mainWin.loadFile(parser.value("file"));
   }
   if(isExpression){
       //Перед вставкой выражений убираем (если есть) запятые в строке с выражениями
        mainWin.pasteString(parser.value("expressions").replace("," , "\n"));
   }
    mainWin.show();
    return app.exec();
}
