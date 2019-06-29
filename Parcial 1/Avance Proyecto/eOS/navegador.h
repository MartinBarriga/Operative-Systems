#ifndef NAVEGADOR_H
#define NAVEGADOR_H

#include <QDialog>

namespace Ui {
class Navegador;
}

class Navegador : public QDialog
{
    Q_OBJECT

public:
    explicit Navegador(QWidget *parent = 0);
    ~Navegador();

private:
    Ui::Navegador *ui;
};

#endif // NAVEGADOR_H
