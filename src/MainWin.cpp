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
	setWindowIcon(QIcon("image/candybox.png"));
	
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
	_quitAction = new QAction(tr("&Quit"), this);
	_quitAction->setShortcut(QKeySequence("Ctrl+Q"));
	_showAction = new QAction(tr("&Show"), this);
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
	
	_autosaveCheck = new QCheckBox(tr("Autosave?"));
	
    _refreshButton->setIcon(QIcon::fromTheme("view-refresh", QIcon("image/refresh.png")));
	if(_lockBoolButton->isChecked())
		_lockBoolButton->setIcon(QIcon::fromTheme("object-locked", QIcon("image/object-locked.png")));
	else
		_lockBoolButton->setIcon(QIcon::fromTheme("object-unlocked", QIcon("image/object-unlocked.png")));
	
	_autosaveCheck->setChecked(Settings::isAutosaving());
	autosave(Settings::isAutosaving());
	
    _addTabButton->setIcon(QIcon::fromTheme("add", QIcon("image/add.png")));
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
	
	_tab->setCornerWidget(_addTabButton);
	QHBoxLayout *bottomLayout = new QHBoxLayout;
	
	bottomLayout->addWidget(_lockBoolButton);
	bottomLayout->addWidget(_passwordLabel);
	bottomLayout->addWidget(_passwordLine);
	bottomLayout->addWidget(_enterButton);
	bottomLayout->addWidget(_refreshButton);
	bottomLayout->addWidget(_autosaveCheck);
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
	_file->addAction(_hideAction);
	_file->addAction(_quitAction);
	
	_trayIconMenu = new QMenu(this);
	_trayIconMenu->addAction(_showAction);
	_trayIconMenu->addAction(_quitAction);
}

