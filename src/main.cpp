/*
The MIT License (MIT)

Copyright (c) 2013 Yann Gauthier

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <iostream>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include "Config.hpp"
#include "MainWin.hpp"
#include "Settings.hpp"

#define SHOW true
#define DONTSHOW false
using namespace std;
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	cout << NAME << " v" << VERSION << endl;
	
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator translator[2];
	
	if(Settings::getLang() == "System")
	{
		
		translator[0].load(QString(APP_DIRECTORY + "translation/candyboxgui_") + locale);
		translator[1].load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		app.installTranslator(&translator[0]);
		app.installTranslator(&translator[1]);
	}
	else if(Settings::getLang() != "English")
	{
		translator[0].load(QString(APP_DIRECTORY + "translation/candyboxgui_") + Settings::getLang());
		translator[1].load(QString("qt_") + Settings::getLang(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		app.installTranslator(&translator[0]);
		app.installTranslator(&translator[1]);
	}

	MainWin *win = new MainWin;
	QStringList args = QCoreApplication::arguments();
	bool show = SHOW;
	if(args.count() > 1)
	{
		for(int i = 1 ; i < args.count() ; i++)
		{
			if(args.at(i).left(2) != "--")
			{
				for(int j = 1 ; j < args.at(i).count() ; j++)
				{
					cout << j;
					if(strncmp(&args.at(i).toStdString().c_str()[j], "b", 1) == 0)
					{
						show = DONTSHOW;
						cout << args.at(i).toStdString().at(j) << endl;
					}
					else if(strncmp(&args.at(i).toStdString().c_str()[j], "a", 1) == 0)
					{
						win->setAutosave(true);
						cout << args.at(i).toStdString().at(j) << endl; 
					}
					else if(strncmp(&args.at(i).toStdString().c_str()[j], "n", 1) == 0)
					{
						win->setAutosave(false);
						cout << args.at(i).toStdString().at(j) << endl;
						
					}
					else
						cout << "Wrong arguments provided : " << &args.at(i).toStdString().at(j) << endl;
				}
			}
			else if(args.at(i).left(2) == "--")
			{
				if(args.at(i).toStdString() == "--background")
					show = DONTSHOW;
				else if(args.at(i).toStdString() == "--autosave")
					win->setAutosave(true);
				else if(args.at(i).toStdString() == "--noautosave")
					win->setAutosave(false);
				else
					cout << "Wrong arguments provided : " << args.at(i).toStdString() << endl;
			}
		}
		
	}

	if(show)
	{
		win->init();
	}
	else
	{
		win->initInBack();
	}
	
	
	return app.exec();
}
