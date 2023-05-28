#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QMessageBox>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    void setPort(int _port) { port = _port; }


signals:
    
public slots:
    void newConnection();
    void onClicked();

protected:
    void showEvent(QShowEvent* event) override;

private:
    int port;
    Ui::ServerClass ui;
    QTcpServer* server;
    QList<QTcpSocket*> clientConnectionList;


    void addNewClientConnection(QTcpSocket* socket);
};
