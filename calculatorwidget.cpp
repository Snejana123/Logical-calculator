#include "calculatorwidget.h"
#include <QFileDialog>
#include <QTextStream>
#include <QSaveFile>
#include <QMessageBox>
#include <QRegExp>

//#include <QFileInfo>

#include "parametrslist.h"

calculatorWidget::calculatorWidget(QWidget *parent)
    :QWidget(parent)
{
    /*
     * Класс QPlainTextEdit предоставляет виджет, который используется для редактирования и отображения простого текста.
     * textEdit - виджет для ввода входных данных пользователем
     * displaySolution - виджет для отображения решения
    */
    textEdit = new QPlainTextEdit;
    textEdit->setDocumentTitle(QString("Logical expressions"));

    displaySolution = new QPlainTextEdit;
    //Убираем возможность редактирования, чтобы пользователь случайно не изменил решение
    displaySolution->setReadOnly(true);
    displaySolution->setDocumentTitle(QString("Solution"));

    //Кнопка, после нажатия которой, логический интерпретатор должен посчитать и отобразить решение
    solveButton = new QPushButton("Solve", this);
    solveButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    //Класс QVBoxLayout выстраивает виджеты вертикально.
    calcLayout = new QVBoxLayout;

    calcLayout->addWidget(textEdit);
    calcLayout->addWidget(solveButton);
    calcLayout->addWidget(displaySolution);

    setLayout(calcLayout);

    connect(solveButton, SIGNAL(clicked()), this, SLOT(getSolution()));

    polish = new reversePolishNotation;

}

calculatorWidget::~calculatorWidget(){
    delete textEdit;
    delete displaySolution;
    delete calcLayout;
}


/*
 * Слот, который вызывается в ответ на сигнал о нажатии кнопки solveButton
 */
void calculatorWidget::getSolution(){
   QString text = textEdit->toPlainText();
   QTextStream str(&text, QIODevice::ReadOnly);
   QString line, currParamName ="", currParamVal = "", myOutStr = "", currExpr ="";
   QString answer, error, polishNot;
   QRegExp reg ("[^>^<^!^=.]*=[^=]*");
   parametrsList * pList = 0;
   bool paramError = false, wasExpr = false;
   while(!str.atEnd()){
     line = str.readLine();
     if ((line.isEmpty()) || (QRegExp("[ \t\n\r]*").exactMatch(line)))
         continue;
     if ( reg.exactMatch(line)){
         if (wasExpr){
             if (paramError){
                     paramError = false;
             }else{
                 polish->setExpression(currExpr);
                 currExpr.clear();
                 if(! polish->calculatePolishNot()){
                     error = polish->getError();
                     myOutStr.append(error).append("\n");
                 }else{
                     polish->setParametrList(pList);
                     polish->replaceParametrsWithValues();
                     if (! polish->getError().isEmpty()){
                         error = polish->getError();
                         myOutStr.append(error).append("\n");
                     }else{
                         polishNot = polish->getPolishNot();
                         logAns.setRevPolishNot(& polishNot);
                         if(logAns.calculateAnswer()){
                             answer = logAns.getStringAnswer();
                             myOutStr.append(answer).append("\n");
                         }else{
                             error = logAns.getError();
                             myOutStr.append(error).append("\n");
                     }
                     }

                 }
             }
             wasExpr = false;
             myOutStr.append("\n");
         }
         currParamName.clear();
         currParamVal.clear();
         polishNot.clear();

         myOutStr.append(line).append("\n");


         if (paramError == true)
             continue;

         int i = 0;
         bool parametrNotRead = true;
         while (line[i] != "="){
             if (parametrNotRead && ((line[i] == " ") || (line[i] == "\n")
                     || (line[i] == "\t") || (line[i] == "\r"))){
                 ++i;
                 continue;
             }
             parametrNotRead = false;
             currParamName.append(line.at(i));
             ++i;
         }
         ++i;

         int k = currParamName.length() - 1;
         while(k >= 0){
             if ((currParamName[k] == " ") || (currParamName[k] == "\n")
                     || (currParamName[k] == "\t") || (currParamName[k] == "\r")){
                 currParamName.remove(k,1);
                 k--;
                 continue;
             }
             break;
         }

         if (currParamName.isEmpty()){
            myOutStr.append("ERROR No parametr name \n");
            paramError = true;
            continue;
         }
         bool valNotRead = true;
         while (i < line.length()){
             if (valNotRead && ((line[i] == " ") || (line[i] == "\n")
                     || (line[i] == "\t") || (line[i] == "\r"))){
                 ++i;
                 continue;
             }
             valNotRead = false;
             currParamVal.append(line[i]);
             ++i;
         }
         k = currParamVal.length() - 1;
         while(k >= 0){
             if ((currParamVal[k] == " ") || (currParamVal[k] == "\n")
                     || (currParamVal[k] == "\t") || (currParamVal[k] == "\r")){
                 currParamVal.remove(k,1);
                 k--;
                 continue;
             }
             break;
         }
         if (currParamVal.isEmpty()){
            myOutStr.append("ERROR No parametr value \n");
            paramError = true;
            continue;

         }

         pList = pList->addValueToHead(pList, currParamName, currParamVal);


     }else{
        wasExpr = true;
        myOutStr.append(line).append("\n");
        if(paramError){
            continue;
        }
        currExpr.append(line);
        if (str.atEnd()){
            polish->setExpression(currExpr);
            currExpr.clear();
            if(! polish->calculatePolishNot()){
                error = polish->getError();
                myOutStr.append(error);
            }else{
                polish->setParametrList(pList);
                polish->replaceParametrsWithValues();
                if (! polish->getError().isEmpty()){
                    error = polish->getError();
                    myOutStr.append(error).append("\n");
                }else{
                    polishNot = polish->getPolishNot();
                    logAns.setRevPolishNot(& polishNot);
                    if(logAns.calculateAnswer()){
                        answer = logAns.getStringAnswer();
                        myOutStr.append(answer).append("\n");
                    }else{
                        error = logAns.getError();
                        myOutStr.append(error).append("\n");
                    }
                }
            }
            break;
        }
     }
   }

   displaySolution->setPlainText(myOutStr);
   pList->deleteList(pList);


}

