#include "shell.h"
#include "ui_shell.h"

Shell::Shell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shell)
{
    ui->setupUi(this);
}

Shell::~Shell()
{
    delete ui;
}
