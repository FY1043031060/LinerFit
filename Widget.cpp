#include "Widget.h"
#include "ui_Widget.h"
#include <cmath>
#include <CZW.h>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    const int DATA_SIZE = 512;
    double m_x[DATA_SIZE] ={0};
    double m_y[DATA_SIZE] ={0};
    double m_yploy[DATA_SIZE] ={0};
    for(size_t i =0;i< DATA_SIZE;++i)
    {
        m_x[i] = i;
        m_y[i] = i+randf(-25,28);
        m_yploy[i] = 0.005*pow(double(i),2)+0.0012*i+4+randf(-25,25);

    }
    czy::Fit fit;
    fit.linearFit(m_x, m_y, DATA_SIZE);
    QString str;
    str= QString::asprintf(u8"方程：y=%gx+%g \n误差：ssr:%g,sse=%g,rmse:%g,确定系数:%g \n",fit.getSlope(),fit.getIntercept()
                           ,fit.getSSR(),fit.getSSE(),fit.getRMSE(),fit.getR_square());
    qDebug() << str;
    for (int i = 0; i < DATA_SIZE; i++)
    {
        qDebug()<<m_x[i]<<"       "<< m_y[i] << "\n";
    }
    qDebug()<< "-------\n";

    czy::Fit fitPoly;
    fitPoly.polyfit(m_x, m_yploy, DATA_SIZE, 2);
    QString strFun("y="), strTemp("");
    for (int i=0; i<fitPoly.getFactorSize(); ++i)
    {
        if (0 == i)
        {
            strTemp = QString::asprintf(("%g"), fitPoly.getFactor(i));
        }
        else
        {
            double fac = fitPoly.getFactor(i);
            if (fac<0)
            {
                strTemp = QString::asprintf(("%gx^%d"),fac,i);
            }
            else
            {
                strTemp = QString::asprintf(("+%gx^%d"),fac,i);
            }
        }
        strFun += strTemp;
    }
    str = QString::asprintf(u8"方程：%s \n 误差：ssr:%g,sse=%g,rmse:%g,确定系数:%g \n", strFun.toStdString().c_str()
                            ,fitPoly.getSSR(),fitPoly.getSSE(),fitPoly.getRMSE(),fitPoly.getR_square());
    qDebug() << str;
    for (int i = 0; i < DATA_SIZE; i++)
    {
        qDebug()<<m_x[i]<<"      "<< m_yploy[i] << "\n";
    }
}

Widget::~Widget()
{
    delete ui;
}
double Widget::randf(double min,double max)
{
    int minInteger = (int)(min*10000);
    int maxInteger = (int)(max*10000);
    int randInteger = rand()*rand();
    int diffInteger = maxInteger - minInteger;
    int resultInteger = randInteger % diffInteger + minInteger;
    return resultInteger/10000.0;
}
