#include "maindialog.h"
#include "ui_maindialog.h"
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    //qDebug() << "构造函数：开始";

        //qDebug() << "构造函数：准备 setupUi";
    ui->setupUi(this);
    
    //qDebug() << "构造函数：setupUi 完成";

       //qDebug() << "构造函数：固定窗口大小";
    //固定窗口宽度和高度
    setFixedSize(width(),height());//固定尺寸是以用户为准
    
    //qDebug() << "构造函数：窗口大小固定完成";

       //qDebug() << "构造函数：初始化变量";
    m_TotalBytes=0;//文件总大小(字节)
    m_BytesWrites=0;//已写入/发送的字节数
    m_BytesToWrite=0;//待写入/待发送的字节数
    m_LoadSizes= 4*1024;//每次发送的数据块大小 =4kb

    //qDebug() << "构造函数：变量初始化完成";

    //qDebug() << "构造函数：创建 Socket";
    m_TcpMsgClient=new QTcpSocket(this);  //处理聊天消息Socket
    m_TcpFileClient= new QTcpSocket(this);//处理文件传输消息socket
    //qDebug() << "构造函数：Socket 创建完成";
    // qDebug() << "构造函数：获取本地 IP";
    //获取本地ip地址
    QString strLocalIPs=GetLocalIPAddress();
    //qDebug() << "构造函数：获取到 IP:" << strLocalIPs;
    //qDebug() << "构造函数：设置 UI 控件";
    QString strIp =("本机ip地址" + strLocalIPs);
    ui->label_LocalIP->setText(strIp);
    qDebug()<<"IP:"<<strIp;

    //将返回的ip地址显示到Combo box组合框控件里面来
    ui->comboBox_ServerIP->addItem(strLocalIPs);

    //qDebug() << "构造函数：UI 控件设置完成";
     //qDebug() << "构造函数：设置按钮状态";
    //将返回的ip地址显示到Combo box 组合框控件里面
    ui->comboBox_ServerIP->addItem(strLocalIPs);

    //举例命令按钮切换实现
    ui->pushButton_DisconnectServer->setEnabled(false);
    ui->pushButton_SendFile->setEnabled(false);
    //qDebug() << "构造函数：按钮状态设置完成";

        //qDebug() << "构造函数：全部完成";

    //聊天信息,槽函数连接
    connect(m_TcpMsgClient,&QTcpSocket::connected,this,&MainDialog::OnConnectedFunc);
    connect(m_TcpMsgClient,&QTcpSocket::disconnected,this,&MainDialog::OnDisconnectedFunc);
    connect(m_TcpMsgClient,&QTcpSocket::readyRead,this,&MainDialog::OnSocketReadyReadFunc);

    //禁止消息列表控件,修改里面的数据信息,设置为只读
    ui->plainTextEdit_MsgList->setReadOnly(true);

    //当有数据发送成功的时,更新进度条状态
    connect(m_TcpFileClient,&QTcpSocket::bytesWritten,this,&MainDialog::UpdateClientProgressFunc);

}

MainDialog::~MainDialog()
{
    delete ui;
}
void MainDialog::paintEvent(QPaintEvent *event)//实现更改窗口背景
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/new/prefix1/images/bgpng.png"),QRect());
}
QString MainDialog::GetLocalIPAddress()//获取本机的Ip地址
{
    //获取本机ip地址
    QString strHostName =QHostInfo::localHostName();//获取本地主机名称
    QHostInfo HostInfos=QHostInfo::fromName(strHostName);//通过主机名称获取ip地址

    QString strLocalIP;
    //
    QList<QHostAddress> addressList = HostInfos.addresses();

    //遍历所有ip地址找出第一个非回环的Ipv4地址
    for(int i=0;i<addressList.count();++i)
    {
        QHostAddress address = addressList.at(i);
        //判断是否为Ipv4地址且不是本地回环(127.0.0.1)
        if(address.protocol()==QAbstractSocket::IPv4Protocol && address !=QHostAddress::LocalHost)
        {
            strLocalIP = address.toString();
                        break;  // 找到后退出循环
        }
    }
    // 如果没有找到有效的IPv4地址，则使用本地回环地址
    if (strLocalIP.isEmpty())
    {
        strLocalIP = QHostAddress(QHostAddress::LocalHost).toString();
    }

    return strLocalIP;
//    if(!addressList.isEmpty())
//    {
//        for(int i= 0;i<addressList.count();i++)
//        {
//            QHostAddress sHost=addressList.at(i);
//        }
//        //判断本机ip地址是否为ipv4
//        if(QAbstractSocket::IPv4Protocol==sHost.protocal())
//        {
//            StrLocalIP=strHost.toString();
//            break;
//        }
//    }
//    return StrLocalIP;
}

void MainDialog::closeEvent(QCloseEvent *event)//关闭事件
{
    if(m_TcpMsgClient->state()==QAbstractSocket::ConnectedState)
        m_TcpMsgClient->disconnectFromHost();
    if(m_TcpFileClient->state()==QAbstractSocket::ConnectedState)
        m_TcpFileClient->disconnectFromHost();
    event->accept();
}

