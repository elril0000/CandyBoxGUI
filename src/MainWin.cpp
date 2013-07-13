#include "MainWin.hpp"

MainWin::MainWin(): QMainWindow()
{
	
	createCentralWidget();
	createActions();
	createMenus();
	createTrayIcon();
	
	setProperties();
	setMinimumSize(500, 400);
	QString windowTitles("Candy Box GUI v");
	setWindowTitle(windowTitles + VERSION);
#ifdef OS_Linux
	setWindowIcon(QIcon("/usr/share/candyboxgui/image/candybox.png"));
#endif
#ifdef OS_Win32
	setWindowIcon(QIcon("image/candybox.png"));
#endif
	
	connect(_passwordLine, SIGNAL(returnPressed()), this, SLOT(loadPassword()));
	connect(_enterButton, SIGNAL(clicked()), this, SLOT(loadPassword()));
	connect(_refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
	connect(_lockBoolButton, SIGNAL(clicked(bool)), this, SLOT(lockPassword()));
	connect(_addTabButton, SIGNAL(clicked()), this, SLOT(newTabSlots()));
	connect(_tab, SIGNAL(currentChanged(int)), this, SLOT(changeTab()));
	connect(_tab->tabBar(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	connect(_quitAction, SIGNAL(triggered()), this, SLOT(close()));
	connect(_hideAction, SIGNAL(triggered()), this, SLOT(hide()));
	connect(_showAction, SIGNAL(triggered()), this, SLOT(showWindow()));
	connect(_autosaveCheck, SIGNAL(clicked(bool)), this, SLOT(autosave(bool)));
	connect(_autosaveTimer, SIGNAL(timeout()), this, SLOT(save()));
	connect(_reloadTimer, SIGNAL(timeout()), this, SLOT(refreshNoWarning()));
	connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(doubleClickTray(QSystemTrayIcon::ActivationReason)));
	connect(_saveAll, SIGNAL(clicked()), this, SLOT(save()));
	connect(_saveAllAction, SIGNAL(triggered()), this, SLOT(save()));
	connect(_saveAllAndQuit, SIGNAL(triggered()), this, SLOT(saveAndQuit()));
	connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
	connect(_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(_selectLanguage, SIGNAL(triggered()), this, SLOT(selectLanguage()));
}

void MainWin::doubleClickTray(QSystemTrayIcon::ActivationReason reason)
{
	if(reason == QSystemTrayIcon::DoubleClick)
	{
		if(isVisible())
			setWindowState(Qt::WindowActive);
		else
			setVisible(true);
	}
}

void MainWin::createActions()
{
	_hideAction = new QAction(tr("&Hide"), this);
	_hideAction->setShortcut(QKeySequence("Ctrl+H"));
	_quitAction = new QAction(tr("&Quit"), this);
	_quitAction->setShortcut(QKeySequence("Ctrl+Q"));
	_showAction = new QAction(tr("&Show"), this);
	_saveAllAction = new QAction(tr("&Save All"), this);
	_saveAllAction->setShortcut(QKeySequence("Ctrl+S"));
	_saveAllAndQuit = new QAction(tr("S&ave All && Quit"), this);
	_saveAllAndQuit->setShortcut(QKeySequence("Ctrl+Alt+S"));
	_selectLanguage = new QAction(tr("Select Language"), this);
	_aboutAction = new QAction(tr("About"), this);
	_aboutQtAction = new QAction(tr("About Qt"), this);
}

void MainWin::createCentralWidget()
{
	_autosaveTimer = new QTimer(this);
	_reloadTimer = new QTimer(this);
	_enterButton = new QPushButton(tr("Enter"));
	_refreshButton = new QPushButton();
	_lockBoolButton = new QPushButton();
	_lockBoolButton->setCheckable(true);
	_lockBoolButton->setChecked(Settings::isLocked());
	_addTabButton = new QPushButton;
	_saveAll = new QPushButton(tr("Save All"));
	
	_autosaveCheck = new QCheckBox(tr("Autosave?"));
#ifdef OS_Linux
    _refreshButton->setIcon(QIcon::fromTheme("view-refresh", QIcon("/usr/share/candyboxgui/image/refresh.png")));
	if(_lockBoolButton->isChecked())
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("/usr/share/candyboxgui/image/object-locked.png")));
	else
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("/usr/share/candyboxgui/image/object-unlocked.png")));
	
	_addTabButton->setIcon(QIcon::fromTheme("add", QIcon("/usr/share/candyboxgui/image/add.png")));
#endif
#ifdef OS_Win32
	_refreshButton->setIcon(QIcon::fromTheme("view-refresh", QIcon("image/refresh.png")));
	if(_lockBoolButton->isChecked())
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-locked.png")));
	else
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("image/object-unlocked.png")));
	
	_addTabButton->setIcon(QIcon::fromTheme("add", QIcon("image/add.png")));
#endif
	_autosaveCheck->setChecked(Settings::isAutosaving());
	autosave(Settings::isAutosaving());
	
    
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
			if(openedTab[i] == tr("(New Game)"))
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
	
	if(_tab->tabText(0) == tr("(New Game)"))
		_passwordLine->setText("");
	else
		_passwordLine->setText(_tab->tabText(0));
	
	_tab->setCornerWidget(_addTabButton);
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	
	bottomLayout->addWidget(_lockBoolButton);
	bottomLayout->addWidget(_passwordLabel);
	bottomLayout->addWidget(_passwordLine);
	bottomLayout->addWidget(_enterButton);
	bottomLayout->addWidget(_refreshButton);
	bottomLayout->addWidget(_autosaveCheck);
	bottomLayout->addWidget(_saveAll);
	bottomLayout->setAlignment(Qt::AlignRight);
	
	QVBoxLayout *layout = new QVBoxLayout;
	
	layout->addWidget(_tab);
	layout->addLayout(bottomLayout);
	
	QWidget *widgetCountainer = new QWidget;
	widgetCountainer->setLayout(layout)
	;
	setCentralWidget(widgetCountainer);
}

