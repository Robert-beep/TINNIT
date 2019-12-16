#include "MyButton.h"
#include <QPushButton>
#include <QtGui/QPainter>
#include <QtCore/QParallelAnimationGroup>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTime>
#include <Memory.h>




MyButton::MyButton(const int i, const int j, QWidget* parent) : QPushButton(parent)
{
	btnReihe = i;
	btnSpalte = j;
	owner = LAMA_1_;
	umgedreht = false;

}





MyButton::~MyButton()
{
}


