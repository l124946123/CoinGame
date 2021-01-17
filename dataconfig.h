#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:
    explicit dataConfig(QObject *parent = 0);

public:

    QMap<int, QVector< QVector<int> > >mData;
    /*使用QMap容器来存储每一关的布局,每一关有一个键值与一个类似于2维数组的容器,这个2维数组
   是使用了两个QVector容器进行嵌套  */


signals:

public slots:
};

#endif // DATACONFIG_H
