#include "sokoban.h"
#include "ui_sokoban.h"

Sokoban::Sokoban(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sokoban)
{
    ui->setupUi(this);
}

Sokoban::~Sokoban()
{
    delete ui;
}
