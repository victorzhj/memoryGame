/* COMP.CS.110 SPRING 2021
 * --------------------
 * Memory game.
 *
 * Description:
 * This program creates a memory game with gui that the player can interact with
 * for further details please read instructions.txt.
 * */
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
