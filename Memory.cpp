#include "Memory.h"
#include "Player.h"

//das Label kann beliebig eingefügt werden um zu überprüfen ob ein Schritt funktioniert
		/*test = new QLabel(this);
		test->setText("funktioniert");
		test->setGeometry(POS_LABEL_X, 30, 160, 50);

		QFont labelFont1;
		labelFont1.setPixelSize(14);
		test->setFont(labelFont1);*/

Memory::Memory(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this); //immer zuerst

	QScreen* screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	int height = 0.6*screenGeometry.height();
	int width = 0.8*screenGeometry.width();

	this->setGeometry(40, 40, width, height);
	//this->setGeometry(40, 40, ((N + 2) * BUTTON_BREITE), (N * BUTTON_HOEHE));
	//Zufallszahl: Zeit auf Systemzeit setzen
	srand(time(NULL));
	int zahl1 = ((rand() % 10));
	cout << zahl1 << endl;

	initList();
	/*setSound();*/
	

	QMediaPlayer* negative_sound = new QMediaPlayer;
	negative_sound->setMedia(QUrl::fromLocalFile("wrong.swf.wav"));
	negative_sound->setVolume(50);
	
	//Player erstellen
	//Player *player1 = new Player;

	// Die Memory-Karten erstellen 
	QPixmap whs_logo("WH_Logo200.jpg");
	QIcon ButtonIcon(whs_logo);

	int s_offset = 0;
	for (int reihe = 0; reihe < N; reihe++) {
		s_offset = (N - 1) * reihe;
		for (int spalte = 0; spalte < N; spalte++)
		{
			playCards[reihe][spalte] = new MyButton(reihe, spalte, this); //Instanzierung			
			// set size and location of the button
			playCards[reihe][spalte]->setGeometry((QRect(QPoint(BUTTON_BREITE * reihe, BUTTON_HOEHE * spalte), QSize(BUTTON_BREITE, BUTTON_HOEHE))));  //x,y,w,h
			playCards[reihe][spalte]->resize(BUTTON_BREITE, BUTTON_HOEHE); //Größe setzen
			playCards[reihe][spalte]->move(BUTTON_BREITE * spalte, BUTTON_HOEHE * reihe); //platzieren
			//WHSLogo auf Button platzieren
			playCards[reihe][spalte]->setIcon(ButtonIcon);
			playCards[reihe][spalte]->setIconSize(whs_logo.rect().size());
			playCards[reihe][spalte]->setFixedSize(whs_logo.rect().size());

			int sum = spalte + s_offset + reihe;
			//Spielkarten soll Bild zugewiesen werden
			playCards[reihe][spalte]->owner = static_cast <int> (cards[sum]);
			

			// Signale verbinden
			connect(playCards[reihe][spalte], SIGNAL(clicked()), this, SLOT(myButtonClicked()));
		}
	}
		

	// Konfiguratiion eines Lables
	spielzugLabel = new QLabel(this);
	debugLabel = new QLabel(this);
	//int points = player1->points;
	//spielzugLabel->setText(QString::number(points));
	spielzugLabel->setGeometry(POS_LABEL_X, POS_LABEL_Y, 160, 50); //x,y,w,h
	debugLabel->setGeometry(POS_LABEL_X, POS_LABEL_Y+200, 160, 50);											  // Größe der Schriftart auf dem Label setzen
	QFont labelFont;
	labelFont.setPixelSize(14);
	spielzugLabel->setFont(labelFont);
	debugLabel->setFont(labelFont);


}

void Memory::initPixmap(int r, int s) {

	//vorher Abfrage Spielmodus Lama == 0, Bauenhof == 1, usw.
	
	QString Spielkarten[5][(N * N + 1) / 2];
	
	
	int modus = 0;
	QString praefix[5]{ "Lama_","Farm_","Jap_" };

	for (int pos = 0; pos < (N * N + 1) / 2; pos++) {
		QString buff;
		buff = praefix[modus] + QString::number(pos);
		Spielkarten[modus][pos] = buff;
		filename[pos] = Spielkarten[modus][pos] + ".png";
	}
	
	//QString TEST = "Lama_0.png";
	QPixmap Card_0;
	QPixmap Card_1;

	Card_0.load(filename[0]);
	Card_1.load(filename[1]);
	//listeIcon[0].load(filename[0]); // diese Methode funktioniert nicht!!!

	QPixmap Card_2(filename[2]);
	QPixmap Card_3(filename[3]);
	QPixmap Card_4(filename[4]);
	QPixmap Card_5(filename[5]);
	QPixmap Card_6(filename[6]);
	QPixmap Card_7(filename[7]);
	QPixmap Card_8(filename[8]);
	QPixmap Card_9(filename[9]);
	QPixmap Card_10(filename[10]);

	switch (playCards[r][s]->owner) {

	case 0: playCards[r][s]->setIcon(Card_0); break;
	case 1:	playCards[r][s]->setIcon(Card_1); break;
	case 2:	playCards[r][s]->setIcon(Card_2); break;
	case 3:	playCards[r][s]->setIcon(Card_3); break;
	case 4:	playCards[r][s]->setIcon(Card_4); break;
	case 5:	playCards[r][s]->setIcon(Card_5); break;
	case 6:	playCards[r][s]->setIcon(Card_6); break;
	case 7:	playCards[r][s]->setIcon(Card_7); break;
	case 8:	playCards[r][s]->setIcon(Card_10); break;
	case 9:	playCards[r][s]->setIcon(Card_9); break;
	default:playCards[r][s]->setIcon(Card_8); break;
	}
	return;
	
}

