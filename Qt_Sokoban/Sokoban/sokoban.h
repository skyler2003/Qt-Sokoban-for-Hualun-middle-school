#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <QMainWindow>

namespace Ui {
class Sokoban;
}

class Sokoban : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sokoban(QWidget *parent = 0);
    ~Sokoban();

private:
    Ui::Sokoban *ui;
};

#endif // SOKOBAN_H
