#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();
    w->setupConsoleWindow();
    w->setupIndicators();


    /* TODO: Resources file in QT */
    std::ofstream ofs("/Users/michael/Documents/workspace/MicroCART-F2013/BasicPrograms/GUI/K_LOL.txt", std::ofstream::out);

    /* Setup enclosed CLI */
    /* DEFAULT SETTINGS, MAKE A FUNCTION */
        Logger log(ofs);
        CLI* cli = new CLI(log);
        cli->setUsingCameras(true);
        cli->setUsingController(false);
         w->setCLI(cli);


     /* Set std:err to the console in GUI */
     /*
      * http://www.qtforum.org/article/678/redirecting-cout-cerr-to-qdebug.html
     */

    w->show();


    return a.exec();
}
