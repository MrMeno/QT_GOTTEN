#include "ScreenCaputredEvent.h"

ScreenCaputredEvent::ScreenCaputredEvent(Type ScreenCaputredEventType):QEvent(ScreenCaputredEventType){}
ScreenCaputredEventSender::ScreenCaputredEventSender(int argc,char *argv[]):QCoreApplication(argc,argv){}


bool ScreenCaputredEventSender::notify(QObject *receiver, QEvent *event)
{
    if(event->type() == ScreenCaputredEventType)
    {
        qDebug()<<"ScreenCaputredEventType is coming!";
        //return true;
        /*这里不能return true,因为重写notify就是在事件被向下传递之前截住它，
        随便搞它，搞完了还得给QCoreApplication::notify向下传递，除非在mySender.notify
        实现了事件向下传递的那一套。直接返回的话myArmy就收不到这个事件，因为执行完这个
        mySender.notify的return true后，事件传递被人为的在半截终止了
        （见Qt事件处理的五个层次http://blog.csdn.net/michealtx/article/details/6865891 ）
        ，下面的myArmy的安装的过滤器和它自己的event都不会收到这个事件，更甭提最后干活
        的myEventHandler了。所以在主函数中执行完mySender.sendEvent把myEvent
        交给mySender.notify这个败家子儿后，就执行mySender.exec进入其它事件的循环了。这就是
        问题http://topic.csdn.net/u/20111012/19/78036d16-c163-40f9-a05c-3b7d6f4e9043.html
        出现的原因。感谢1+1=2大牛！非常感谢！
        */
    }
    return QCoreApplication::notify(receiver,event);
}
bool ScreenCaputredEventWatcher::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == ScreenCaputredEventType)
    {
        qDebug()<<"I don't wanna filter MyEventType";
        return false;
     }
    return QObject::eventFilter(watched,event);
}
void ScreenCaputredEventArgs::ScreenCaputredEventHandler(QEvent *event)
{
    qDebug()<<"The event is being handled!";
    event->accept();

}

bool ScreenCaputredEventArgs::event(QEvent *event)
{
    if(event->type() == ScreenCaputredEventType)
    {
        qDebug()<<"event() is dispathing MyEvent";
        ScreenCaputredEventHandler(event);//调用事件处理函数
        if((ScreenCaputredEvent*)event->isAccepted())
        {
            qDebug()<<"The event has been handled!";
            return true;
        }
    }
    return QObject::event(event);
}

