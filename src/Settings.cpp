#include "Settings.hpp"

Settings::Settings()
{

}

QPoint Settings::getPosition()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("Dimension/pos").toPoint();
}

QSize Settings::getSize()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("Dimension/size").toSize();
}

QStringList Settings::getOpenedTab()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("tab").toStringList();
}

bool Settings::isLocked()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("locked").toBool();
}

/*
QString Settings::getLang()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("lang").toString();
}//*/

bool Settings::isMaximized()
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	return settings->value("Dimension/maximized").toBool();
}

void Settings::setMaximized(bool maximized)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
    if(maximized)
	  settings->setValue("Dimension/maximized", "true");
      else
	  settings->setValue("Dimension/maximized", "false");
}

void Settings::setPosition(QPoint pos)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
    settings->setValue("Dimension/pos", pos);
}

void Settings::setPosition(int x, int y)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
    QPoint pos(x, y);
	settings->setValue("Dimension/pos", pos);
}

void Settings::setSize(QSize size)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
    settings->setValue("Dimension/size", size);
}


void Settings::setSize(int w, int h)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
    QSize size(w, h);
	settings->setValue("Dimension/size", size);
}

void Settings::setLocked(bool locked)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	settings->setValue("locked", locked);
}

void Settings::setOpenedTab(QStringList openedTab)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	settings->setValue("tab", openedTab);
}

/*
void Settings::setLang(QString lang)
{
	QSettings *settings = new QSettings(tr("Candy Box GUI"), "Candy Box GUI");
	settings->setValue("lang", lang);
}//*/