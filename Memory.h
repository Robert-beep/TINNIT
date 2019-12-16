
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Memory.h"
#include "MyButton.h"
#include <QPushButton>
#include <QLabel>
#include <stdlib.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QScreen>
#include <QMediaPlayer>

using namespace std;

template<class T> std::string toString(const T& t)
{
	std::ostringstream stream;
	stream << t;
	return stream.str();
}

#define N 3 //Spielfeldgröße N x N
#define BUTTON_BREITE 200
#define BUTTON_HOEHE 200

#define POS_LABEL_X (N+1)*BUTTON_BREITE 
#define POS_LABEL_Y 10
//enum Spielmodus;


class Memory : public QMainWindow
{
	Q_OBJECT

public:
	Memory(QWidget* parent = Q_NULLPTR);


private:
	Ui::MemoryClass ui;

private:
	//QPushButton *myButton;
	MyButton* playCards[N][N]; // Array für die Widgets
	QLabel* spielzugLabel;
	QLabel* test;
	QLabel* debugLabel;
	

	int counter = 0;


	//--- Funktionen der Klasse
	bool checkGameOver();
	void toggleButton(int, int);
	bool samecard(ownerTyp, ownerTyp);
	void connectcard();
	void initPixmap(int r, int s);
	void initList();
	void turnToBack(int reihe, int spalte);
	void pointToPlayer();
	bool compare(int, int);
	int cards[(2*(N * N+1)/2)];
	QString filename[20];
	QPixmap listeIcon[(N * N + 1) / 2];
	bool thefirst = false;
	int thisOne;
	int firstOne;
	int firstCard_r;
	int firstCard_s;
	//void setSound();
	QMediaPlayer* positive_sound;
	//QMediaPlayer* negative_sound;
	

private slots:
	// Beschreibt, was beim Clicken passiert
	void myButtonClicked();

};

