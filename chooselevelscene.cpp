#include "chooselevelscene.h"
#include "mypushbutton.h"
#include "playscene.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));//设置图标
    this->setWindowTitle("设置关卡场景");//设置标题

    //创建菜单栏
    QMenuBar* bar =  this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction* quitAction = startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });

    //创建选择关卡的音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);


    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");//返回按钮
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //告诉主场景  我返回了,主场景监听返回按钮
        backSound->play();
        emit this->chooseScenBack();

    });
    //创建选择关卡的按钮
    for(int i=0;i<20;i++ )//可以使用一个for循环来排列按钮,在move函数中就需要使用取余和除法来计算位置
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4 *70, 130+i/4 *70 );

        connect(menuBtn,&MyPushButton::clicked,[=](){

            chooseSound->play();//播放音效

            QString str = QString("您选择的是第 %1 关").arg(i+1);
            qDebug()<<str;
            //进入到关卡场景 开始玩游戏
            this->hide();//隐藏选择关卡场景
            play = new PlayScene(i+1);//play 作为一个独立的主窗口,和chooselevelscene类 一样,没有父窗口
            play->setGeometry(this->geometry());//与选择关卡的场景保持一致位置
            play->show();

            connect(play,&PlayScene::chooseScenBack,[=](){

                QTimer::singleShot(500,this,[=](){//延时进入到选择关卡场景汇总
               // play->hide();  这里一共有20关 ,如果仅仅只是隐藏,太耗费内存了
                this->setGeometry(play->geometry());//返回选择关卡场景时,让选择关卡场景与游玩场景位置一致
                this->show();
                delete play; //由于没有父窗口,该对象在对象树上 这里进行手动释放内存,以节约空间
                play = NULL;

                });
            });
        });

        QLabel* label = new QLabel(this);
        //label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));//将数字转换成字符串显示
        label->move(25+i%4 *70, 130+i/4 *70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置 label上的文字对齐,水平加垂直居中

        //由于QLabel的在每个MyPushButton的上方 ,所有按钮信号无法传达到 该按钮上,被QLabel部件给阻挡了
        //设置让鼠标点击信号进行穿透给按钮,设置51号属性也就是Qt::WA_TransparentForMouseEvents
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画上方的图标
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);//在上方居中显示

}
