#include "sokoban.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sokoban w;
    w.show();

    return a.exec();
}
