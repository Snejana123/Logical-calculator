# Logical-calculator
 The engine is able to parse boolean expressions given as input data when it is run.
 
 Creation of a graphical application for solving logical expressions using Qt 5.12, C++.
 
 1. UML diagram
 
![Діаграма без назви drawio(1)](https://user-images.githubusercontent.com/103432419/212894154-c9f1f203-fd70-483d-a205-0c55827e805a.png)

1.2. Class diagram

![class_diag](https://user-images.githubusercontent.com/103432419/212895021-8609e14a-9360-4a69-942d-759aa7cdce1a.jpg)

2. Description of the app

The application has a File menu and a Help menu, a toolbar, a field for entering an expression, a Solve button for requesting the solution of expressions, a field for displaying the solution, and a status bar. The application uses dialog boxes for importing/exporting files and for reporting technical errors (QFileDialog, QMessageBox). The following features are implemented when launching the application via the command line: getting help about the application (-h, --help), getting information about the application version, entering logical expressions for parsing via the command line, importing logical expressions from a txt file via the command line.

3. APP OPERATOR'S MANUAL

3.1. Launching an application via the command line

The application processes the following commands:
1) Get application help (-h, --help)
2) Getting information about the version of the application (-v, --version)
3) Import of logical expressions from txt file (-f, --file, --txt <file>)
4) Import into applications of logical expressions entered via the command line (--exp, --expressions <expressions>)
 
Examples of using:
 
 ![pr_1](https://user-images.githubusercontent.com/103432419/212908039-e57c3083-e88f-4b5a-9cc4-5c3ca334a9da.png)
 
 ![pr_2](https://user-images.githubusercontent.com/103432419/212908112-88db5793-4d3e-42ac-a86d-51ca816d3b89.png)
 
![pr_3](https://user-images.githubusercontent.com/103432419/212908280-dd97bdfe-c15e-470b-9f29-8b75cbf4e5e3.png)

 3.2. Working with a running application

The application has a File menu and a Help menu, a toolbar, a field for entering an expression, a Solve button for requesting the solution of expressions, a field for displaying the solution, and a status bar. The application uses dialog boxes to import/export files and to report technical errors.
To simplify the user's work, hot keys are also implemented.
 
 ![calc](https://user-images.githubusercontent.com/103432419/212914456-d03d9be4-a56c-4183-a395-0474cc37ed4c.png)
 
 ![image_2021_06_26T09_05_23_421Z](https://user-images.githubusercontent.com/103432419/214171159-38fa6641-781f-49ad-a27f-c9689b9f09ef.png)
 
 4. DESCRIPTION OF ALGORITHMS AND JUSTIFICATION OF THEIR USE

While writing the algorithm for parsing logical expressions, the algorithm for translating expressions into reverse Polish notation was used.
The algorithm was used because in it is possible to enter complex logical expressions with brackets. In reverse Polish notation, the order in which operations are performed is uniquely specified by the order in which the signs of operations appear in an expression, so it can be used to remove parentheses from expressions and introduce priorities for operations, which greatly simplifies further processing of expressions.
 
 



 
