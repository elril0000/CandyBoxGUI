#pragma once

#include "Config.hpp"
#include <QtCore>

namespace Settings
{
	bool isMaximized();
	QSize getSize();
	QPoint getPosition();
	QString getLang();
	QStringList getOpenedTab();
	bool isLocked();
	bool isAutosaving();
	int getRefreshTime();
	int getAutosaveTime();
	
	void setAutosaving(bool autosaving);
	void setMaximized(bool maximized);
	void setSize(QSize size);
	void setSize(int w, int h);
	void setPosition(QPoint position);
	void setPosition(int x, int y);
	void setLang(QString lang);
	void setOpenedTab(QStringList openedTab);
	void setLocked(bool locked);
	void setAutosaveTime(int autosavetime);
	void setRefreshTime(int refreshTime);
  
}