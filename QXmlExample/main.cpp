#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
/**
 * @brief Write xml
 */
void Write() {
    QFile file("test.xml");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("bookmark");
        stream.writeAttribute("href", "http://qt-project.org/");
        stream.writeTextElement("title", "Qt Project");
        stream.writeEndElement();
        stream.writeEndDocument();
        file.close();
        qDebug()<<"write ok";
        return;
    }
    qDebug()<<"write error";
    return;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Write();
    QFile file("test.xml");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        while (!xml.atEnd() && !xml.hasError()) {//循环逐行读取
            QXmlStreamReader::TokenType token = xml.readNext();
            if(token == QXmlStreamReader::StartDocument)//文件开始跳过
                continue;
            if(token == QXmlStreamReader::StartElement) {//StartElement类型，主要针对bookmark和title
                if(xml.name() == "bookmark") {//bookmark读取，其下attributes有但只有一个
                    qDebug()<<"StartElement-"<<xml.name();
                    QXmlStreamAttributes attributes = xml.attributes();
                    if(attributes.hasAttribute("href")) {//针对href的attribute做判断
                        qDebug()<<"Attributes-"<<attributes.value("href");//返回值是QStringRef
                    }
                    //多个attributes在这里增加更多的if
                    continue;
                }
                if(xml.name() == "title") {//title
                    xml.readNext();//没有attributes，理应直接进入while，此处偷懒了
                    if(xml.isCharacters()) //可以做Characters判断也可以直接用text
                        qDebug()<<"title-Characters-"<<xml.text();
                }
            }
        }
        if (xml.hasError()) {
            //范例，判断枚举类型，写出错误字符串
            if(xml.error() == QXmlStreamReader::CustomError) {
                //可以直接写出错误字符串
                qDebug()<<"error:" <<xml.errorString();
            }
        }
    }
    return 0;
}
