#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public :
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString  btnImg);//参数代表 传入的是金币路径 还是银币

    //金币的属性
    int posX;//x坐标位置
    int posY;//y坐标位置
    bool flag;//正反表示

    //改变标志的方法
    void changgeFlag();
    QTimer* timer1;//金币翻银币的定时器
    QTimer* timer2;//银币翻金币的定时器
    int max = 8;
    int min = 1;

    //执行动画标志,作用是防止用户连续点击
    bool isAnimation = false;

    bool isWin = false;//是否胜利的标志,注意这里一定要初始化,否则iswin里将会是一个随机值,信号最终会被拦截,导致一开始就无法翻转金币

    virtual void mousePressEvent(QMouseEvent *e) override;

signals:

public slots:
};

#endif // MYCOIN_H
