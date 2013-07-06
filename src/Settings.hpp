#pragma once

#include "Config.hpp"
#include <QtCore>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();
    
    static bool isMaximized();
    static QSize getSize();
    static QPoint getPosition();
    //static QString getLang();
	static QStringList getOpenedTab();
    static bool isLocked();
	
    static void setMaximized(bool maximized);
    static void setSize(QSize size);
    static void setSize(int w, int h);
    static void setPosition(QPoint position);
    static void setPosition(int x, int y);
    //static void setLang(QString lang);
	static void setOpenedTab(QStringList openedTab);
	static void setLocked(bool locked);
    
public slots:
    
private:
    
    
    
};