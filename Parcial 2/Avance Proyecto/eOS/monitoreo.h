#ifndef MONITOREO_H
#define MONITOREO_H

#include <QDialog>

namespace Ui {
class Monitoreo;
}

class Monitoreo : public QDialog
{
    Q_OBJECT

public:
    explicit Monitoreo(QWidget *parent = 0);
    ~Monitoreo();

private:
    Ui::Monitoreo *ui;
};

#endif // MONITOREO_H
