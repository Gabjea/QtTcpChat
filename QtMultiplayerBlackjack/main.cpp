#include "QtMultiplayerBlackjack.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMultiplayerBlackjack w;
    w.show();
    return a.exec();
}
