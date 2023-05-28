#include "Server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.sendServerMessage, &QPushButton::clicked, this, &Server::onSendServerMessage);
    

}

void Server::onSendServerMessage()
{
    sendToAllClients(ui.serverMessageInput->text());
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
    QString clientConnectedString = "Clinet: " + QString::number(socket->socketDescriptor()) + " has connected to the server.";
    
    ui.userList->addItem(QString::number(socket->socketDescriptor()));
    
    sendToClient("Welcome to the server",socket);
    sendToAllClientsExceptClient(clientConnectedString,socket);
}

void Server::sendToClient(QString message, QTcpSocket* socket)
{
    socket->write(message.toStdString().c_str());
}

void Server::sendToAllClients(QString message)
{
    ui.messageList->addItem("Server: "+ message);
    for (QTcpSocket* socket : clientConnectionList)
    {
        socket->write(message.toStdString().c_str());
    }
}

void Server::sendToAllClientsExceptClient(QString message, QTcpSocket* exceptSocket)
{
    ui.messageList->addItem("Server: " + message);
    for (QTcpSocket* socket : clientConnectionList)
    {
        if(socket->socketDescriptor() != exceptSocket->socketDescriptor())
            socket->write(message.toStdString().c_str());
    }
}
