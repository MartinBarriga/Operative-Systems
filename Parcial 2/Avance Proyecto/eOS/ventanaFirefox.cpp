#include "ventanaFirefox.h"
#include "ui_ventana.h"

ventana::ventana(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventana)
{
    ui->setupUi(this);
}

ventana::~ventana()
{
    delete ui;
}
