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


    // 创建 QTcpServer 对象
   // P_TCPServerObject = new QTcpServer(this);  // this 作为父对象，自动管理内存qDebug()<<"Qt version:"<<qVersion();

    //初始化文件传输相关变量
    m_FileTotalBytes=0;         // 文件总大小
       m_FileBytesReceived=0;      // 已经接收字节数
       m_FileNameSizes=0;         // 文件名长度

       // 创建TCP服务器对象
         P_TCPServerObject=new QTcpServer(this);
         // 关联槽函数
         connect(P_TCPServerObject,SIGNAL(newConnection()),this,SLOT(OnNewConnectionFunc()));
        // connect(P_TCPServerObject,&QTcpServer::newConnection,this,&OnNewConnectionFunc);
         // 创建两个TCP套接字分别处理文本和文件传输
         P_TCPTextScoketObject=new QTcpSocket(this); // 文本通信套接字
         P_TCPFileScoketObject=new QTcpSocket(this); // 文件通信套接字




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
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "    color: yellow;"  // 设置文字为黄色
        "}"
    );
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
        connect(P_TCPFileScoketObject,SIGNAL(connected()),this,SLOT(OnFileClientConnectedFunc()));
        //connect(P_TCPFileScoketObject,&QTcpSocket::connected,this,&FileTransferToolsDialog::OnClientConnectedFunc);
        connect(P_TCPFileScoketObject,&QTcpSocket::disconnected,this,&FileTransferToolsDialog::OnClientDisconnectedFunc);
        connect(P_TCPFileScoketObject,&QTcpSocket::readyRead,this,&FileTransferToolsDialog::UpdateServerProgressFunc);
        //connect(P_TCPFileScoketObject,&QTcpSocket::errorOccurred,this,&FileTransferToolsDialog::DisplayErrorInfoFunc);  5.15版之后的写法
        //connect(P_TCPFileScoketObject,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayErrorInfoFunc()));
        connect(P_TCPFileScoketObject,
                static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),
                this,
                &FileTransferToolsDialog::DisplayErrorInfoFunc);
        ui->plainTextEdit_ListMsg->appendPlainText("[文件传输通道已连接]");
    }
    ui->plainTextEdit_ListMsg->appendPlainText("\n[******有客户端连接*******");

}

