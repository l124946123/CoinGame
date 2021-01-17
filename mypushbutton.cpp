#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>//动画特性
//MyPushButton::MyPushButton()
//{

//}

MyPushButton::MyPushButton(QString normalimg, QString pressimg)
{
    this->normalImgPath = normalimg;
    this->pressImgPath = pressimg;

    QPixmap pix;
    bool ret = pix.load(normalimg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());//设置按钮固定大小,大小与图片一致
    this->setStyleSheet("QPushButton{border:0px}");//设置不规则图片样式,部件样式,这里对按钮的形态进行了隐藏
    this->setIcon(pix);//设置图标,当图片设置在按钮上时,会被缩放
    this->setIconSize(QSize(pix.width(),pix.height()));//重新设置图标大小

}

void MyPushButton::zoom1()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");//第一个参数 实现特效的对象,第二个参数为以矩形框的形式实现特效
    animation->setDuration(2000);//设置动画的持续时间
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));  //起始位置
    animation->setEndValue(QRect(this->x(),this->y()+100,this->width(),this->height()));//结束位置,将this->y的值增加,可以明星明显看出弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);//设置弹跳曲线
    animation->start();//执行动画
}

void MyPushButton::zoom2()
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(this,"geometry");//第一个参数 实现特效的对象,第二个参数为以矩形框的形式实现特效
    animation1->setDuration(200);//设置动画的持续时间
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //起始位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));//结束位置,将this->y的值增加,可以明星明显看出弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);//设置弹跳曲线
    animation1->start();//执行动画
}

void MyPushButton::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
    if(this->pressImgPath !="")//传入的按下图片不为空 说明这个实例有两张图片 需要有按下状态
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());//设置按钮固定大小,大小与图片一致
        this->setStyleSheet("QPushButton{border:0px}");//设置不规则图片样式,部件样式,这里对按钮的形态进行了隐藏
        this->setIcon(pix);//设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));//设置图标大小
    }

   return QPushButton::mousePressEvent(e);//让父类处理其他事件结果

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)//鼠标按钮抬起事件
{
    if(this->pressImgPath !="")//传入的按下图片不为空  说明这个实例有两张图片 需要有抬起状态,所以需要切换成默认图片
    {

        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());//设置按钮固定大小,大小与图片一致
        this->setStyleSheet("QPushButton{border:0px}");//设置不规则图片样式,部件样式,这里对按钮的形态进行了隐藏
        this->setIcon(pix);//设置图标
        this->setIconSize(QSize(pix.width(),pix.height()));//设置图标大小
    }

    return QPushButton::mouseReleaseEvent(e);//让父类处理其他事件结果
}
