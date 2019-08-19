#include "mainwindow.h"
#include <QApplication>
/**
 * @brief main It is the main function of the program from where the execution will begin
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Reckless Chasing(Home)");
    w.show();

    return a.exec();
}
