#include <QtWidgets>
#include <QtWebKit>
#include <QtWebKitWidgets>

class MainWin : public QMainWindow
{
public:
    MainWin();
	QWebView *ActualPage();
	QWidget *newTab(QUrl url);
	
private:
	QPushButton *_enterButton;
	QPushButton *_refreshButton;
	QPushButton *_lockBoolButton;
	QPushButton *_addTabButton;
	
	QTabWidget *_tab;
	
	QLabel *_passwordLabel;
	QLineEdit *_passwordLine;
	
	
	
};