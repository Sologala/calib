#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include "widget/points.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <QtOpenGL/qgl.h>
#include <QtOpenGL>
#include <qvector.h>
#include <thread_pool.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
