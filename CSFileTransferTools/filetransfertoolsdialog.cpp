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

    //固定窗口大小
    setFixedSize(this->width(),this->height());

    //测试qt版本
    qDebug()<<"Qt version:"<<qVersion();

    //初始化文件传输相关变量




    //调用GetLocalIpAddressFunc()函数返回IP地址,并且将IP地址添加到组合框控件
    QString strIp=GetLocalInAddressFunc();
    ui->comboBox_IP->addItem(strIp);
    //qDebug()<<strIp;
    //QMessageBox::Critical(NULL,strIp,QMessageBox::Yes);

    //修改标签的颜色
    QPalette platestr1=ui->label_Server->palette();
    platestr1.setColor(QPalette::WindowText,Qt::yellow);//设置字体颜色
    ui->label_Server->setPalette(platestr1);
    ui->label_Port->setPalette(platestr1);
    ui->label_progressrate ->setPalette(platestr1);
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
    //qDebug() << "hostInfo:"<< hostInfo;

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
                //qDebug()<<"StrLocalIP="<<StrLocalIP;
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
    //文本传输通道处理
    if(!P_TCPTextScoketObject ||P_TCPTextScoketObject->state()==QAbstractSocket::UnconnectedState)
    {
        //获取的客户端连接
        P_TCPTextScoketObject=P_TCPServerObject->nextPendingConnection();

        //连接文本相关槽函数
        //connect(P_TCPTextScoketObject,SIGNAL(connected()),this,SLOT(OnClientConnectedFunc()));
        //connect(P_TCPTextScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientConnectedFunc);
        connect(P_TCPTextScoketObject,&QTcpSocket::disconnected,this,&FileTransferToolsDialog::OnClientDisconnectedFunc);
        connect(P_TCPTextScoketObject,&QTcpSocket::readyRead,this,&FileTransferToolsDialog::OnSocketReadyReadFunc);

        return;//如果是文本通道，处理完就直接退出函数
        //不会执行文件通道那段代码

    }

    //文件传输处理
    if(!P_TCPFileScoketObject ||P_TCPFileScoketObject->state()==QAbstractSocket::UnconnectedState)
    {
        //获取的客户端连接
        P_TCPFileScoketObject=P_TCPServerObject->nextPendingConnection();

        //连接文件相关槽函数
        connect(P_TCPFileScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientConnectedFunc);
        connect(P_TCPFileScoketObject,&QTcpSocket::disconnected,this,&FileTransferToolsDialog::OnClientDisconnectedFunc);
        connect(P_TCPFileScoketObject,&QTcpSocket::readyRead,this,&FileTransferToolsDialog::OnSocketReadyReadFunc);
        //connect(P_TCPFileScoketObject,&QTcpSocket::errorOccurred,this,&FileTransferToolsDialog::DisplayErrorInfoFunc);  5.15版之后的写法
        connect(P_TCPFileScoketObject,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayErrorInfoFunc()));
    }
    ui->plainTextEdit_ListMsg->appendPlainText("\n[******有客户端连接*******");
}

//文本通道槽函数
//void FileTransferToolsDialog::OnClientConnectedFunc()  //文本socket连接成功处理
//{   暂时留着

//}
void FileTransferToolsDialog::OnClientDisconnectedFunc()//文本socket断开连接处理
{
    ui->plainTextEdit_ListMsg->appendPlainText("\n[*******客户端已断开和服务器连接*******");
    P_TCPTextScoketObject->close();
}
void FileTransferToolsDialog::OnSocketReadyReadFunc()//读取客户端发送的文本数据
{
    //获取当前时间戳
    QDateTime curretDateTime=QDateTime::currentDateTime();//获取当前系统时间
    QString strtemp=curretDateTime.toString("yyyy/MM/dd hh:mm:ss");

    //读取并显示客户端消息
    while (P_TCPTextScoketObject->canReadLine()) //检查是否有完整的行数据可读
    {
        ui->plainTextEdit_ListMsg->appendPlainText("[客服端消息 "+strtemp+"]:"+P_TCPTextScoketObject->readLine());
    }
}

