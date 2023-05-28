#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QMessageBox>
#include <QScopedPointer>
#include "User.h"

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    void setPort(int _port) { port = _port; }


signals:
    
private slots:
    void newConnection();
    void onSendServerMessage();
    void readDataFromSocket();
protected:
    void showEvent(QShowEvent* event) override;
    

private:
    int port =-1;
    Ui::ServerClass ui;
    QTcpServer* server;
    QList<User *> clientConnectionList;

    void interpretMessage(QString message, User* user);
    void addNewClientConnection(QTcpSocket* socket);
    void sendToClient(QString message, QTcpSocket* socket);
    void sendToAllClients(QString message);
    void sendToAllClientsExceptClient(QString message, QTcpSocket* socket);
    User* getUser(QTcpSocket* socket);
};
