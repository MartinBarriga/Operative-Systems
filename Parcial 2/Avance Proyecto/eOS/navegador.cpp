#include "navegador.h"
#include "ui_navegador.h"

Navegador::Navegador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Navegador)
{
    ui->setupUi(this);
}

Navegador::~Navegador()
{
    delete ui;
}
