#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMultiplayerBlackjack.h"

class QtMultiplayerBlackjack : public QMainWindow
{
    Q_OBJECT

public:
    QtMultiplayerBlackjack(QWidget *parent = nullptr);
    ~QtMultiplayerBlackjack();

private:
    Ui::QtMultiplayerBlackjackClass ui;
};
