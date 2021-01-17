#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
class  ChooseLevelScene;

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //重写paintEvent事件 添加背景图片
    virtual void paintEvent(QPaintEvent *event) override ;

    ChooseLevelScene* chooseScene = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