//文本通道槽函数
//void FileTransferToolsDialog::OnClientConnectedFunc()  //文本socket连接成功处理
//{  

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
       ui->plainTextEdit_ListMsg->appendPlainText("[客户端消息 "+strtemp+"]:"+P_TCPTextScoketObject->readLine());
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
{   //获取当前时间戳
    QString strtemp =QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    //创建数据流对象(关联到socket)
    QDataStream in(P_TCPFileScoketObject);//in 现在可以从socket读取数据

    //第一阶段 接受文件头信息
    // 第一阶段判断：m_FileBytesReceived(0) <= 16 ? 是的，还在第一阶段
    if(m_FileBytesReceived<=sizeof(qint64)*2)   //sizeof(qint64)*2 = 16
    {
        //接收文件总大小和文件名长度
        // 第一个if：接收文件总大小和文件名长度
                // bytesAvailable() = 16，有足够数据
                // m_FileNameSizes == 0，还没接收文件名长度信息
        if((P_TCPFileScoketObject->bytesAvailable()>=sizeof(qint64)*2)&& (m_FileNameSizes==0))
        {
            in>>m_FileTotalBytes>>m_FileNameSizes;
            qDebug()<<"文件总大小:"<<m_FileTotalBytes<<"文件名长度:"<<m_FileNameSizes;
            m_FileBytesReceived += sizeof(qint64)*2;
        }

    //接收文件名
    if((P_TCPFileScoketObject->bytesAvailable() >=m_FileNameSizes) &&(m_FileNameSizes !=0))
    {
        // 读取文件名
       // in>>m_FileNames;
        // 直接读取原始字节（假设文件名是UTF-8编码）
           QByteArray fileNameData = P_TCPFileScoketObject->read(m_FileNameSizes);
           m_FileNames = QString::fromUtf8(fileNameData);
           qDebug()<<"接收到的文件名:"<<m_FileNames;



        // 显示日志
        ui->plainTextEdit_ListMsg->appendPlainText(tr("[%1 开始接收文件 %2  ...]").arg(strtemp).arg(m_FileNames));
        // 更新已接收字节数

        //更新已接收到的字节数(16字节数+文件名长度)
        m_FileBytesReceived =sizeof(qint64)*2 +m_FileNameSizes;
        //m_FileBytesReceived += m_FileNameSizes;

        //创建本地文件,路径是程序目录+文件名称
        m_LocalFiles = new QFile(QApplication::applicationDirPath()+ "/" +m_FileNames);

        QString filePath = QApplication::applicationDirPath() + "/" + m_FileNames;
        qDebug() << "尝试打开文件:" << filePath;

        if(!m_LocalFiles->open(QFile::WriteOnly))
        {
            qDebug()<<"文件打开失败,请重新检查?";
            delete m_LocalFiles;
            m_LocalFiles=nullptr;
            // 重置状态变量，防止后续 readyRead 误操作
               m_FileTotalBytes = 0;
               m_FileBytesReceived = 0;
               m_FileNameSizes = 0;
               m_FileNames.clear();
            return;

        }
    }
    else{
        return;
    }

    }
    //第二阶段:接受文件内容
    if(m_FileBytesReceived<m_FileTotalBytes)// 如果还没收完
    {

        //读取所有可用的数据(可能一次性读取多个数据包)
        m_InBlaocks=P_TCPFileScoketObject->readAll();

        //将数据写入本地文件
        m_LocalFiles->write(m_InBlaocks);
        //更新已经接收字节数
        m_FileBytesReceived +=m_InBlaocks.size();
        m_InBlaocks.clear();//清空临时数据块
        //更新接受文件进程效果
        ui->progressBar->setMaximum(m_FileTotalBytes);
        ui->progressBar->setValue(m_FileBytesReceived);

    }

    //第三阶段 :传输完成处理
    if(m_FileBytesReceived==m_FileTotalBytes)
    {
        m_LocalFiles->close();

        //记录传输成功日志
        ui->plainTextEdit_ListMsg->appendPlainText(QString("[%1 文件 %2 接受成功").arg(strtemp).arg(m_FileNames));

        //重置状态变量,准备下一次传输
        m_FileTotalBytes=0;
        m_FileBytesReceived=0;
        m_FileNameSizes=0;
        delete m_LocalFiles;
        m_LocalFiles=nullptr;

    }

}

void FileTransferToolsDialog::DisplayErrorInfoFunc(QAbstractSocket::SocketError socketError)//显示socket错误信息
{
    //文件传输过程中出现错误,关闭套接字,传输进度条重设
    P_TCPServerObject->close();
    ui->progressBar->reset();
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
    // 先检查指针是否有效
    if(!P_TCPServerObject) {
        ui->plainTextEdit_ListMsg->appendPlainText("[错误: 服务器对象未初始化]");
        return;
    }
 //获取Ip和端口
    QString strIp=ui->comboBox_IP->currentText();
    quint16 port=ui->spinBox_Port->value();

    //验证IP地址
    QHostAddress address(strIp);
    if(address.isNull()) {
        ui->plainTextEdit_ListMsg->appendPlainText("[错误: 无效的IP地址: " + strIp + "]");
        return;
    }

    //启动服务器开始监听
    if(P_TCPServerObject->listen(QHostAddress(strIp),port)){
        ui->plainTextEdit_ListMsg->appendPlainText("[服务器开始监听]");
        ui->plainTextEdit_ListMsg->appendPlainText("[IP地址:"+strIp+"][端口:"+QString::number(port)+"]");

       //更新按扭状态
        ui->pushButton_StartListen->setEnabled(false);
        ui->pushButton_StopListen->setEnabled(true);
        ui->pushButton_SendMsg->setEnabled(true);
    }else{
        //添加错误信息
        ui->plainTextEdit_ListMsg->appendPlainText("[监听失败: +" + P_TCPServerObject->errorString()+"]");
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

