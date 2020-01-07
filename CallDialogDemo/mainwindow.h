#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <vector>
typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

namespace Ui {
class MainWindow;
}

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QChart *createBarChart(int valueCount) const;

    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    QChart *createBarChartByVector(std::vector<float>& before_optim_data, std::vector<float>& after_optim_data) const;

private:
    Ui::MainWindow *ui;
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    DataTable m_dataTable;
};

#endif // MAINWINDOW_H
