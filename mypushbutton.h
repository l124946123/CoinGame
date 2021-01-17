#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
  // explicit MyPushButton(QWidget * parent = 0);
    //构造函数 参数1 正常显示的图片路径 参数2  按下后显示的图片路径
   MyPushButton(QString normalimg,QString pressimg ="");
   //成员属性 保存用户传入的默认显示路径 以及按下后显示的图片路径
   QString normalImgPath;
   QString pressImgPath;

   //弹跳特效
   void zoom1();//向下跳
   void zoom2();//向上跳

   virtual void mousePressEvent(QMouseEvent* e ) override;
   virtual void mouseReleaseEvent (QMouseEvent* e ) override;

};

#endif // MYPUSHBUTTON_H
