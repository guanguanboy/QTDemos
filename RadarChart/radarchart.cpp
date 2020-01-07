#include "radarchart.h"

RadarChart::RadarChart(QWidget *parent) : QWidget(parent)
{
    init();
}
void RadarChart::setDatas(const QList<RadarData> &datas)
{
    m_datas = datas;
    m_AngularCount = m_datas.count();
    this->update();
}
void RadarChart::setRadarType( RadarType radartype )
{
    m_radartype = radartype;
    this->update();
}
void RadarChart::setPointTpye( PointTpye pointstype )
{
    m_pointstype = pointstype;
    this->update();
}
void RadarChart::setAxisRange(qreal min,qreal max)
{
    m_Axis_min = min;
    m_Axis_max = max;
    this->update();
}
void RadarChart::init()
{
    m_radartype = Spider;
    m_pointstype = LinePoints;
    m_showRadialAxisLabel = true;
    m_showAngularAxisLabel = true;
    m_AngularCount = 0;
    m_titleFont = QFont("Arial",12,QFont::Bold);
    m_titleColor = Qt::black;
    m_tickCount = 3;  //表示的是横隔线的数量
    m_Axis_min = 0;
    m_Axis_max = 10;
    m_AngularLineColor = Qt::black;
    m_RadialLineColor = Qt::black;
    m_AngularLabelColor = Qt::black;
    m_RadialLabelColor = Qt::black;
    m_seriesColor = QColor(102,170,238);
    m_labelFont = QFont("Arial",9);
    m_backgroundColor = Qt::white;
}
void RadarChart::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::TextAntialiasing);
    //添加背景颜色
    painter.save();
    painter.setBrush(m_backgroundColor);
    painter.drawRect(0,0,width(),height());
    painter.restore();
    drawTitle(&painter);
    drawData(&painter);
    drawRadarType(&painter);
    drawRadialLabel(&painter);
    drawAngularLabel(&painter);
    QWidget::paintEvent(event);
}
void RadarChart::drawTitle(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setColor(m_titleColor);
    painter->setPen(pen);
    painter->setFont(m_titleFont);
    qreal w = width();
    QFontMetricsF fontMetrics(m_titleFont);
    qreal strWidth = fontMetrics.width(m_title);
    qreal strHeight = fontMetrics.height();
    qreal cur_x,cur_y;
    cur_x = w / 2 - strWidth / 2;
    cur_y = 10 + strHeight;
    m_titleHeight = cur_y + 5;
    painter->drawText(cur_x,cur_y,m_title);
    painter->restore();
}
void RadarChart::drawRadarType( QPainter *painter )
{
    switch (m_radartype)
    {
        case Radar:drawRadar(painter);break;
        case Spider:drawSpider(painter);break;
        default:drawRadar(painter);break;
    }
}
void RadarChart::drawRadar( QPainter *painter )
{
    painter->save();
    QPen pen;
    pen.setWidthF(0.4);
    pen.setColor(m_AngularLineColor);
    painter->setPen(pen);
    qreal w = width();
    qreal h = height() - m_titleHeight;
    //绘制环线
    qreal radius = qMin(w,h)/2; //半径
    qreal step = radius/(m_tickCount+1);  //每环之间的距离
    qreal x0 = w/2 ;    //中心点X坐标
    qreal y0 = h/2 + m_titleHeight;     //中心点Y坐标
    qreal cur_x,cur_y;
    QPainterPath loopPath;
    for (int i = 1; i < m_tickCount+1; ++i)
    {
        qreal curRadius = step*i;
        loopPath.addEllipse(QPointF(x0, y0), curRadius, curRadius);
    }
    painter->drawPath(loopPath);
    pen.setColor(m_RadialLineColor);
    painter->setPen(pen);
    //绘制中心到边缘的直线
    qreal dRadian = PI*2 / m_AngularCount;  //每个环形标签之间的夹角
    for (int i = 0 ; i < m_AngularCount; ++i)
    {
        cur_x = x0 + radius*qSin(dRadian*i);
        cur_y = y0 - radius*qCos(dRadian*i);
        painter->drawLine(x0,y0,cur_x,cur_y);
    }
    painter->restore();
}
void RadarChart::drawSpider( QPainter *painter )
{
    painter->save();
    QPen pen;
    pen.setWidthF(0.4);
    pen.setColor(m_AngularLineColor);
    painter->setPen(pen);
    qreal w = width();
    qreal h = height() - m_titleHeight;
    qreal radius = qMin(w,h)/2;
    qreal step = radius/(m_tickCount+1);
    qreal dRadian = PI*2 / m_AngularCount;
    qreal x0 = w/2 ;
    qreal y0 = h/2 + m_titleHeight;
    qreal cur_x,cur_y;
    QPointF *points = new QPointF[m_AngularCount + 1];
    for (int j = 1 ; j < m_tickCount + 1; ++j)
    {
        qreal curRadius = step*j;
        for (int i = 0 ; i < m_AngularCount; ++i)
        {
            cur_x = x0 + curRadius*qSin(dRadian*i);
            cur_y = y0 - curRadius*qCos(dRadian*i);
            points[i] = QPointF(cur_x,cur_y);
        }
        points[m_AngularCount] = points[0];
        painter->drawPolyline(points,m_AngularCount + 1);
    }
    pen.setColor(m_RadialLineColor);
    painter->setPen(pen);
    for (int i = 0 ; i < m_AngularCount; ++i)
    {
        painter->drawLine(x0,y0,points[i].x(),points[i].y());
    }
    delete []points;
    painter->restore();
}
void RadarChart::drawRadialLabel( QPainter *painter )
{
    if (!m_showRadialAxisLabel) return;
    painter->save();
    qreal w = width();
    qreal h = height() - m_titleHeight;
    qreal radius = qMin(w,h)/2;
    qreal step = radius/(m_tickCount+1);
    qreal x0 = w/2 ;
    qreal y0 = h/2 + m_titleHeight;
    qreal cur_x,cur_y;
    QPen pen;
    pen.setColor(m_RadialLabelColor);
    painter->setPen(pen);
    painter->setFont(m_labelFont);
    qreal dY = (m_Axis_max - m_Axis_min)/(m_tickCount);
    qreal offset = 20;
    if( step < 40 )
        offset = step / 2;
    for (int j = 0 ; j < m_tickCount+1; ++j)
    {
        qreal curRadius = step*j;
        cur_x = x0 + 2;
        cur_y = y0 - curRadius + offset;
        qreal value = m_Axis_min + dY * j;
        QString str = QString::number(value,'f',2);
        painter->drawText(cur_x,cur_y,str);
    }
    painter->restore();
}
void RadarChart::drawAngularLabel( QPainter *painter )
{
    if (!m_showAngularAxisLabel) return;
    painter->save();
    qreal w = width();
    qreal h = height() - m_titleHeight;
    qreal radius = qMin(w,h)/2;
    qreal x0 = w/2 ;
    qreal y0 = h/2 + m_titleHeight;
    qreal newRadius = m_tickCount * radius/(m_tickCount+1) + 5;
    qreal cur_x,cur_y;
    qreal dRadian = PI*2 / m_AngularCount;
    QPen pen;
    pen.setColor(m_RadialLabelColor);
    painter->setPen(pen);
    painter->setFont(m_labelFont);
    QFontMetricsF fontMetrics(m_labelFont);
    qreal strWidth,strHeight;
    qreal dError;
    for (int i = 0 ; i < m_AngularCount; ++i)
    {
        cur_x = x0 + newRadius*qSin(dRadian*i);
        cur_y = y0 - newRadius*qCos(dRadian*i);
        strWidth = fontMetrics.width(m_datas.at(i).name);
        strHeight = fontMetrics.height();
        dError = abs(cur_x - x0);
        if( dError < 1e-8 )         //cur_x == x0
            cur_x -= strWidth / 2;
        else
        {
            if( cur_x < x0 )
                cur_x = cur_x - strWidth - 2;
            else if( cur_x > x0 )
                cur_x += 2;
        }
        dError = abs(cur_y - y0);
        if( dError < 1e-8 )         //cur_y == y0
            cur_y += strHeight / 2;
        else
        {
            if( cur_y > y0 )
                cur_y -= strHeight *qCos(dRadian*i) ;
            else if( cur_y < y0 )
                cur_y = cur_y - strHeight *qCos(dRadian*i) + strHeight;
        }
        painter->drawText(cur_x,cur_y,m_datas.at(i).name);
    }
    painter->restore();
}
void RadarChart::drawData( QPainter *painter )
{
    switch(m_pointstype)
    {
    case ScatterPoints:drawScatterPoints(painter);break;
    case LinePoints:drawLinePoints(painter);break;
    default:drawLinePoints(painter);break;
    }
}
void RadarChart::drawScatterPoints( QPainter *painter )
{
    painter->save();
    qreal w = width();
    qreal h = height() - m_titleHeight;
    qreal radius = qMin(w,h)/2;
    qreal x0 = w/2 ;
    qreal y0 = h/2 + m_titleHeight;
    radius = m_tickCount * radius/(m_tickCount+1);
    qreal cur_x,cur_y;
    qreal dRadian = PI*2 / m_AngularCount;
    qreal step = 1.0*radius/(m_Axis_max-m_Axis_min);
    painter->setPen(m_seriesColor.darker(200));
    painter->setBrush(m_seriesColor.darker(200));
    for( int i = 0; i < m_AngularCount ; i++ )
    {
        qreal valueLength = m_datas.at(i).value * step;
        cur_x = x0 + valueLength*qSin(dRadian*i);
        cur_y = y0 - valueLength*qCos(dRadian*i);
        painter->drawEllipse(QPointF(cur_x,cur_y),4,4);
    }
    painter->restore();
}
void RadarChart::drawLinePoints( QPainter *painter )
{
    painter->save();
    qreal w = width();
    qreal h = height() - m_titleHeight;
    qreal radius = qMin(w,h)/2;
    qreal x0 = w/2 ;
    qreal y0 = h/2 + m_titleHeight;
    radius = m_tickCount * radius/(m_tickCount+1);
    qreal cur_x,cur_y;
    qreal dRadian = PI*2 / m_AngularCount;
    qreal step = 1.0*radius/(m_Axis_max-m_Axis_min);
    painter->setPen(m_seriesColor.darker(200));
    painter->setBrush(m_seriesColor.darker(200));
    QPointF *points = new QPointF[m_AngularCount];
    for( int i = 0; i < m_AngularCount ; i++ )
    {
        qreal valueLength = m_datas.at(i).value * step;
        cur_x = x0 + valueLength*qSin(dRadian*i);
        cur_y = y0 - valueLength*qCos(dRadian*i);
        points[i] = QPointF(cur_x,cur_y);
        painter->drawEllipse(QPointF(cur_x,cur_y),2,2);
    }
    painter->setBrush(m_seriesColor.lighter(100));
    painter->drawPolygon(points,m_AngularCount);
    painter->restore();
}