//文件通道槽函数
void FileTransferToolsDialog::OnFileClientConnectedFunc()//文件socket连接成功处理
{
 ui->plainTextEdit_ListMsg->appendPlainText("******文件传输通道已连接**********");
}
void FileTransferToolsDialog::OnFileClientDisconnectedFunc()//文件socket连接断开处理
{
      ui->plainTextEdit_ListMsg->appendPlainText("*********文件传输连接已与服务器断开连接***********");
      P_TCPFileScoketObject->close();
}

//业务逻辑槽函数
void FileTransferToolsDialog::UpdateServerProgressFunc()//更新文件接收进度条状态
{   //获取当前系统试讲
    QString strtemp =QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    QDataStream in(P_TCPFileScoketObject);

    //第一阶段 接受文件头信息
    if(m_FileBytesReceived<=sizeof(qint64)*2);
    {
        //接收文件总大小和文件名长度
        if((P_TCPFileScoketObject->bytesAvailable()>=sizeof(qint64)*2)&& (m_FileNameSizes==0))
        {
            in>>m_FileTotalBytes>>m_FileNameSizes;
            m_FileBytesReceived += sizeof(qint64)*2;
        }
    }
    //接收文件名
    if((P_TCPFileScoketObject->bytesAvailable() >=m_FileNameSizes) &&(m_FileNameSizes !=0))
    {
        in>>m_FileNames;
        ui->plainTextEdit_ListMsg->appendPlainText(tr("[%1 开始接受文件 %2  ...]").arg(strtemp).arg(m_FileNames));
        m_FileBytesReceived += m_FileNameSizes;

        //创建本地文件,路径是程序目录+文件名称
        m_LocalFiles = new QFile(QApplication::applicationDirPath()+ "\\" +m_FileNames);

        if(!m_LocalFiles->open(QFile::WriteOnly))
        {
            qDebug()<<"文件打开失败,请重新检查?";
            delete m_LocalFiles;
            m_LocalFiles=nullptr;
            return;

        }
    }
    else{
        return;
    }

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
   // event->accept();
    QWidget::closeEvent(event);//调用父类
}


//_________________________________________

//开始监听
void FileTransferToolsDialog::on_pushButton_StartListen_clicked()
{
 //获取Ip和端口
    QString strIp=ui->comboBox_IP->currentText();
    quint16 port=ui->spinBox_Port->value();

    //启动服务器开始监听
    if(P_TCPServerObject->listen(QHostAddress(strIp),port)){
        ui->plainTextEdit_ListMsg->appendPlainText("[服务器开始监听]");
        ui->plainTextEdit_ListMsg->appendPlainText("[Ip地址:"+strIp+"][端口:"+QString::number(port)+"]");

       //更新按扭状态
        ui->pushButton_StartListen->setEnabled(false);
        ui->pushButton_StopListen->setEnabled(true);
        ui->pushButton_SendMsg->setEnabled(true);
    }
}

//停止监听
void FileTransferToolsDialog::on_pushButton_StopListen_clicked()
{
    //判断是否处于监听状态
    if(P_TCPServerObject->isListening()){
        P_TCPServerObject->close();
        ui->plainTextEdit_ListMsg->appendPlainText("[服务器已停止监听");
    }

    //更新按扭状态
    ui->pushButton_StopListen->setEnabled(false);
    ui->pushButton_SendMsg->setEnabled(false);
    ui->pushButton_StartListen->setEnabled(true);
}

//关闭窗口
void FileTransferToolsDialog::on_pushButton_ExitSystem_clicked()
{
    this->close();
}

//点击"清除消息"命令按扭
void FileTransferToolsDialog::on_pushButton_ClearMsg_clicked()
{
    ui->plainTextEdit_ListMsg->clear();
}

//发送信息
void FileTransferToolsDialog::on_pushButton_SendMsg_clicked()
{
    //获取plainTextEdit控件中的文本信息,并且验证
    QString strMsg=ui->plainTextEdit_EditMsg->toPlainText().trimmed();
    if(strMsg.isEmpty())
    {
        QMessageBox::critical(this,"错误","系统提示:消息不能为空?");
        return;
    }
//生成时间戳
    QString strtemp=QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

    //显示消息并发送给客户端
    ui->plainTextEdit_ListMsg->appendPlainText("[服务器消息 "+strtemp+"]"+strMsg);
    P_TCPTextScoketObject->write((strMsg+"\n").toUtf8());
    ui->plainTextEdit_EditMsg->clear();
}
