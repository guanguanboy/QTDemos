#ifndef RADARCHART_H
#define RADARCHART_H

//#include <QWidget>

//class RadarChart : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit RadarChart(QWidget *parent = nullptr);

//signals:

//public slots:
//};

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "qmath.h"
enum RadarType
{
    Radar,  //雷达图
    Spider    //蛛网图
};
enum PointTpye
{
    ScatterPoints, //散点图
    LinePoints       //连线图
};
struct RadarData
{
    RadarData(const QString& _name,const qreal &_value){ name = _name;value=_value;}
    QString name;
    qreal value;
};
#define  PI M_PI
class RadarChart : public QWidget
{
    Q_OBJECT
public:
    explicit RadarChart(QWidget *parent = 0);
    void setRadarType(RadarType radartype);
    void setPointTpye(PointTpye pointstype);
    void setRadialAxisLabelVisible(bool visible){ m_showRadialAxisLabel = visible;this->update();}
    void setAngularAxisLabelVisible(bool visible){ m_showAngularAxisLabel = visible;this->update();}
    void setTitle(const QString &title){ m_title = title;this->update(); }
    void setTitleFont(const QFont &titleFont){ m_titleFont = titleFont; this->update();}
    void setTitleColor(const QColor &titleColor){ m_titleColor = titleColor; this->update();}
    void setDatas(const QList<RadarData> &datas);
    void setTickCount(int tickCount){ m_tickCount = tickCount; this->update();}
    void setAxisRange(qreal min,qreal max);
    void setAngularLineColor(const QColor &color){ m_AngularLineColor = color;this->update();}
    void setRadialLineColor(const QColor &color){ m_RadialLineColor = color;this->update();}
    void setAngularLabelColor(const QColor &color){ m_AngularLabelColor = color;this->update();}
    void setRadialLabelColor(const QColor &color){ m_RadialLabelColor = color;this->update();}
    void setSeriesColor(const QColor &color){ m_seriesColor = color;this->update();}
    void setbackgroundColor(const QColor &color){ m_backgroundColor = color;this->update();}
    void setLabelFont(const QFont &labelFont){ m_labelFont = labelFont; this->update();}
protected:
    void paintEvent(QPaintEvent *event);
private:
    void init();
    void drawTitle(QPainter *painter);
    void drawRadarType(QPainter *painter);
    void drawRadar(QPainter *painter);
    void drawSpider(QPainter *painter);
    void drawRadialLabel(QPainter *painter);
    void drawAngularLabel(QPainter *painter);
    void drawData(QPainter *painter);
    void drawScatterPoints(QPainter *painter);
    void drawLinePoints(QPainter *painter);
private:
    RadarType m_radartype;
    PointTpye m_pointstype;
    bool m_showRadialAxisLabel;
    bool m_showAngularAxisLabel;
    QString m_title;
    QFont m_titleFont;
    QColor m_titleColor;
    QList<RadarData> m_datas;
    int m_tickCount;
    int m_AngularCount;
    qreal m_Axis_min;
    qreal m_Axis_max;
    QColor m_AngularLineColor;
    QColor m_RadialLineColor;
    QColor m_AngularLabelColor;
    QColor m_RadialLabelColor;
    QColor m_seriesColor;
  QColor m_backgroundColor;

    QFont m_labelFont;
    qreal m_titleHeight;
};


#endif // RADARCHART_H
