#include <QCoreApplication>
#include <QDebug>
#include <QTemporaryFile>
#include <QTemporaryDir>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc,argv);
    QTemporaryFile testfile1;//建立第一个文件
    qDebug()<<"testfile1"<<testfile1.fileName()
           <<testfile1.fileTemplate();
    //第一次open之前文件是没有建立的，所以没名字
    testfile1.open();
    testfile1.close();
    qDebug()<<"testfile1"<<testfile1.fileName()
           <<testfile1.fileTemplate();
    //只要对象不被销毁，可以重复open，不会变文件
    testfile1.open();
    qDebug()<<"testfile1"<<testfile1.fileName()
           <<testfile1.fileTemplate();
    //指定名字
    QTemporaryFile testfile2("testfile2");
    testfile2.open();
    qDebug()<<"testfile2"<<testfile2.fileName()
           <<testfile2.fileTemplate();
    //建立一个重名的
    QTemporaryFile testfile3("testfile2");
    testfile3.open();
    qDebug()<<"testfile3"<<testfile3.fileName()
           <<testfile3.fileTemplate();
    //在QTemporaryDir临时目录下建立一个
    QTemporaryDir testdir1;
    qDebug()<<"testdir1"<<testdir1.filePath("testfile4.txt");
    QTemporaryFile testfile4(testdir1.filePath("testfile4.txt"));
    testfile4.open();
    qDebug()<<"testfile4"<<testfile4.fileName()
           <<testfile4.fileTemplate();
    //注意最后一个就算文件名定义了txt后缀，夜壶自动在后面加.xxxxxx
    //QTemporaryFile继承了QFile，在open以后可以直接进行QFile的所有操作
    return 0;
}