void MainWin::createMenus()
{
	_file = menuBar()->addMenu(tr("&File"));
	_file->addAction(_saveAllAction);
	_file->addAction(_hideAction);
	_file->addAction(_saveAllAndQuit);
	_file->addAction(_quitAction);
	
	_aboutMenu = menuBar()->addMenu(tr("&About"));
	_aboutMenu->addAction(_selectLanguage);
	_aboutMenu->addSeparator();
	_aboutMenu->addAction(_aboutAction);
	_aboutMenu->addAction(_aboutQtAction);
	
	_trayIconMenu = new QMenu(this);
	_trayIconMenu->addAction(_saveAllAction);
	_trayIconMenu->addAction(_showAction);
	_trayIconMenu->addAction(_saveAllAndQuit);
	_trayIconMenu->addAction(_quitAction);
}

void MainWin::createTrayIcon()
{
	_trayIcon = new QSystemTrayIcon(this);
#ifdef OS_Linux
	_trayIcon->setIcon(QIcon("/usr/share/candyboxgui/image/candybox.png"));
#endif
#ifdef OS_Win32
	_trayIcon->setIcon(QIcon("image/candybox.png"));
#endif
	_trayIcon->setContextMenu(_trayIconMenu);
	_trayIcon->setToolTip(tr("Candy Box GUI"));

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
#ifdef OS_Linux
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("/usr/share/candyboxgui/image/object-locked.png")));
#endif
#ifdef OS_Win32
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-locked.png")));
#endif
		_passwordLine->setReadOnly(true);
	}
	else
	{
#ifdef OS_Linux
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("/usr/share/candyboxguiimage/object-unlocked.png")));
#endif
#ifdef OS_Win32
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("image/object-unlocked.png")));
#endif
		
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

void MainWin::refreshNoWarning()
{
	for(int i = 0 ; i < _tab->count() ; i++)
	{
		_tab->widget(i)->findChild<QWebView* >()->reload();
	}
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
	hide();
    event->ignore();
	
}

void MainWin::writeOption()
{
    Settings::setMaximized(isMaximized());
	Settings::setAutosaving(_autosaveCheck->isChecked());
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

void MainWin::hide()
{
	setVisible(false);
}

void MainWin::close()
{
	if(QMessageBox::question(this, tr("Unsaved Change"), tr("All unsaved change will be lost.\nContinue?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		{
			writeOption();
			qApp->quit();
		}
}

void MainWin::showWindow()
{
	if(isVisible())
		setWindowState(Qt::WindowActive);
	else
		setVisible(true);
}

void MainWin::init()
{
	show();
	
	qApp->processEvents();
	QTimer::singleShot(1200, _trayIcon, SLOT(show()));
	
	
}

void MainWin::autosave(bool saving)
{
	if(saving)
	{
		_autosaveTimer->start(300000);
		_reloadTimer->start(3601000);
	}
	else
	{
		_autosaveTimer->stop();
		_reloadTimer->stop();
	}
}

void MainWin::saveAndQuit()
{
	save();
	QMessageBox::information(this, tr("Succesfully saved"), tr("All games were successfully saved."));
	writeOption();
	qApp->quit();
}

void MainWin::selectLanguage()
{
	_languageSelectionWin = new QDialog(this);
	
	_language = new QComboBox();
	QLabel *languageLabel = new QLabel(tr("Language"));
	QPushButton *okButton = new QPushButton(tr("Ok"));
	
	QDir *dir = new QDir("translation");
	QStringList filter;
	filter << "candyboxgui_*.qm";
	dir->setNameFilters(filter);
	QStringList fileList = dir->entryList();
	
	_language->addItem("System");
	_language->addItem("English");
	
	for(int i = 0 ; i < fileList.count() ; i++)
	{
		QString newLang = fileList[i].remove(0, 12);
		newLang.remove(2, 3);
		_language->addItem(newLang);
		
	}
	
	QBoxLayout *hlayout = new QHBoxLayout();
	hlayout->addWidget(languageLabel);
	hlayout->addWidget(_language);
	QBoxLayout *layout = new QVBoxLayout();
	layout->addLayout(hlayout);
	layout->addWidget(okButton, Qt::AlignRight);
	
	_languageSelectionWin->setLayout(layout);
	
	connect(okButton, SIGNAL(clicked()), this, SLOT(writeLanguage()));
	int index = 0;
	
	for(int i = 0 ; i < _language->count() ; i++)
	{
		if(Settings::getLang() == _language->itemText(i))
		{
			index = i;
			i = _language->count();
		}
	}
	_language->setCurrentIndex(index);
	
	_languageSelectionWin->exec();
	
	
}

void MainWin::writeLanguage()
{
	Settings::setLang(_language->currentText());
	QMessageBox::information(this, tr("Restart Needed"), tr("You need to restart the application to apply the language"));
	_languageSelectionWin->accept();
}

void MainWin::about()
{
	QMessageBox::information(this, tr("About"), tr("Special thanks to gracicot for the help he provided me : <a href=http://www.github.com/gracicot>gracicot's Github</a><br /><br />All the fallback icons are from the crystal theme by Everaldo Coelho.<br /> <a href=http://www.iconfinder.com/iconsets/crystalproject>http://www.iconfinder.com/iconsets/crystalproject</a>"));
}
