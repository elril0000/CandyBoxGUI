#include <iostream>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include "Config.hpp"
#include "MainWin.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	cout << NAME << " v" << VERSION << endl;
	
	QString locale = QLocale::system().name().section('_', 0, 0);
  
    QTranslator translator[2];
    translator[0].load(QString("translation/candyboxgui_") + locale);
	translator[1].load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator[0]);
	app.installTranslator(&translator[1]);
	
	MainWin *win = new MainWin;
	win->init();
	
	return app.exec();
}
