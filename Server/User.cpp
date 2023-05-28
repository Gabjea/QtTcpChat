#include "User.h"

User::User(QString name, QTcpSocket* socket, QObject* parent)
	: name{ name }, socket{ socket },QObject(parent)
{}

User::~User()
{}
