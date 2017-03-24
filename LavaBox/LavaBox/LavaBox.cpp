//Sigma Parvis Magna - Francis Drake - Greatness, from small beginnings

#include <qt\qapplication.h> //<---in C++ include path <>
#include <QtGui\qwidget.h>
#include "myGLwindow.h" //<---in same directory file is located in compilation is in ""
#include "Game.h"





//ORDER//
//lavabox game relies on the engine
//uses code from the engine
//build engine code before the actual game
//engine code is not an executable anymore, it is a dll (dynamic linking)
//using engine as a library 
//pre processor -> compiler -> link (8:58 Adding QT middlware to sandbox game(4))


//NOTES
//checking jaimie's obj video in C++ playlist
//check the dll's and obj files information in c++
//openGL is right handed coordinate system


int main(int argc, char* argv[])
{
	//QApplication application(argc, argv);
	//myGLwindow myWidg;
	//if(!myWidg.initialize())
	//	return -1;
	//myWidg.show(); //show() -> shows the widget or setvisible to true or shows the object
	//int errorCode = application.exec();
	//if (! myWidg.shutdown() )
	//	errorCode = 1;
	//return errorCode;


	QApplication application(argc, argv);
	Game theGame;
	if (!theGame.initialize())
		return -1;
	theGame.Go();
	int errorCode = application.exec();
	if (!theGame.shutdown())
		errorCode = 1;
	return errorCode;


	
	
}