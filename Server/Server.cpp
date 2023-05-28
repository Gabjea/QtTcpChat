#include "Server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.sendServerMessage, &QPushButton::clicked, this, &Server::onSendServerMessage);
    

}

void Server::onSendServerMessage()
{
    sendToAllClients("Server: "+ui.serverMessageInput->text());
    ui.serverMessageInput->clear();
}

void Server::readDataFromSocket()
{
    
    QTcpSocket* m_socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray messageFromSocket = m_socket->readAll();
    User* currentUser = getUser(m_socket);
    QString message = getUser(m_socket)->getName() + ": " + QString::fromStdString(messageFromSocket.toStdString());

    interpretMessage(message, currentUser);
    //sendToAllClients(message);
}


Server::~Server()
{
    if (server != nullptr)
        delete server;

    for (User* user : clientConnectionList)
        if(user != nullptr)
            delete user;
}

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



void Server::interpretMessage(QString message, User* user)
{
    QStringList splittedMessage = message.split(QRegularExpression("\\s+"));
    QString command =splittedMessage[1];
    QString data =splittedMessage[2];

    if (command == "/message")
    {
        sendToAllClients(splittedMessage[0]+splittedMessage[2]);
    }
    else if (command == "/changename")
    {
        user->setName(data);
        QString clientConnectedString = user->getName() + " has connected to the server.";

        ui.userList->addItem(user->getName());

        sendToClient("Welcome to the server", user->getSocket());
        sendToAllClientsExceptClient(clientConnectedString, user->getSocket());
    }
    
}

void Server::addNewClientConnection(QTcpSocket* socket)
{
    User* user = new User{ QString("alex"), socket };
    clientConnectionList.append(user);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readDataFromSocket()));
  
}

void Server::sendToClient(QString message, QTcpSocket* socket)
{
    socket->write(message.toStdString().c_str());
}

void Server::sendToAllClients(QString message)
{
    ui.messageList->addItem(message);
    for (User* user : clientConnectionList)
    {
        
        user->getSocket()->write(message.toStdString().c_str());
    }
}

void Server::sendToAllClientsExceptClient(QString message, QTcpSocket* exceptSocket)
{
    ui.messageList->addItem("Server: " + message);
    for (User* user : clientConnectionList)
    {
        if(user->getSocket()->socketDescriptor() != exceptSocket->socketDescriptor())
            user->getSocket()->write(message.toStdString().c_str());
    }
}

User* Server::getUser(QTcpSocket* socket)
{
    for (User* user : clientConnectionList)
    {
        if (user->getSocket() == socket)
            return user;
    }
    return nullptr;
}
