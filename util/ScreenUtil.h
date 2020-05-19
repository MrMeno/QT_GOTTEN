#ifndef SCREENUTIL_H
#define SCREENUTIL_H

#include <QObject>

class ScreenUtil:public QObject
{
    Q_OBJECT
public:
   explicit ScreenUtil(QObject *parent = nullptr);
    ~ScreenUtil();
};

#endif // SCREENUTIL_H
