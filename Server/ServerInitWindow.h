#pragma once

#include <QMainWindow>
#include "ui_ServerInitWindow.h"
#include <QMessageBox>
#include "Server.h"
#include <QCloseEvent>
class ServerInitWindow : public QMainWindow
{
	Q_OBJECT

public:
	ServerInitWindow(Server& server,QWidget *parent = nullptr);
	~ServerInitWindow();


signals:

public slots:
	void onStartServer();

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	
	Ui::ServerInitWindowClass ui;
	Server& mainWindow;
};
