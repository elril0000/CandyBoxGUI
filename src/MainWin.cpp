#include "MainWin.hpp"

MainWin::MainWin(): QMainWindow()
{
	_enterButton = new QPushButton(tr("Enter"));
	_refreshButton = new QPushButton();
	_lockBoolButton = new QPushButton();
	_lockBoolButton->setCheckable(true);
	_addTabButton = new QPushButton;
	
	_tab = new QTabWidget;
	_tab->addTab(newTab(tr("http://candies.aniwey.net/index.php?pass=wtrbr")), tr("(New Game)"));
	_passwordLabel = new QLabel;
	_passwordLine = new QLineEdit;
	
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	
	bottomLayout->addWidget(_lockBoolButton);
	bottomLayout->addWidget(_passwordLabel);
	bottomLayout->addWidget(_passwordLine);
	bottomLayout->addWidget(_enterButton);
	bottomLayout->addWidget(_refreshButton);
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	layout->addWidget(_tab);
	layout->addLayout(bottomLayout);
	
	QWidget *widgetCountainer = new QWidget;
	widgetCountainer->setLayout(layout);
	
	setCentralWidget(widgetCountainer);
}

QWebView *MainWin::ActualPage()
{
    return _tab->currentWidget()->findChild<QWebView *>();
}

QWidget *MainWin::newTab(QUrl url)
{
	QWidget *widgetCountainer = new QWidget;
	QWebView *webPage = new QWebView;
	
	
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(webPage);
	widgetCountainer->setLayout(layout);
	
	webPage->load(url);
	
	return widgetCountainer;
}
