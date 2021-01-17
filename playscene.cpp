#include "playscene.h"
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QPropertyAnimation>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug()<< str;
    this->levelIndex = levelNum;

    //初始化游戏场景

    this->setFixedSize(320,588);//设置固定大小
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));//设置图标
    this->setWindowTitle("翻金币"); //设置标题

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

    QSound* coinSound = new QSound(":/res/ConFlipSound.wav",this);//翻金币音效
    QSound* winSound = new QSound(":/res/LevelWinSound.wav",this);//胜利音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);//返回音效

    //返回按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");//返回按钮
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //告诉选择关卡场景  我返回了,在选择关卡场景中监听返回信号
        backSound->play();//返回按钮音效
        emit this->chooseScenBack();
        qDebug()<<"翻金币场景中,点击了返回按钮";

    });

    //显示当前的关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    //设置字体 字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体设置到label里
    QString str1 = QString("Level: %1 ").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);

    //label->setFixedSize();
   // label->move(100,500);这里可以直接使用 setGeometry
    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组,以便于对每关进行布局,把得到的数据零时存放至 this->gameArray
    dataConfig config;
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j =0; j<4; j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width())* 0.5 , -tmpPix.height());//注意这里第二个参数为负值,一开始是开不到的,在窗口外边


    //显示金币背景图案
    for(int i =0 ;i<4;i++)
    {
        for(int j =0 ;j<4 ;j++)
        {
            //绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode(1).png");
            QLabel* label = new QLabel(this);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            //label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png" ;//显示金币
            }
            else
            {
                str = ":/res/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,203+j*50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];//1正面 0反面

            //将金币放入到 金币的二维数组里 以便以后的维护
            coinBtn[i][j] = coin;


          //  if(coin->isAnimation == false)//这个if语句是没有意义的,执行的时候 coin->isanimation 肯定是false,并且信号创建成功

                connect(coin,&MyCoin::clicked,[=](){


                    for(int i = 0;i < 4 ; i++)                  //    由于周围金币的翻转有延时0.3秒的设定这里进行设置
                    {                                           //  在此期间为了防止玩家进行其他金币翻转的操作
                        for(int j=0;j<4;j++)                    //  防止禁止用户操作,所以在这里将所有按钮的属性都
                        {                                       //  设置成true
                            this->coinBtn[i][j]->isWin = true;  //
                        }                                       //
                    }                                           //
                    coinSound->play();
                    coin->changgeFlag();
                   // qDebug()<< coin;
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0 ;

                    //翻转周围硬币,并且延时
                    QTimer::singleShot(300,this,[=](){
                        allAroundTurn(coin,i,j);//实际上 i与j并不需要传递进去,因为有coin->posX和posY可以使用

                        //翻转完之后才可以进行操作,所以这里我们再重新设置成false
                        for(int i = 0;i < 4 ; i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                this->coinBtn[i][j]->isWin = false;
                            }
                        }



                        //判断是否胜利
                        this->isWin = true;
                        for(int i =0 ; i<4; i++)
                        {
                           for(int j=0;j<4;j++)
                           {
                              if(coinBtn[i][j]->flag == false) //说明只要有一个反面的金币,就算失败
                              {
                                  this->isWin = false;
                                  break;
                              }
                           }
                        }
                        if(this->isWin == true)
                        {
                            //胜利了
                            qDebug() << "游戏胜利";
                            //将所有按钮的胜利标志改为true;
                            for(int i =0 ; i<4; i++)
                            {
                               for(int j=0;j<4;j++)
                               {
                                    this->coinBtn[i][j]->isWin=true;
                               }
                            }

                            //将胜利的图片移动下来
                            QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");//第一个参数 实现特效的对象,第二个参数为以矩形框的形式实现特效
                            animation->setDuration(1500);//设置动画的持续时间
                            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));  //起始位置
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+175,winLabel->width(),winLabel->height()));//结束位置,将this->y的值增加,可以明星明显看出弹跳效果
                            animation->setEasingCurve(QEasingCurve::OutBounce);//设置弹跳曲线
                            animation->start();//执行动画

                            winSound->play();//播放胜利音效

                        }
                    });
                });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画上方的图标
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);//在上方居中显示
}

void PlayScene::allAroundTurn(MyCoin *coin,int i ,int j)
{
    if(coin->posX + 1 <= 3)//周围的右侧金币翻转的条件
    {
        coinBtn[coin->posX+1][coin->posY]->changgeFlag();
        this->gameArray[i+1][j] = this->gameArray[i+1][j] == 0 ? 1 : 0 ;
    }
    //左侧硬币翻转条件
    if(coin->posX - 1 >= 0)
    {
        coinBtn[coin->posX-1][coin->posY]->changgeFlag();
        this->gameArray[i-1][j] = this->gameArray[i-1][j] == 0 ? 1 : 0 ;
    }
    //翻转上侧硬币
    if(coin->posY - 1 >= 0)
    {
        coinBtn[coin->posX][coin->posY-1]->changgeFlag();
        this->gameArray[i][j-1] = this->gameArray[i][j-1] == 0 ? 1 : 0 ;
    }
    //翻转下侧硬币
    if(coin->posY + 1 <= 3)
    {
        coinBtn[coin->posX][coin->posY+1]->changgeFlag();
        this->gameArray[i][j+1] = this->gameArray[i][j+1] == 0 ? 1 : 0 ;
    }
}
