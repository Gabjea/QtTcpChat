#pragma once

#include <QObject>
#include <QTcpSocket>
class User  : public QObject
{
	Q_OBJECT

private:
	QString name;
	QTcpSocket* socket;

public:
	User(QString name, QTcpSocket* socket,QObject *parent= nullptr);
	~User();
	QString getName() { return name; }
	void setName(QString _name) { name = _name; }
	QTcpSocket* getSocket() { return socket; }
};
