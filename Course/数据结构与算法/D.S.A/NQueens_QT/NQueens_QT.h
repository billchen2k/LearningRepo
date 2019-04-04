#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_NQueens_QT.h"

class NQueens_QT : public QMainWindow
{
	Q_OBJECT

public:
	NQueens_QT(QWidget *parent = Q_NULLPTR);

private:
	Ui::NQueens_QTClass ui;
};