void MainWin::createTrayIcon()
{
	_trayIcon = new QSystemTrayIcon(QIcon("image/candybox.png"), this);
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
	
	qApp->processEvents(); // Sans ça la position de l'icone n'est pas connue tout de suite
	QTimer::singleShot(1000, _trayIcon, SLOT(show()));
	
	
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

void MainWin::save()
{
	
	QString javascriptQuery = R"delimiter($.ajax({
		type: "POST",//Envoi des donnÃ©es avec la mÃ©thode POST
		url: "scripts/save.php",//Ã  la page sauvegarde.php
		data: {
			code : ((code === undefined || code == null || code.length == "") ? 0 : code),
			swordName : sword.name,
			swordSpecialSword : getPhpStuff(sword.specialSword),
			swordSpecialPower : sword.specialPower,
			candiesNbrOwned : candies.nbrOwned,
			candiesNbrThrown : candies.nbrThrown,
			candiesNbrEaten : candies.nbrEaten,
			candiesNbrTotal : candies.nbrTotal,
			candiesCandiesPerSecond : candies.candiesPerSecond,
			candiesConverterActivated : getPhpStuff(candiesConverter.activated),
			cauldronBookPage : cauldron.bookPage,
			cauldronCandies : cauldron.candiesInTheCauldron,
			cauldronLollipops : cauldron.lollipopsInTheCauldron,
			chocolateBarsNbrOwned : chocolateBars.nbrOwned,
			farmLollipopsPlanted : farm.lollipopsPlanted,
			farmCurrentFlagIndex : farm.currentFlagIndex,
			farmPlantingButtonsStep : farm.plantingButtonsStep,
			forgeStep : forge.step,
			shopLollipopsButtonsShown : getPhpStuff(shop.buy10LollipopsButtonShown),
			shopShown : getPhpStuff(shop.shown),
			shopTicklingStep : shop.ticklingStep,
			shopClickingOnLollipopStep : shop.clickingOnLollipopStep,
			hutStep : hut.step,
			hutSpeech : hut.speech,
			inventoryMagicianHatLetter : inventory.magicianHatLetter,
			lollipopsNbrOwned : lollipops.nbrOwned,
			lollipopsNbrInStock : lollipops.nbrInStock,
			lollipopsNbrBought : lollipops.nbrBought,
			mainNbrOfSecondsSinceLastMinInterval : main.nbrOfSecondsSinceLastMinInterval,
			mainNbrOfSecondsSinceLastHourInterval : main.nbrOfSecondsSinceLastHourInterval,
			mainNbrOfSecondsSinceLastDayInterval : main.nbrOfSecondsSinceLastDayInterval,
			mountGoblinBasicChestProbability : mountGoblin.basicChestProbability,
			peacefulForestBasicChestProbability : peacefulForest.basicChestProbability,
			peacefulForestPoniesEncountered : peacefulForest.poniesEncountered,
			objectsHaveObjectKey : getPhpStuff(objects.list.key.have),
			objectsHaveObjectHutMap : getPhpStuff(objects.list.hutMap.have),
			objectsHaveObjectWellMap : getPhpStuff(objects.list.wellMap.have),
			objectsHaveObjectSwampMap : getPhpStuff(objects.list.swampMap.have),
			objectsHaveObjectBoots : getPhpStuff(objects.list.boots.have),
			objectsHaveObjectMagicianHat : getPhpStuff(objects.list.magicianHat.have),
			objectsHaveObjectPinkRing : getPhpStuff(objects.list.pinkRing.have),
			objectsHaveObjectForgeMap : getPhpStuff(objects.list.forgeMap.have),
			objectsHaveObjectCandiesConverter : getPhpStuff(objects.list.candiesConverter.have),
			objectsHaveObjectPlateArmour : getPhpStuff(objects.list.plateArmour.have),
			objectsHaveObjectCauldron : getPhpStuff(objects.list.cauldron.have),
			objectsHaveObjectMagicalHorn : getPhpStuff(objects.list.magicalHorn.have),
			objectsHaveObjectHornOfPlenty : getPhpStuff(objects.list.hornOfPlenty.have),
			objectsHaveObjectOldAmulet : getPhpStuff(objects.list.oldAmulet.have),
			potionsShownHealth : getPhpStuff(potions.list.health.shown),
			potionsShownEscape : getPhpStuff(potions.list.escape.shown),
			potionsShownBerserk : getPhpStuff(potions.list.berserk.shown),
			potionsShownFireScroll : getPhpStuff(potions.list.fireScroll.shown),
			potionsShownAcidRainScroll : getPhpStuff(potions.list.acidRainScroll.shown),
			potionsShownTeleportScroll : getPhpStuff(potions.list.teleportScroll.shown),
			potionsShownEarthquakeScroll : getPhpStuff(potions.list.earthquakeScroll.shown),
			potionsShownImpInvocationScroll : getPhpStuff(potions.list.impInvocationScroll.shown),
			potionsShownMajorHealth : getPhpStuff(potions.list.majorHealth.shown),
			potionsShownInvulnerability : getPhpStuff(potions.list.invulnerability.shown),
			potionsShownTurtle : getPhpStuff(potions.list.turtle.shown),
			potionsShownJelly : getPhpStuff(potions.list.jelly.shown),
			potionsShownSeed : getPhpStuff(potions.list.seed.shown),
			potionsShownCloning : getPhpStuff(potions.list.cloning.shown),
			potionsShownSuperman : getPhpStuff(potions.list.superman.shown),
			potionsShownGmooh : getPhpStuff(potions.list.gmooh.shown),
			potionsNbrOwnedHealth : potions.list.health.nbrOwned,
			potionsNbrOwnedEscape : potions.list.escape.nbrOwned,
			potionsNbrOwnedBerserk : potions.list.berserk.nbrOwned,
			potionsNbrOwnedFireScroll : potions.list.fireScroll.nbrOwned,
			potionsNbrOwnedAcidRainScroll : potions.list.acidRainScroll.nbrOwned,
			potionsNbrOwnedTeleportScroll : potions.list.teleportScroll.nbrOwned,
			potionsNbrOwnedEarthquakeScroll : potions.list.earthquakeScroll.nbrOwned,
			potionsNbrOwnedImpInvocationScroll : potions.list.impInvocationScroll.nbrOwned,
			potionsNbrOwnedMajorHealth : potions.list.majorHealth.nbrOwned,
			potionsNbrOwnedInvulnerability : potions.list.invulnerability.nbrOwned,
			potionsNbrOwnedTurtle : potions.list.turtle.nbrOwned,
			potionsNbrOwnedJelly : potions.list.jelly.nbrOwned,
			potionsNbrOwnedSeed : potions.list.seed.nbrOwned,
			potionsNbrOwnedCloning : potions.list.cloning.nbrOwned,
			potionsNbrOwnedSuperman : potions.list.superman.nbrOwned,
			potionsNbrOwnedGmooh : potions.list.gmooh.nbrOwned,
			questMaxLandOrder : quest.maxLandOrder,
			questTiredTime : quest.tiredTime,
			spellsFasterCandiesFibo1 : spells.fasterCandiesFiboPrev,
			spellsFasterCandiesFibo2 : spells.fasterCandiesFiboCurr,
			swampStep : swamp.step,
			tabsAnimation : tabs.animation,
			wishingWellSpeech : wishingWell.speech,
			wishingWellStep : wishingWell.step,
			yourselfCanSurpass : getPhpStuff(yourself.canSurpass),
			developperComputerWon : getPhpStuff(developperComputer.won)
		},
	   success: function(msg){//Une fois la requÃªte terminÃ©e
			if(msg=="Erreur"){ //Si la sauvegarde Ã  Ã©chouÃ©e
			
				// Alors on affiche un message
                                alert("There was a problem while saving. Please try again later :/");   
				$("span#save").html("");
				
			}else{ // si la sauvegarde Ã  fonctionnÃ©e
			
				// on affiche le lien de chargement
                                if(msg.substring(0,5) != "<br /"){ 
				code = msg.substring(0,5);
								
                                $("span#save").html(" You can load your save later <a href=\"http://candies.aniwey.net/index.php?pass=" + code + "\">here</a>.");
						        }
                                else{
                                    alert("There was a problem while saving. Please try again later :/");    
                                }
                        }
	   }
	});)delimiter";
				
	for(int i = 0 ; i < _tab->count() ; i ++)
	{
		_tab->widget(i)->findChild<QWebView *>()->page()->mainFrame()->evaluateJavaScript(javascriptQuery);
	}
}
