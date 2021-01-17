#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paintEvent事件 添加背景图片
    virtual void paintEvent(QPaintEvent *event) override ;

    PlayScene* play = NULL;//游戏场景对象


signals:
     void chooseScenBack();//发送给主场景的信号,用于返回主场景

public slots:
};

#endif // CHOOSELEVELSCENE_H
