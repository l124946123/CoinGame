#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    int levelIndex;

    virtual void paintEvent(QPaintEvent *event)override; //重写paintEvent事件
    int gameArray[4][4]; //2维数组 维护每个关卡的具体数据

    MyCoin* coinBtn[4][4];//每个创建出来的金币对象一共16个,用于维护使用

    void allAroundTurn(MyCoin* coin,int i,int j);//四周金币翻转的方法

    //是否胜利的标志
    bool isWin;

signals:
    void chooseScenBack();
public slots:
};

#endif // PLAYSCENE_H