/*polish->setExpression(text);
QString answer = polish->getPolishNot();
QString error = polish->getError();
if (error == ""){
     logAns.setRevPolishNot(&answer);
     answer = logAns.getStringAnswer();
     error = logAns.getError();
}
if (error != ""){
    displaySolution->setPlainText(error);
}else{
    displaySolution->setPlainText(answer);
}*/
//displaySolution->setPlainText(text);
//displaySolution->setPlainText(logicalErrorMessage);

//очистка виджетов перед вводом новых логических выражений
void calculatorWidget::clearCalc(){
    displaySolution->clear();
    textEdit->clear();
}


//Импорт текстового файла с именем fileName
bool calculatorWidget::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        //Если приложение не может прочитать файл, информирование пользователя об ошибке через диалоговое окно
        QMessageBox::warning(this, tr("Logical Calculator"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }
    //Импорт файла
    QTextStream in(&file);
    textEdit->insertPlainText(in.readAll());
    return true;
}

/*
 * Слот для получения имени файла через диалоговое окно QFileDialog
 * Если пользователь выбрал файл для импортирования, имя файла передается в loadFile() для его загрузки в приложение
 * Добавлен фильтр для рассширений файлов (только txt)
 */
bool calculatorWidget::import(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("*.txt"));
    if (!fileName.isEmpty())
    {
    QTextStream in(&fileName);
    return loadFile(fileName);
    }
    return false;
}


/*
 * Тоже функция для импорта файла как и import.
 * Отличие в том, что функции передается предпологаемое имя текстового файла,
 * затем сразу идет проверка, что это действительно имя файла, затем проверка, что файл txt.
 * Функция используется для импорта при запуске приложения через командную строку
 */
bool calculatorWidget::importFile(QString fileName){
    if (!fileName.isEmpty())
    {
        QFileInfo fi(fileName);
        if(! fi.isFile()){
            QMessageBox::warning(this, tr("Logical Calculator"), "File not found. Please check the filename.");
            return false;
        }
        if (fi.completeSuffix() != "txt"){
            QMessageBox::warning(this, tr("Logical Calculator"), "Cannot open this file type. Please import txt file.");
            return false;
        }
        loadFile(fileName);
        //textEdit->insertPlainText(in.readAll());
    }
    return true;
}


/*
 * Получение имени файла для экспорта решения через диалоговое окно.
 * При успешном получении иемени файла, оно дальше передается в функцию saveAs, отвечающую за экспорт.
 * Если никакого решения пока нет, появляется диалоговое окно с оповещением, что экспортировать нечего.
 * Добавлен фильтр на допустимое расширений файла (txt)
 */
bool calculatorWidget::exportSolution(){
    if (maybeExport()){
        if (maybeExport()){
            QFileDialog dialog(this);
            dialog.setAcceptMode(QFileDialog::AcceptSave);
            dialog.setFileMode(QFileDialog::AnyFile);
            dialog.setNameFilter("*.txt");
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save file as"), QDir::currentPath(), tr("*.txt"));
            return saveAs(fileName);
        }
    }
    QMessageBox::warning(this, tr("Logical Calculator"), "Nothing to export");
    return false;
}


/*
 * Экспорт решения в txt файл с именем fileName.
 * В случаях ошибок при попытке записать данные появиться диалоговое окно с errorMessage.
 */
bool calculatorWidget::saveAs(const QString &fileName){
    if (fileName.isEmpty())
        return false;
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out <<displaySolution->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Logical Calculator"), errorMessage);
        errorMessage.clear();
        return false;
    }

    return true;
}



void calculatorWidget::setString(QString &insString){
    textEdit->setPlainText(insString);
}

void calculatorWidget::insertString(QString &insString){
    textEdit->insertPlainText(insString);
}


/*
 * Проверка, есть ли решение, которое можно экспортироовать.
 */
bool calculatorWidget::maybeExport(){
    if (displaySolution->document()->isEmpty())
        return false;
    return true;
}


/*
 * Возвращает строку с информацией об ошибке. В работе эта функция пока не использовалась
 */
QString calculatorWidget::getErrorMessage(){
    return errorMessage;
}
