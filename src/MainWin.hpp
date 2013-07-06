#include <QtWidgets>
#include <QtWebKit>
#include <QtWebKitWidgets>
#include "Config.hpp"

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
	void changeTab();
	void closeTab(int index);
	
private:
	QPushButton *_enterButton;
	QPushButton *_refreshButton;
	QPushButton *_lockBoolButton;
	QPushButton *_addTabButton;
	
	QTabWidget *_tab;
	
	QLabel *_passwordLabel;
	QLineEdit *_passwordLine;
	
	
	
};