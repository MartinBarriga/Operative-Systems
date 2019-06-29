#ifndef MONITOR_H
#define MONITOR_H

#include <QDialog>

namespace Ui {
class Monitor;
}

class Monitor : public QDialog
{
    Q_OBJECT

public:
    explicit Monitor(QWidget *parent = 0);
    ~Monitor();

private slots:
    void on_inicio_linkActivated(const QString &link);

private:
    Ui::Monitor *ui;
};

#endif // MONITOR_H
