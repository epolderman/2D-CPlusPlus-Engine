#ifndef LAVABOX_MY_GL_WINDOW_H
#define LAVABOX_MY_GL_WINDOW_H
#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>

//**QGLWIDGET CLASS INFORMATION**//

//QGLWidget class is a widget for rendering OpenGL graphics.
//QGLWidget provides functionality for displaying OpenGL graphics integrated into a Qt application. 
//It is very simple to use.You inherit from it and use the subclass like any other QWidget, 
//except that you have the choice between using QPainter and standard OpenGL rendering commands.
//QGLWidget provides three convenient virtual functions that you can reimplement 
//in your subclass to perform the typical OpenGL tasks 

//LINK -> http://doc.qt.io/qt-4.8/qwidget.html#visible-prop

//paintGL() - Renders the OpenGL scene.Gets called whenever the widget needs to be updated.

//resizeGL() - Sets up the OpenGL viewport, projection, etc.Gets called whenever the 
//widget has been resized(and also when it is shown for the first time because all newly 
//created widgets get a resize event automatically).

//initializeGL() - Sets up the OpenGL rendering context, defines display lists, etc.Gets called 
//once before the first time resizeGL() or paintGL() is called.

//**END QGLWIDGET class information**//

///////////////////////////////////////////////////////////////////////////////////////////

//*QOBJECT MACRO INFORMATION**//
//macro needed declaration needed for the use of slots
//needs meta data and definitions for the macro QObject
//moc.exe takes declarations of QOBJECT class and myGLwindow.h and generates the definitions
//in its own CPP file//

//END QOBJECT MACRO INFORMATION//

///////////////////////////////////////////////////////////////////////////////////////////



class myGLwindow : public QGLWidget
{

Q_OBJECT
QTimer theTimer;
protected:
	void initializeGL();
	void paintGL();
	//void keyPressEvent(QKeyEvent *);
private slots: //slots qt thing event handler
	void theUpdate();
private:
	void update();
	void draw();
	void setGLstate();
	void pathfindingLerper();
	void targetNextLerpPoint();
	void updateVelocity();
	void rotation();
	void checkBoundaries();
public:
	bool shutdown();
	bool initialize();
	//video vector subtraction 137
};

#endif