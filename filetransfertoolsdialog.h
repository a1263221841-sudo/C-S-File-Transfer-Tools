#ifndef FILETRANSFERTOOLSDIALOG_H
#define FILETRANSFERTOOLSDIALOG_H

#include <QDialog>
//设置执行字符集为UTF-8,防止中文乱码
#include <QTcpServer>//tcp服务器类
#include <QFile> //文件操作类
#include <QtNetwork>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>  //绘图工具类



QT_BEGIN_NAMESPACE
namespace Ui { class FileTransferToolsDialog; }
QT_END_NAMESPACE

class FileTransferToolsDialog : public QDialog
{
    Q_OBJECT

public:
    FileTransferToolsDialog(QWidget *parent = nullptr);
    ~FileTransferToolsDialog();

    //网络通信组件
    QTcpServer *P_TCPServerObject;       //tcp服务器对象指针(监听连接)
    QTcpSocket *P_TCPTextScoketObject;  //文本数据传输socke对象指针(处理双方聊天消息)
    QTcpSocket *P_TCPFileScoketObject;   //文件传输socket对象指针(处理文件传输)

    //文件传输相关成员变量
    qint64 m_FileTotalBytes;  //文件总字体数
    qint64 m_FileBytesReceived; //已接收文件字节数
    qint64 m_FileNameSizes;   //文件名称长度(字节)
    qint64 m_FileNames;    //接收的文件名
    QFile *m_LocalFiles;    //本地文件对象指针(用于保存接收文件)
    QByteArray m_InBlaocks; //接收数据缓冲区(存储文件数据块)

    //获取本地Ip地址/重绘事件处理(设置窗口背景)
    QString GetLocalInAddressFunc();  //获取本机IP地址
    void paintEvent(QPaintEvent *ev);  //重绘事件处理(设置窗口背景)

protected:
    //时间处理
    void closeEvent(QCloseEvent *event);//窗口关闭事件处理(停止监听并释放资源)
private slots:
    //TCP服务器相关槽函数
    void OnNewConnectionFunc();//处理新连接请求(当有客户端连接时触发)

    //文本通道槽函数
    void OnClientConnectedFunc();  //文本socket连接成功处理
    void OnClientDisconnectedFunc();//文本socket断开连接处理
    void OnSocketReadyReadFunc();//读取客户端发送的文本数据

    //文件通道槽函数
    void OnFileClientConnectedFunc();//文件socket连接成功处理
    void OnFileClientDisconnectedFunc();//文件socket连接断开处理

    //业务逻辑槽函数
    void UpdateServerProgressFunc();//更新文件接收进度条状态
    void DisplayErrorInfoFunc(QAbstractSocket::SocketError socketError);//显示socket错误

private slots:
    void on_pushButton_StartListen_clicked();

    void on_pushButton_StopListen_clicked();

    void on_pushButton_ExitSystem_clicked();

    void on_pushButton_CleanMes_clicked();

    void on_pushButton_SendMsg_clicked();

private:
    Ui::FileTransferToolsDialog *ui;
};
#endif // FILETRANSFERTOOLSDIALOG_H
