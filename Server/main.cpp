#include "ServerInitWindow.h"
#include "Server.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server mainWindow;
    ServerInitWindow initWindow{ mainWindow };
    initWindow.show();
    
  
    return a.exec();
}
