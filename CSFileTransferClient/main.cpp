#include "maindialog.h"

#include <QApplication>
#include <QtDebug>
#include <QException>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


        qDebug() << "程序启动...";
        qDebug() << "可用内存:" << QSysInfo::buildCpuArchitecture();

        try {
            qDebug() << "正在创建 MainDialog 对象...";
            MainDialog w;

            qDebug() << "正在显示窗口...";
            w.show();

            qDebug() << "进入事件循环...";
            return a.exec();
        }
        catch (const std::bad_alloc &e) {
            qDebug() << "内存分配失败:" << e.what();
            qDebug() << "请检查是否有大内存分配操作";
            return 1;
        }
        catch (const std::exception &e) {
            qDebug() << "标准异常:" << e.what();
            return 1;
        }
        catch (...) {
            qDebug() << "未知异常";
            return 1;
        }
    MainDialog w;

    //显示窗口最小化按扭
    w.setWindowFlags(w.windowFlags()|Qt::WindowMinimizeButtonHint);
    w.show();
    return a.exec();
}
