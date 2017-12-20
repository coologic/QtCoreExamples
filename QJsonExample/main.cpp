#include <QCoreApplication>
#include <QJsonDocument>//json文档
#include <QJsonArray>//json数组
#include <QJsonObject>//json对象
#include <QJsonValue>//json值
#include <QJsonParseError>//错误处理
#include <QDebug>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QJsonDocument json;
    QJsonArray array;
    array.append(true);
    array.append(999);
    array.append("string");
    QJsonObject object;
    object.insert("Array",array);
    object.insert("Key","Value");
    //null用空的QJsonValue即可
    object.insert("null",QJsonValue());
    //最外层是大括号所以是object
    json.setObject(object);
    auto json_text = json.toJson(QJsonDocument::Compact);
    auto json_binary = json.toBinaryData();
    QJsonDocument read1 = QJsonDocument::
            fromJson(json_text);
    QJsonDocument read2 = QJsonDocument::
            fromBinaryData(json_binary);
    //验证两个是一样的
    if(QString(read1.toBinaryData()) ==
            QString(read2.toBinaryData()))
        qDebug()<<"same";
    //用于判断是否为空，对QJsonXXX对象均支持
    if(!read1.isEmpty())
        qDebug()<<"empty";
    //下面开始解析代码
    if(read1.isObject() ) {
        auto read_object = read1.object();
        if(!read_object.isEmpty()) {
            qDebug()<<read_object.value("Key").toString();
            qDebug()<<read_object.value("null").isNull();
            QJsonValue value = read_object.value("Array");
            qDebug()<<value.type()<<value;
            if(value.isArray()) {
                auto read_array = value.toArray();
                for(auto one_of_array : read_array)
                    qDebug()<<one_of_array;
                //此处建议判断好具体类型，因为array里面也可能有object
            }
        }
    }
    return 0;
}
