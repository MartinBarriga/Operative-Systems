#ifndef VENTANA_H
#define VENTANA_H

#include <QDialog>

namespace Ui {
class ventana;
}

class ventana : public QDialog
{
    Q_OBJECT

public:
    explicit ventana(QWidget *parent = 0);
    ~ventana();

private:
    Ui::ventana *ui;
};

#endif // VENTANA_H
