#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /*
    setStyleSheet("background-color: #000000;");
    ui->aplicaciones->setStyleSheet("color: #D5D5D3;");
    ui->hora_fecha->setStyleSheet("color: #D5D5D3;");
    ui->notificaciones->setStyleSheet("color: #D5D5D3;");*/

    set_style();

    /*Reloj y Fecha*/
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();

}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");
    QDateTime datetime = QDateTime::currentDateTime();
    QString datetime_text = datetime.toString("dd MMMM yyyy");
    ui->hora_fecha->setText(datetime_text + "     " + time_text);
}

void MainWindow::set_style()
{

    QFile styleSheet(":/styles.qss");

    if (!styleSheet.open(QIODevice::ReadOnly)) {
        qWarning("Unable to open :/styles.qss");
        return;
    }

    qApp->setStyleSheet(styleSheet.readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BotonFirefox_clicked()
{
    //Navegador firefox;
    //firefox.setModal(true);
    //firefox.exec();
    navegador = new Navegador(this);
    navegador ->show();
}

void MainWindow::on_BotonShell_clicked()
{
    shell = new Shell(this);
    shell ->show();
}

void MainWindow::on_BotonMonitor_clicked()
{
    monitor = new Monitor(this);
    monitor ->show();
}

void MainWindow::on_BotonProcesoMemoria_clicked()
{
    monitoreo = new Monitoreo(this);
    monitoreo ->show();
}
