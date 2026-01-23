#include "filetransfertoolsdialog.h"
#include "ui_filetransfertoolsdialog.h"
#include <QDebug>
#include<QPainter>
FileTransferToolsDialog::FileTransferToolsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileTransferToolsDialog)
{
    ui->setupUi(this);
    //qDebug()<<"Qt Version"<<qVersion();

    //调用GetLocalIpAddressFunc()函数返回IP地址,并且将IP地址添加到组合框控件
    QString strIp=GetLocalInAddressFunc();
    ui->comboBox_IP->addItem(strIp);
    qDebug()<<strIp;
    //QMessageBox::Critical(NULL,strIp,QMessageBox::Yes);

    //修改标签的颜色
    QPalette platestr1=ui->label_Server->palette();
    platestr1.setColor(QPalette::WindowText,Qt::yellow);//设置字体颜色
    ui->label_Server->setPalette(platestr1);
    ui->label_Port->setPalette(platestr1);
    ui->label_progressrate->setPalette(platestr1);
    ui->groupBox_ListMsg->setPalette(platestr1);
    ui->groupBox_SendMsg->setPalette(platestr1);
    //设置字体加粗  //这里加一个临时对象font,这样不会原本的其他字体产生影响,否则
    QFont font1=ui->label_Server->font();//相当新建一个对象然后对其复制然直接就能运用上
    font1.setBold(true);//设置字体加粗
    ui->label_Server->setFont(font1);
    ui->label_Port->setFont(font1);
    ui->label_progressrate->setFont(font1);
}

FileTransferToolsDialog::~FileTransferToolsDialog()
{
    delete ui;
}
//获取本地Ip地址/重绘事件处理(设置窗口背景)
QString FileTransferToolsDialog::GetLocalInAddressFunc()  //获取本机IP地址
{
    //通过主机名称获取网络信息
    QString hostName=QHostInfo::localHostName();
    QHostInfo hostInfo=QHostInfo::fromName(hostName);

    QString StrLocalIP="";

    //遍历所有网络地址,搜索IPv4地址
    QList<QHostAddress> addList=hostInfo.addresses();
    if(!addList.isEmpty())
    {
        for(int i =0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            if(aHost.protocol()==QAbstractSocket::IPv4Protocol)
            {
                StrLocalIP=aHost.toString();
                break;
            }
        }
    }
    return StrLocalIP;
}

//重绘窗口背景
void FileTransferToolsDialog::FileTransferToolsDialog::paintEvent(QPaintEvent *ev) //重绘事件处理(设置窗口背景)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/images/bgpng4.png"),QRect());

}



//TCP服务器相关槽函数
void FileTransferToolsDialog::OnNewConnectionFunc()//处理新连接请求(当有客户端连接时触发)
{
    //文本传输处理
    if(!P_TCPTextScoketObject ||P_TCPTextScoketObject->state()==QAbstractSocket::UnconnectedState)
    {
        //获取的客户端连接
        P_TCPTextScoketObject=P_TCPServerObject->nextPendingConnection();

        //连接文本相关槽函数
        //connect(P_TCPTextScoketObject,SIGNAL(connected()),this,SLOT(OnClientConnectedFunc()));
        connect(P_TCPTextScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientConnectedFunc);
        connect(P_TCPTextScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientDisconnectedFunc);
        connect(P_TCPTextScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnSocketReadyReadFunc);

    }

    //文件传输处理
    if(!P_TCPFileScoketObject ||P_TCPFileScoketObject->state()==QAbstractSocket::UnconnectedState)
    {
        //获取的客户端连接
        P_TCPFileScoketObject=P_TCPServerObject->nextPendingConnection();

        //连接文件相关槽函数
        connect(P_TCPFileScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientConnectedFunc);
        connect(P_TCPFileScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientDisconnectedFunc);

    }
}

//文本通道槽函数
void FileTransferToolsDialog::OnClientConnectedFunc()  //文本socket连接成功处理
{

}
void FileTransferToolsDialog::OnClientDisconnectedFunc()//文本socket断开连接处理
{

}
void FileTransferToolsDialog::OnSocketReadyReadFunc()//读取客户端发送的文本数据
{

}

//文件通道槽函数
void FileTransferToolsDialog::OnFileClientConnectedFunc()//文件socket连接成功处理
{

}
void FileTransferToolsDialog::OnFileClientDisconnectedFunc()//文件socket连接断开处理
{

}

//业务逻辑槽函数
void FileTransferToolsDialog::UpdateServerProgressFunc()//更新文件接收进度条状态
{

}
void FileTransferToolsDialog::DisplayErrorInfoFunc(QAbstractSocket::SocketError socketError)//显示socket错误
{

}


//窗口关闭事件处理(停止监听并释放资源)
void FileTransferToolsDialog::closeEvent(QCloseEvent *event)
{
    if(P_TCPServerObject->isListening())
    {
        P_TCPServerObject->close();
    }
    event->accept();
}


//_________________________________________
void FileTransferToolsDialog::on_pushButton_StartListen_clicked()
{

}

void FileTransferToolsDialog::on_pushButton_StopListen_clicked()
{

}

void FileTransferToolsDialog::on_pushButton_ExitSystem_clicked()
{
    this->close();
}

void FileTransferToolsDialog::on_pushButton_CleanMes_clicked()
{

}

void FileTransferToolsDialog::on_pushButton_SendMsg_clicked()
{

}
