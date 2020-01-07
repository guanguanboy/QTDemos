#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QStandardItemModel>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
     m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))
{
    ui->setupUi(this);

    setWindowTitle(tr("全系统全流程抗干扰动态分析子系统"));

    QGridLayout *baseLayout = new QGridLayout();

    QChartView *chartView;

    chartView = new QChartView(createBarChart(m_valueCount));
    baseLayout->addWidget(chartView, 1, 1);

//    QChartView *chartView2;

//    chartView2 = new QChartView(createBarChart(m_valueCount));


    std::vector<float> before_optim_data;
    std::vector<float> after_optim_data;

    for(int i = 0; i< 7;i++)
    {
        before_optim_data.push_back(i+0.2);
        after_optim_data.push_back(i + 0.3);
    }

    QChartView *chartView2;

    chartView2 = new QChartView(createBarChartByVector(before_optim_data, after_optim_data));

    baseLayout->addWidget(chartView2, 2, 1);

    setLayout(baseLayout);
    ui->groupBox_barChart->setLayout(baseLayout);

    //准备数据模型
    QStandardItemModel *item_model = new QStandardItemModel();
    item_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("名称")));
    item_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("优化前综指")));
    item_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("评价")));
    item_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("优化后综指")));
    item_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("评价")));
    item_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("贡献率")));
    item_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("评价")));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(item_model);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QChart *MainWindow::createBarChartByVector(std::vector<float>& before_optim_data, std::vector<float>& after_optim_data) const
{
    //! 建立柱状图1
    QChart *chart = new QChart();
    chart->setTitle("综合评估指标");
    QBarSeries *series = new QBarSeries(chart);

    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");

    for (int i = 0; i < before_optim_data.size(); i++)
    {
        *set0 << before_optim_data[i];
        *set1 << after_optim_data[i];
    }

    series->append(set0);
    series->append(set1);

    chart->createDefaultAxes();
    chart->addSeries(series);

    return chart;
}

QChart *MainWindow::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        foreach (Data data, m_dataTable[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();

    return chart;
}

DataTable MainWindow::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}