void MainDialog::OnConnectedFunc()//客户端连接服务器
{
    //connected信号槽函数
    ui->plainTextEdit_MsgList->appendPlainText("[*******客服端与服务器连接成功*******]");
    ui->plainTextEdit_MsgList->appendPlainText("IP Address :" +m_TcpMsgClient->peerAddress().toString()+"]"
                                               +"[Port: " +QString::number(m_TcpMsgClient->peerPort())+"]");
    ui->pushButton_ConnectServer->setEnabled(false);//连接服务器按扭禁止
    ui->pushButton_DisconnectServer->setEnabled(true);//断开服务器可以使用


}
void MainDialog::OnDisconnectedFunc()//客户端与服务器断开
{
    //disconnected信号槽函数
    ui->plainTextEdit_MsgList->appendPlainText("[客户端与服务器断开连接]\n");

    ui->pushButton_ConnectServer->setEnabled(true);//
    ui->pushButton_DisconnectServer->setEnabled(false);

}
void MainDialog::OnSocketReadyReadFunc()//读取服务器socket传输的数据信息
{
    //日期时间
    QDateTime CurrentDataTime=QDateTime::currentDateTime();
    QString strYear=QString::number(CurrentDataTime.date().year());
    QString strMonth=QString::number(CurrentDataTime.date().month());
    QString strDay=QString::number(CurrentDataTime.date().day());
    QString strHour=QString::number(CurrentDataTime.time().hour());
    QString strMinute=QString::number(CurrentDataTime.time().minute());
    QString strSecond=QString::number(CurrentDataTime.time().second());

   // 将年月日时分秒6个字符串连接
    QString strDateTimes=strYear+"/"+strMonth+"/"+strDay+" "+strHour+":"+strMinute+":"+strSecond;
    while (m_TcpMsgClient->canReadLine()) {
        ui->plainTextEdit_MsgList->appendPlainText("[服务器消息:"+m_TcpMsgClient->readLine()+"]");
    }
}
void MainDialog::StartTransferFunc()//传输文件信息
{

}

//文件传输过程中,进度条变化装填显示
void MainDialog::UpdateClientProgressFunc(qint64 numBytes) // 文件传输及显示进度条更新
{
    // 日期时间处理操作
        QDateTime CurrentDataTime=QDateTime::currentDateTime();
        QString strYear=QString::number(CurrentDataTime.date().year());
        QString strMonth=QString::number(CurrentDataTime.date().month());
        QString strDay=QString::number(CurrentDataTime.date().day());
        QString strHour=QString::number(CurrentDataTime.time().hour());
        QString strMinute=QString::number(CurrentDataTime.time().minute());
        QString strSecond=QString::number(CurrentDataTime.time().second());

        // 将年月日时分秒6个字符串连接
        QString strDateTimes=strYear+"/"+strMonth+"/"+strDay+" "+strHour+":"+strMinute+":"+strSecond;

        //确认已发送的数据信息
        m_BytesWrites=m_BytesWrites+(int)numBytes;

        if(m_BytesWrites>0)
        {

        }
}
void MainDialog::DisplayErrorFunc(QAbstractSocket::SocketError) // 异常处理信息
{



}

//连接服务器命令按扭,代码实现
void MainDialog::on_pushButton_ConnectServer_clicked()
{
    //首先获取ip地址和端口
    QString ipaddress=ui->comboBox_ServerIP->currentText();
    quint16 port=ui->spinBox_ServerPort->value();

    //连接服务器
    m_TcpMsgClient->connectToHost(ipaddress,port);
}


void MainDialog::on_pushButton_DisconnectServer_clicked()
{
    //断开服务器
    if(m_TcpMsgClient->state()==QAbstractSocket::ConnectedState)
    {
        m_TcpMsgClient->disconnectFromHost();
    }
}

void MainDialog::on_pushButton_Exit_clicked()
{
    //退出系统,关闭套接字
    m_TcpMsgClient->close();
    m_TcpFileClient->close();
    this->close();
}

void MainDialog::on_pushButton_ClearMsg_clicked()
{
    ui->plainTextEdit_MsgList->clear();
}

void MainDialog::on_pushButton_SendMsg_clicked()
{
    // 日期时间处理操作
        QDateTime CurrentDataTime=QDateTime::currentDateTime();
        QString strYear=QString::number(CurrentDataTime.date().year());
        QString strMonth=QString::number(CurrentDataTime.date().month());
        QString strDay=QString::number(CurrentDataTime.date().day());
        QString strHour=QString::number(CurrentDataTime.time().hour());
        QString strMinute=QString::number(CurrentDataTime.time().minute());
        QString strSecond=QString::number(CurrentDataTime.time().second());

        // 将年月日时分秒6个字符串连接
        QString strDateTimes=strYear+"/"+strMonth+"/"+strDay+" "+strHour+":"+strMinute+":"+strSecond;

    //获取多行编辑器控件,用户所输入的信息
        QString strMsg=ui->plainTextEdit_SendMsg->toPlainText();

        //判断发送出去的信息是否为空
        if(strMsg.isEmpty())
        {
            QMessageBox::critical(this,"错误","发送到服务器的数据信息不能为空,请重新检查?",QMessageBox::Yes);
            ui->plainTextEdit_SendMsg->setFocus(); // 将光标焦点定位到用户输入控件
            return;
        }

        //将用户发送的数据信息显示到消息列表队列,<plainTextEdit_MsgList对象控件
        ui->plainTextEdit_MsgList->appendPlainText("[客服端消息"+strDateTimes+"]:"+strMsg);
        ui->plainTextEdit_SendMsg->clear();
        ui->plainTextEdit_SendMsg->setFocus();

        //QByteArray用于处理字节数字的类,可以存储和访问二进制数据,图像,音频等
        QByteArray bytearray=strMsg.toUtf8();
        bytearray.append('\n');

        //将数据信息发送至服务器
        m_TcpMsgClient->write(bytearray);
}
void MainDialog::on_pushButton_SelectFile_clicked()
{

}

void MainDialog::on_pushButton_SendFile_clicked()
{

}

