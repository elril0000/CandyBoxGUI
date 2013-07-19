#include "Settings.hpp"

QPoint Settings::getPosition()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("Dimension/pos").toPoint();
}

QSize Settings::getSize()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("Dimension/size").toSize();
}

QStringList Settings::getOpenedTab()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("tab").toStringList();
}

bool Settings::isLocked()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("locked").toBool();
}

//*
QString Settings::getLang()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("lang", "System").toString();
}//*/

bool Settings::isMaximized()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("Dimension/maximized").toBool();
}

bool Settings::isAutosaving()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("Autosave").toBool();
}

int Settings::getAutosaveTime()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("AutosaveTime", 5).toInt();
}

int Settings::getRefreshTime()
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	return settings->value("RefreshTime", 60).toInt();
}

void Settings::setAutosaving(bool autosaving)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("Autosave", autosaving);
}


void Settings::setMaximized(bool maximized)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
    if(maximized)
	  settings->setValue("Dimension/maximized", "true");
      else
	  settings->setValue("Dimension/maximized", "false");
}

void Settings::setPosition(QPoint pos)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
    settings->setValue("Dimension/pos", pos);
}

void Settings::setPosition(int x, int y)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
    QPoint pos(x, y);
	settings->setValue("Dimension/pos", pos);
}

void Settings::setSize(QSize size)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
    settings->setValue("Dimension/size", size);
}


void Settings::setSize(int w, int h)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
    QSize size(w, h);
	settings->setValue("Dimension/size", size);
}

void Settings::setLocked(bool locked)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("locked", locked);
}

void Settings::setOpenedTab(QStringList openedTab)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("tab", openedTab);
}

//*
void Settings::setLang(QString lang)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("lang", lang);
}//*/

void Settings::setAutosaveTime(int autosavetime)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("AutosaveTime", autosavetime);
}

void Settings::setRefreshTime(int refreshTime)
{
	QSettings *settings = new QSettings("Candy Box GUI", "Candy Box GUI");
	settings->setValue("RefreshTime", refreshTime);
}
