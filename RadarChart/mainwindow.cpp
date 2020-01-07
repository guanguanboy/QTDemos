#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "radarchart.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RadarChart * widget = new RadarChart(this);
        QList<RadarData> datas;
        datas<<RadarData("Jan",10)<<RadarData("Feb",30)<<RadarData("Mar",50)<<RadarData("Apr",90)<<RadarData("May",20);
        widget->setDatas(datas);
        widget->setAxisRange(0,100);
        this->setCentralWidget(widget);
        this->resize(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
