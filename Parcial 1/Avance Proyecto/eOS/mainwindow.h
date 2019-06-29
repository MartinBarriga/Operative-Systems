#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navegador.h"
#include "shell.h"
#include "monitor.h"
#include "monitoreo.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showTime();
    void set_style();

    void on_BotonFirefox_clicked();

    void on_BotonShell_clicked();

    void on_BotonMonitor_clicked();

    void on_BotonProcesoMemoria_clicked();

private:
    Ui::MainWindow *ui;
    Navegador *navegador;
    Shell *shell;
    Monitor *monitor;
    Monitoreo *monitoreo;
};

#endif // MAINWINDOW_H
