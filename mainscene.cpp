#include "mainscene.h"
#include "ui_mainscene.h"
#include  "mypushbutton.h"
#include  "chooselevelscene.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    this->setFixedSize(320,588);//设置固定大小

    this->setWindowIcon(QIcon(":/res/Coin0001.png"));//设置窗口标题栏图标
    this->setWindowTitle("翻金币主场景");//设置标题
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //主场景准备按钮音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);
   // startSound->setLoops(10); // 设置播放次数,参数-1为无限循环
   // startSound->play();

   //设置开始按钮
   MyPushButton* startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
   startBtn->setParent(this);//设置父窗口
   startBtn->move((this->width() - startBtn->width())*0.5,this->height()*0.7);//用屏幕宽度的一半减去按钮大小的一半,找到按钮的居中的位置
   this->chooseScene  = new ChooseLevelScene;//这里的关卡选择界面是先创建好了的,在下面点击了开始再显示出来,而游戏界面则不同,是点击之后再进行创建和显示的

   connect(startBtn,&MyPushButton::clicked,[=](){
       qDebug() << "点击了开始";

       //播放音效资源
       startSound->play();


       //做按钮图标弹起的特效
       // startBtn->zoom1();,但是只有一个函数起了作用
        startBtn->zoom2();

        QTimer::singleShot(500,this,[=](){//延时进入到选择关卡场景汇总
            this->hide();  //自身隐藏
            chooseScene->setGeometry(this->geometry());//点击进入选择关卡界面后,是选择关卡界面与开始界面位置保持一致
            chooseScene->show();//进入到选择关卡的场景中       
        });      
   });

   connect(chooseScene,&ChooseLevelScene::chooseScenBack,[=](){//接收选择关卡界面传回的信号,重新回到开始界面
           QTimer::singleShot(500,this,[=](){
           chooseScene->hide();
           this->setGeometry(chooseScene->geometry());//返回开始界面是,让开始界面与选择关卡界面的位置保持一致
           this->show();         
           });
   });

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //painter.drawPixmap(0,0,pix);使用这种版本无法让图片充满窗口,因为图片像素没有窗口大
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画左上角的图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);//将图片进行缩放
    painter.drawPixmap(10,30,pix);
   // painter.drawPixmap(10,35,150,50,pix);也可以直接使用这个坐标

}
