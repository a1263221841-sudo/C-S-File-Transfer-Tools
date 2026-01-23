#include "filetransfertoolsdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileTransferToolsDialog w;
    w.show();
    return a.exec();
}
