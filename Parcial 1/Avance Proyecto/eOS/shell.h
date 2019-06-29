#ifndef SHELL_H
#define SHELL_H

#include <QDialog>

namespace Ui {
class Shell;
}

class Shell : public QDialog
{
    Q_OBJECT

public:
    explicit Shell(QWidget *parent = 0);
    ~Shell();

private:
    Ui::Shell *ui;
};

#endif // SHELL_H
