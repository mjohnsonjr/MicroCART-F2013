#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "src/CLI.h"
#include "src/Q_DebugStream.h"
#include "src/Logger.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline CLI* getCLI(){
        return this->cli;
    }

    void setCLI(CLI*);
    void setupConsoleWindow();
    void setupIndicators();

private slots:

    /* MY SLOTS */
    void updateVisuals();
    /* END MY SLOTS */
    void on_startButton_clicked();
    void on_ManualThrottlespinBox_valueChanged(int arg1);
//    void on_AltitudeSpinbox_valueChanged(int arg1);
//    void on_LatitudeSpinbox_valueChanged(int arg1);
//    void on_LongitudeSpinbox_valueChanged(int arg1);

    void on_Execute_Button_clicked();

    void on_Apply_pushButton_clicked();

    void on_ManualThrottle_checkBox_toggled(bool checked);

    void on_Auto_button_clicked(bool checked);

    void on_Manual_button_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    CLI *cli;
    Q_DebugStream *qdb;
    QTimer* timer;
};

#endif // MAINWINDOW_H
