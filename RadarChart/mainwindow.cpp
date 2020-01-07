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
        datas<<RadarData("成控度",10)<<RadarData("贡献度",30)<<RadarData("承受度",50)<<RadarData("普适度",40)<<RadarData("体验度",20);
        widget->setDatas(datas);
        widget->setAxisRange(0,50);
        this->setCentralWidget(widget);
        this->resize(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
