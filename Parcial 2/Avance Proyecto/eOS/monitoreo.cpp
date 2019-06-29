#include "monitoreo.h"
#include "ui_monitoreo.h"

Monitoreo::Monitoreo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Monitoreo)
{
    ui->setupUi(this);
}

Monitoreo::~Monitoreo()
{
    delete ui;
}
