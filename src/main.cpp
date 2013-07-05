#include <iostream>
#include <QApplication>
#include "Config.hpp"
#include "MainWin.hpp"

using namespace std;
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	cout << NAME << " v" << VERSION << endl;
	
	MainWin win;
	win.show();
	
	return app.exec();
}