void Memory::initList() {
	int k = 0;
	//Füllen des Arrays
	/*if (N % 2 == 0) {*/
	for (int i = 0; i < N * N; i = i + 2) {
		cards[i] = k;
		cards[i + 1] = k;
		k++;
	}
	random_shuffle(cards, cards + (N * N));
	
	//debug
	/*for (int i = 0; i < N * N; i++) {
		qDebug() << cards[i] << " ";
	}
	qDebug() << endl;*/

}

void Memory::toggleButton(int r, int s) {
	
	
	initPixmap(r,s);


	//for (int pos = 0; pos < (N * N + 1) / 2; pos++) {
	//	listeIcon[pos] = filename[pos];
	//	listeIcon[pos].load(filename[pos]);
	//	//listeIcon[pos] =filename[pos];
	//	}


	//playCards[r][s]->setIcon(listeIcon[playCards[r][s]->owner]);


		for (int i = 0; i < N * N; i++) {
			//qDebug() << filename[i];
			//qDebug() << listeIcon[i];
		}
		qDebug() << endl;
		//debugLabel->setText(QString::fromStdString(filename[playCards[r][s]->owner]));
		
		/*spielFeld[r][s]->setIcon(Spielkarten[0][playCards[r][s]->owner]);*/
		//listeIcon[spielFeld[r][s]->owner] (filename[playCards[r][s]->owner]);

		

	playCards[r][s]->repaint();
	playCards[r][s]->umgedreht = true;
	
	compare(r, s);
	//checkGameOver();
	//if (checkGameOver()) {
	//	//spielzugLabel->setText("Gewonnen !!!");

	//	QApplication::exit(); //Beendet Programm
	//}

	}


//bool checkGameOver()
//{
//	int check = 0;
//	for (int reihe = 0; reihe < N; reihe++)
//	{
//		for (int spalte = 0; spalte < N; spalte++)
//		{
//			if (spielFeld[reihe][spalte]->umgedreht == true) 
//			{
//				check++;
//			}
//		}
//	}
//	if (check == N*N)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
	
//void setSound() {
//
//	return;
//}

bool Memory::compare(int r, int s)
{
	if (thefirst == false && playCards[r][s]->umgedreht == true)
	{
		thefirst = true;
		firstOne = playCards[r][s]->owner;
		firstCard_r = r;
		firstCard_s = s;
	}
	else
	{
		thisOne = playCards[r][s]->owner;
		if (thisOne == firstOne)
		{
			//pointToPlayer();
			thefirst = false;
			playCards[firstCard_r][firstCard_s]->setDisabled(true);
			playCards[r][s]->setDisabled(true);
			QMediaPlayer* positive_sound = new QMediaPlayer;
			positive_sound->setMedia(QUrl::fromLocalFile("correct.wav"));
			positive_sound->setVolume(50);
			positive_sound->play();
		}
		else
		{
			turnToBack(r, s);
			turnToBack(firstCard_r, firstCard_s);
			thefirst = false;
		}
	}
	return true;
}

void Memory::pointToPlayer() 
{
	//player1.addPoints();
}

void Memory::turnToBack(int reihe, int spalte)
{
	_sleep(400);
	QPixmap whs_logo("WH_Logo200.jpg");
	QIcon ButtonIcon(whs_logo);

	playCards[reihe][spalte]->setIcon(ButtonIcon);
	playCards[reihe][spalte]->setIconSize(whs_logo.rect().size());
	playCards[reihe][spalte]->setFixedSize(whs_logo.rect().size());
	playCards[reihe][spalte]->umgedreht = false;
	
}

void Memory::myButtonClicked()
{
	// Wer hat des Event erzeugt?
	QObject* obj = sender();
	//Returns the meta-method index of the signal that called the currently executing slot,
	//which is a member of the class returned by sender(). 
	//If called outside of a slot activated by a signal, -1 is returned.

	//Casten des QObjects in ein QPushButton
	QPushButton* button = qobject_cast<QPushButton*>(sender());

	//Casten auf MyButton
	MyButton* btnClicked = static_cast<MyButton*>(button);
	int r = btnClicked->btnReihe;
	int s = btnClicked->btnSpalte;
	char str[20];
	sprintf(str, "%d %d gecklickt", r, s);
	spielzugLabel->setText(str);
	spielzugLabel->repaint();
	//Toggeln des angeklickten Buttons
	toggleButton(r, s);


	/*if (checkGameOver()) {
		spielzugLabel->setText("Gewonnen !!!");

		QApplication::exit(); //Beendet Programm
	}*/

}
