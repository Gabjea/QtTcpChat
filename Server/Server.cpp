#include "Server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    //connect(ui.pushButton, &QPushButton::clicked, this, &Server::onClicked);
    

}

void Server::onClicked()
{

}


Server::~Server()
{}

void Server::showEvent(QShowEvent * event)
{

    server = new QTcpServer();

    if (server->listen(QHostAddress::Any, port))
    {
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        QString initString = QString("Server has started succesfully on port %1").arg(QString::fromStdString(std::to_string(port)));
        QMessageBox::information(this, "Info",initString);
    }
    else
    {
        QMessageBox::warning(this, "Info", "Server could not be started!");
        this->close();
    }
}

void Server::newConnection()
{
    while (server->hasPendingConnections())
    {
        addNewClientConnection(server->nextPendingConnection());
    }
}

void Server::addNewClientConnection(QTcpSocket* socket)
{
    clientConnectionList.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readDataFromSocket()));
}
