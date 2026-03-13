/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_ConnectServer;
    QPushButton *pushButton_DisconnectServer;
    QPlainTextEdit *plainTextEdit_SendMsg;
    QGroupBox *groupBox;
    QComboBox *comboBox_ServerIP;
    QSpinBox *spinBox_ServerPort;
    QGroupBox *groupBox_2;
    QPlainTextEdit *plainTextEdit_MsgList;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_Exit;
    QPushButton *pushButton_ClearMsg;
    QPushButton *pushButton_SendMsg;
    QLabel *label_LocalIP;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_SendFile;
    QPushButton *pushButton_SelectFile;
    QProgressBar *progressBar;
    QLineEdit *lineEdit;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QString::fromUtf8("MainDialog"));
        MainDialog->resize(873, 611);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainDialog->setWindowIcon(icon);
        label = new QLabel(MainDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 131, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(MainDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(330, 20, 111, 31));
        label_2->setFont(font);
        pushButton_ConnectServer = new QPushButton(MainDialog);
        pushButton_ConnectServer->setObjectName(QString::fromUtf8("pushButton_ConnectServer"));
        pushButton_ConnectServer->setGeometry(QRect(580, 20, 131, 31));
        pushButton_ConnectServer->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/connect.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ConnectServer->setIcon(icon1);
        pushButton_DisconnectServer = new QPushButton(MainDialog);
        pushButton_DisconnectServer->setObjectName(QString::fromUtf8("pushButton_DisconnectServer"));
        pushButton_DisconnectServer->setGeometry(QRect(730, 20, 121, 31));
        pushButton_DisconnectServer->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/disconnect.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_DisconnectServer->setIcon(icon2);
        plainTextEdit_SendMsg = new QPlainTextEdit(MainDialog);
        plainTextEdit_SendMsg->setObjectName(QString::fromUtf8("plainTextEdit_SendMsg"));
        plainTextEdit_SendMsg->setGeometry(QRect(20, 320, 831, 121));
        plainTextEdit_SendMsg->setFont(font);
        groupBox = new QGroupBox(MainDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 851, 51));
        comboBox_ServerIP = new QComboBox(groupBox);
        comboBox_ServerIP->addItem(QString());
        comboBox_ServerIP->setObjectName(QString::fromUtf8("comboBox_ServerIP"));
        comboBox_ServerIP->setGeometry(QRect(140, 10, 171, 31));
        comboBox_ServerIP->setFont(font);
        comboBox_ServerIP->setEditable(true);
        spinBox_ServerPort = new QSpinBox(groupBox);
        spinBox_ServerPort->setObjectName(QString::fromUtf8("spinBox_ServerPort"));
        spinBox_ServerPort->setGeometry(QRect(440, 10, 111, 31));
        spinBox_ServerPort->setFont(font);
        spinBox_ServerPort->setMaximum(65535);
        spinBox_ServerPort->setValue(6657);
        groupBox_2 = new QGroupBox(MainDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 70, 851, 221));
        groupBox_2->setFont(font);
        plainTextEdit_MsgList = new QPlainTextEdit(groupBox_2);
        plainTextEdit_MsgList->setObjectName(QString::fromUtf8("plainTextEdit_MsgList"));
        plainTextEdit_MsgList->setGeometry(QRect(10, 20, 831, 191));
        plainTextEdit_MsgList->setFont(font);
        groupBox_3 = new QGroupBox(MainDialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 300, 851, 191));
        groupBox_3->setFont(font);
        pushButton_Exit = new QPushButton(groupBox_3);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(440, 150, 121, 31));
        pushButton_Exit->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Exit->setIcon(icon3);
        pushButton_ClearMsg = new QPushButton(groupBox_3);
        pushButton_ClearMsg->setObjectName(QString::fromUtf8("pushButton_ClearMsg"));
        pushButton_ClearMsg->setGeometry(QRect(580, 150, 121, 31));
        pushButton_ClearMsg->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/images/clear.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_ClearMsg->setIcon(icon4);
        pushButton_SendMsg = new QPushButton(groupBox_3);
        pushButton_SendMsg->setObjectName(QString::fromUtf8("pushButton_SendMsg"));
        pushButton_SendMsg->setGeometry(QRect(720, 150, 121, 31));
        pushButton_SendMsg->setFont(font);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/images/sendmsg.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_SendMsg->setIcon(icon5);
        label_LocalIP = new QLabel(groupBox_3);
        label_LocalIP->setObjectName(QString::fromUtf8("label_LocalIP"));
        label_LocalIP->setGeometry(QRect(10, 150, 421, 31));
        groupBox_4 = new QGroupBox(MainDialog);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 500, 851, 101));
        groupBox_4->setFont(font);
        pushButton_SendFile = new QPushButton(groupBox_4);
        pushButton_SendFile->setObjectName(QString::fromUtf8("pushButton_SendFile"));
        pushButton_SendFile->setGeometry(QRect(720, 20, 121, 31));
        pushButton_SendFile->setFont(font);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/images/sendfile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_SendFile->setIcon(icon6);
        pushButton_SelectFile = new QPushButton(groupBox_4);
        pushButton_SelectFile->setObjectName(QString::fromUtf8("pushButton_SelectFile"));
        pushButton_SelectFile->setGeometry(QRect(580, 20, 121, 31));
        pushButton_SelectFile->setFont(font);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/images/openfile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_SelectFile->setIcon(icon7);
        progressBar = new QProgressBar(groupBox_4);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(160, 60, 681, 31));
        progressBar->setFont(font);
        progressBar->setValue(0);
        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 60, 141, 31));
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        label->raise();
        label_2->raise();
        pushButton_ConnectServer->raise();
        pushButton_DisconnectServer->raise();
        plainTextEdit_SendMsg->raise();

        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "\345\256\242\346\210\267\347\253\257\344\270\216\346\234\215\345\212\241\345\231\250\346\236\266\346\236\204\347\263\273\347\273\237-TCP\345\256\242\346\210\267\347\253\257 Version 1.8", nullptr));
        label->setText(QApplication::translate("MainDialog", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200\357\274\232", nullptr));
        label_2->setText(QApplication::translate("MainDialog", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", nullptr));
        pushButton_ConnectServer->setText(QApplication::translate("MainDialog", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_DisconnectServer->setText(QApplication::translate("MainDialog", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox->setTitle(QString());
        comboBox_ServerIP->setItemText(0, QApplication::translate("MainDialog", "127.0.0.1", nullptr));

        groupBox_2->setTitle(QApplication::translate("MainDialog", "\346\266\210\346\201\257\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainDialog", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        pushButton_Exit->setText(QApplication::translate("MainDialog", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        pushButton_ClearMsg->setText(QApplication::translate("MainDialog", "\346\270\205\351\231\244\346\266\210\346\201\257", nullptr));
        pushButton_SendMsg->setText(QApplication::translate("MainDialog", "\345\217\221\351\200\201\346\266\210\346\201\257", nullptr));
        label_LocalIP->setText(QApplication::translate("MainDialog", "\346\234\254\346\234\272IP\345\234\260\345\235\200:", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainDialog", "\344\274\240\350\276\223\346\226\207\344\273\266\350\207\263\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_SendFile->setText(QApplication::translate("MainDialog", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        pushButton_SelectFile->setText(QApplication::translate("MainDialog", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        lineEdit->setText(QApplication::translate("MainDialog", "\344\274\240\350\276\223\346\226\207\344\273\266\350\277\233\345\272\246:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
