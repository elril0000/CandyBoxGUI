#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QApplication>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include <iostream>
#include "Config.hpp"
#include "Settings.hpp"

class MainWin : public QMainWindow
{
	Q_OBJECT
public:
    MainWin();
	QWebView *ActualPage();
	QWidget *newTab(QUrl url);
	
public slots:
	void loadPassword();
	void lockPassword();
	void newTabSlots();
	void refresh();
	void refreshNoWarning();
	void changeTab();
	void closeTab(int index);
	void writeOption();
	void setProperties();
	void hide();
	void showWindow();
	void close();
	void init();
	void selectLanguage();
	void writeLanguage();
	void webMenuExec(QPoint point);
	
	void doubleClickTray(QSystemTrayIcon::ActivationReason reason);
	
	void createActions();
	void createMenus();
	void createTrayIcon();
	void createCentralWidget();
	void autosave(bool saving);
	
	void save();
	void saveAndQuit();
	
	void about();
	
private:
	QPushButton *_enterButton;
	QPushButton *_refreshButton;
	QPushButton *_lockBoolButton;
	QPushButton *_addTabButton;
	QPushButton *_saveAll;
	
	QComboBox *_language;
	
	QDialog *_languageSelectionWin;
	
	QCheckBox *_autosaveCheck;
	
	QAction *_quitAction;
	QAction *_hideAction;
	QAction *_showAction;
	QAction *_saveAllAction;
	QAction *_saveAllAndQuit;
	QAction *_selectLanguage;
	QAction *_aboutAction;
	QAction *_aboutQtAction;
	QAction *_refreshAction;
	
	QMenu *_file;
	QMenu *_aboutMenu;
	QMenu *_webMenu;
	
	QTabWidget *_tab;
	
	QLabel *_passwordLabel;
	QLineEdit *_passwordLine;
	
	QSystemTrayIcon *_trayIcon;
	QMenu *_trayIconMenu;
	
	void closeEvent(QCloseEvent *event);
	
	QTimer *_autosaveTimer;
	QTimer *_reloadTimer;
	
	
	
};
