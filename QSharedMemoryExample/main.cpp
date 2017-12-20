#include <QCoreApplication>
#include <QSharedMemory>
#include <QDebug>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    //创建的同时设置key,也可以setKey
    QSharedMemory sm("test_shared");
    //如果是第一个使用必须先创建
    //其余进程不需要创建直接attach
    if(!sm.create(1024))
        qDebug()<<"create error";
    sm.attach();//绑定内存
    //attach会返回bool，可以不用下面方式判断
    if(!sm.isAttached())
        qDebug()<<"attach error";
    sm.lock();
    int *memdata = static_cast<int*>( sm.data() );
    *memdata = 1024;
    sm.unlock();
    //如此偷懒！想要测试多进程把下面拷走建项目
    QSharedMemory testsm("test_shared");
    testsm.attach();
    int *testdata = static_cast<int*>( testsm.data() );
    qDebug()<<*testdata;
    //使当前进程与内存分离，析构的时候也会自动调用
    sm.detach();
    return a.exec();
}
