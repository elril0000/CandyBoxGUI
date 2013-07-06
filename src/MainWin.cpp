#include "MainWin.hpp"

MainWin::MainWin(): QMainWindow()
{
	_enterButton = new QPushButton(tr("Enter"));
	_refreshButton = new QPushButton();
	_lockBoolButton = new QPushButton();
	_lockBoolButton->setCheckable(true);
	_lockBoolButton->setChecked(Settings::isLocked());
	_addTabButton = new QPushButton;
	
	_refreshButton->setIcon(QIcon::fromTheme("view-refresh", QIcon("image/view-refresh.png")));
	if(_lockBoolButton->isChecked())
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-locked.png")));
	else
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-unlocked.png")));
	
	_addTabButton->setIcon(QIcon::fromTheme("add", QIcon("add.png")));
	//_lockBoolButton->setFlat(true);
	//_lockBoolButton->setUpdatesEnabled(false);
	QStringList openedTab = Settings::getOpenedTab();
	
	_passwordLabel = new QLabel;
	_passwordLine = new QLineEdit;
	_passwordLine->setReadOnly(Settings::isLocked());
	
	_tab = new QTabWidget;
	
	
	if(openedTab.isEmpty())
	{
		_tab->addTab(newTab(tr("http://candies.aniwey.net/index.php")), tr("(New Game)"));
	}
	else
	{
		for(int i = 0 ; i < openedTab.count() ; i++)
		{
			if(openedTab[i] == "(New Game)")
			{
				_tab->addTab(newTab(tr("http://candies.aniwey.net/index.php")), tr("(New Game)"));
			}
			else
			{
				_tab->addTab(newTab("http://candies.aniwey.net/index.php?pass=" + openedTab[i]), openedTab[i]);
			}
		}
	}
	_tab->setCurrentIndex(0);
	_tab->setTabsClosable(true);
	
	if(_tab->tabText(0) == "(New Game)")
		_passwordLine->setText("");
	else
		_passwordLine->setText(_tab->tabText(0));
	
	connect(_passwordLine, SIGNAL(returnPressed()), this, SLOT(loadPassword()));
	connect(_enterButton, SIGNAL(clicked()), this, SLOT(loadPassword()));
	connect(_refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
	connect(_lockBoolButton, SIGNAL(clicked(bool)), this, SLOT(lockPassword()));
	connect(_addTabButton, SIGNAL(clicked()), this, SLOT(newTabSlots()));
	connect(_tab, SIGNAL(currentChanged(int)), this, SLOT(changeTab()));
	connect(_tab->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	
	_tab->setCornerWidget(_addTabButton);
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	
	bottomLayout->addWidget(_lockBoolButton);
	bottomLayout->addWidget(_passwordLabel);
	bottomLayout->addWidget(_passwordLine);
	bottomLayout->addWidget(_enterButton);
	bottomLayout->addWidget(_refreshButton);
	bottomLayout->setAlignment(Qt::AlignRight);
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	layout->addWidget(_tab);
	layout->addLayout(bottomLayout);
	
	QWidget *widgetCountainer = new QWidget;
	widgetCountainer->setLayout(layout);
	
	setProperties();
	setMinimumSize(500, 400);
	setCentralWidget(widgetCountainer);
	QString windowTitles("Candy Box GUI v");
	windowTitles += VERSION;
	setWindowTitle(windowTitles);
	setWindowIcon(QIcon("image/candybox.png"));
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

void MainWin::loadPassword()
{
	if(!_passwordLine->text().isEmpty())
	{
		if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		{
			ActualPage()->load(QUrl("http://candies.aniwey.net/index.php?pass=" + _passwordLine->text()));
			_tab->setTabText(_tab->currentIndex(), _passwordLine->text());
		}
	}
	
	else
	{
		if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		{
			ActualPage()->load(QUrl("http://candies.aniwey.net/index.php"));
			_tab->setTabText(_tab->currentIndex(), tr("(New Game)"));
		}
	}
}

void MainWin::lockPassword()
{
	if(_lockBoolButton->isChecked())
	{
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-locked.png")));
		_passwordLine->setReadOnly(true);
	}
	else
	{
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("image/object-unlocked.png")));
		_passwordLine->setReadOnly(false);
	}
}

void MainWin::newTabSlots()
{
	_tab->setCurrentIndex(_tab->addTab(newTab(tr("http://candies.aniwey.net/index.php")), tr("(New Game)")));
}

void MainWin::refresh()
{
	if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		ActualPage()->reload();
}

void MainWin::changeTab()
{
	if(_tab->tabText(_tab->currentIndex()) == tr("(New Game)"))
	{
		_passwordLine->setText("");
	}
	else
	{
		_passwordLine->setText(_tab->tabText(_tab->currentIndex()));
	}
}

void MainWin::closeTab(int index)
{
	if(_tab->count() <= 1)
	{
		if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
			_tab->removeTab(index);
			qApp->quit();
	}
	else
	{
		if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
			_tab->removeTab(index);
	}
}

void MainWin::closeEvent(QCloseEvent * event)
{
	
	if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		writeOption();
		event->accept();
	}
}

void MainWin::writeOption()
{
    Settings::setMaximized(isMaximized());

    Settings::setPosition(pos());   
    Settings::setSize(size());
	Settings::setLocked(_lockBoolButton->isChecked());
	QStringList openedTab;
	for(int i = 0 ; i < _tab->count() ; i++)
	{
		openedTab.push_back(_tab->tabText(i));
	}
	Settings::setOpenedTab(openedTab);
}

void MainWin::setProperties()
{
	if(Settings::isMaximized())
		showMaximized();
	else
	{
		resize(Settings::getSize());
		move(Settings::getPosition());
	}
}

