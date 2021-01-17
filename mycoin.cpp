#include "mycoin.h"
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");//设置金币按钮的风格,为无边框
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer;
    timer2 = new QTimer;
    timer1->setParent(this);
    timer2->setParent(this);


    //监听正面翻转反面的信号,并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");//设置金币按钮的风格,为无边框
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了, 将min重置为1
        if(this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false; //说明动画播放结束
            timer1->stop();

        }
    });
    //监听银币翻转金币的信号,并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");//设置金币按钮的风格,为无边框
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了, 将max重置为8
        if(min > max)
        {
            this->max = 8;
            this->isAnimation = false; //说明动画播放结束
            timer2->stop();

        }
    });


}

void MyCoin::changgeFlag()//改变正面的方法
{
    if(this->isAnimation == true)//此方法可以防止,动画在执行的过程中,再次执行动画(定时器)
    {                            //或者重写一个鼠标按下事件mousePressEvent(QMouseEvent *event)
        return;                  //如果this->isAnimation == true,直接返回不做处理,否则返回给父类处理
    }
    //如果是正面 翻成反面
    if(this->flag)
    {
        //开始正面翻反面的定时器
        this->timer1->start(30);//每隔30毫秒执行一次 connect(timer2,&QTimer::timeout,[=](){ ,直至遇到stop为止
        this->isAnimation = true; // 说明此时动画已经在播放
        this->flag = false;
    }
    else
    {
        this->timer2->start(30);
        this->isAnimation = true; // 说明此时动画已经在播放
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isWin)//如果通关了,这里做了一次信号拦截操作,直接把点击信号拦截掉,不做任何处理,
    {              //也就是说如果全部都翻成金币了,就不能翻了
        return;
    }
    else//这里是将点击事件继续传递上去,硬币可以继续翻转
    {

        QPushButton::mousePressEvent(e);
    }
}
