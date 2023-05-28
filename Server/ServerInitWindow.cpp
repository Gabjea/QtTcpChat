#include "ServerInitWindow.h"

ServerInitWindow::ServerInitWindow(Server& server,QWidget *parent)
	: mainWindow{ server },QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.startServerButton, &QPushButton::clicked, this, &ServerInitWindow::onStartServer);
}

void ServerInitWindow::onStartServer()
{

	this->close();

}


ServerInitWindow::~ServerInitWindow()
{}

void ServerInitWindow::closeEvent(QCloseEvent * event)
{
	mainWindow.setPort(ui.portInput->text().toInt());
	mainWindow.show();
}
