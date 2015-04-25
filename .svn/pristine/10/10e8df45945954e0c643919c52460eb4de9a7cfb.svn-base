#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/CLI.h"
#include <sstream>
#include "src/Q_DebugStream.h"
#include "src/QuadCommand.h"
#include <QTimer>
#include <QPixmap>
#include <QGraphicsScene>

bool TEST_VAR_BOOL = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Setup timer (for regular GUI visual updates) */
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateVisuals()) );
}

MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->cli;
    delete this->qdb;
    delete this->timer;
}

void MainWindow::updateVisuals(){

    //std::cerr << "OMG UPDATE CALLED" << std::endl;

    /* Update the visuals (graphics). */
    float* curPacket = (float*)this->cli->getDataPacket();

    this->ui->gView_FS_Roll->resetTransform();
    this->ui->gView_FS_Roll->rotate(curPacket[CUR_OR_ROLL] * 180.0/3.14);
    this->ui->lEdit_FS_RollText->setText(QString::number(curPacket[CUR_OR_ROLL], 'g', 2));

    this->ui->gView_FS_Pit->resetTransform();
    this->ui->gView_FS_Pit->rotate(-1*curPacket[CUR_OR_PITCH] * 180.0/3.14);
    this->ui->lEdit_FS_PitText->setText(QString::number(curPacket[CUR_OR_PITCH], 'g', 2));

    this->ui->gView_FS_Dir->resetTransform();
    this->ui->gView_FS_Dir->rotate(curPacket[CUR_OR_YAW] * 180.0/3.14);
    //this->ui->lEdit_FS_DirText->setText(QString::number(curPacket[CUR_OR_YAW],'g',2));

    /* Update the text. */
    ui->Sensor_Current_X->setText(QString::number(this->cli->getDataPacket()[CUR_POS_LON], 'g', 2));
    ui->Sensor_Current_Y->setText(QString::number(this->cli->getDataPacket()[CUR_POS_LAT], 'g', 2));
    ui->Sensor_Current_Z->setText(QString::number(this->cli->getDataPacket()[CUR_POS_ALT], 'g', 2));

    ui->Sensor_Target_X->setText(QString::number(this->cli->getDataPacket()[TARGET_POS_LON], 'g', 2));
    ui->Sensor_Target_Y->setText(QString::number(this->cli->getDataPacket()[TARGET_POS_LAT], 'g', 2));
    ui->Sensor_Target_Z->setText(QString::number(this->cli->getDataPacket()[TARGET_POS_ALT], 'g', 2));


}

void MainWindow::setupConsoleWindow(){
    this->qdb = new Q_DebugStream(std::cerr, this->ui->DebugConsole);
}

void MainWindow::setupIndicators(){

    /* Images */
    QPixmap dirImage = QPixmap::fromImage(QImage(":/direction.jpg",0));
    QPixmap rollImage = QPixmap::fromImage(QImage(":/roll.jpg",0));
    QPixmap pitchImage = QPixmap::fromImage(QImage(":/pitch.jpg",0));
//    QPixmap dirImage = QPixmap::fromImage(QImage("/Users/michael/Documents/workspace/MicroCART-F2013/BasicPrograms/GUI/Images/direction.jpg",0));
//    QPixmap rollImage = QPixmap::fromImage(QImage("/Users/michael/Documents/workspace/MicroCART-F2013/BasicPrograms/GUI/Images/roll.jpg",0));
//    QPixmap pitchImage = QPixmap::fromImage(QImage("/Users/michael/Documents/workspace/MicroCART-F2013/BasicPrograms/GUI/Images/pitch.jpg",0));
    QGraphicsScene *dirscene = new QGraphicsScene ();
    QGraphicsScene *rollscene = new QGraphicsScene();
    QGraphicsScene *pitchscene = new QGraphicsScene();
    dirscene->addPixmap(dirImage);
    rollscene->addPixmap(rollImage);
    pitchscene->addPixmap(pitchImage);
    // show pitch, roll and yaw images for the primary control (UAV)
    ui->gView_FS_Dir->setScene(dirscene);
    ui->gView_FS_Roll->setScene(rollscene);
    ui->gView_FS_Pit->setScene(pitchscene);

    /* Text, only if started. */
    ui->Sensor_Current_X->setText("0.0");
    ui->Sensor_Current_Y->setText("0.0");
    ui->Sensor_Current_Z->setText("0.0");

    ui->Sensor_Target_X->setText("0.0");
    ui->Sensor_Target_Y->setText("0.0");
    ui->Sensor_Target_Z->setText("0.0");
}

void MainWindow::setCLI(CLI* cli){
    this->cli = cli;
}

void MainWindow::on_startButton_clicked()
{
    if(!this->cli->is_started()){

        if(!this->cli->setupTransmitter(this->ui->Bluetooth_addr->text().toStdString())){
            return; /* Failed */
        }

        if(!this->cli->setupCamera(this->ui->Camera_ip_addr->text().toStdString())){
            return; /* Failed */
        }
        /* Now try to start. */
        if(this->cli->start()){
            ui->startButton->setText("STOP");
            this->timer->start(5);
        }
        else{
            return; /* CLI failed to start.. */
        }

    }
    else{
        this->cli->stop();
        this->ui->startButton->setText("START");
        this->timer->stop();
    }
}


void MainWindow::on_ManualThrottlespinBox_valueChanged(int arg1)
{
    if(this->ui->ManualThrottle_checkBox->isChecked()){
        std::stringstream ss;
        ss << "smanv " <<  arg1 << "\n";
        this->cli->passCommand(ss.str());
    }
}
/*
void MainWindow::on_AltitudeSpinbox_valueChanged(int arg1)
{
    std::stringstream ss;
    ss << "salt " <<  arg1/100.0 << "\n";
    this->cli->passCommand(ss.str());
}

void MainWindow::on_LatitudeSpinbox_valueChanged(int arg1)
{
    std::stringstream ss;
    ss << "slat " <<  arg1/100.0 << "\n";
    this->cli->passCommand(ss.str());
}

void MainWindow::on_LongitudeSpinbox_valueChanged(int arg1)
{
    std::stringstream ss;
    ss << "slon " <<  arg1/100.0 << "\n";
    this->cli->passCommand(ss.str());
}*/

void MainWindow::on_ManualThrottle_checkBox_toggled(bool checked)
{
    /* Checked */
    if(checked){
        std::stringstream ss;
        ss << "smanv " << ui->ManualThrottlespinBox->value() << "\n";
        this->cli->passCommand(ss.str());
        this->cli->passCommand("sman true");
    }

    /* Unchecked */
    else{
        this->cli->passCommand("sman false");
    }
}

void MainWindow::on_Execute_Button_clicked()
{
    if(this->cli->is_started()){
        std::cerr << "Manual Command passed: " << this->ui->ManualCommanLineEdit->text().toStdString() << "\n";
        this->cli->passCommand(this->ui->ManualCommanLineEdit->text().toStdString());
    }
    else{
        std::cerr << "Interface is not started, please start before passing manual commands.\n";
    }
}

void MainWindow::on_Apply_pushButton_clicked()
{
    std::stringstream ss;
    ss << "salt " <<  ui->AltitudeSpinbox->value()/100.0 << "\n";
    this->cli->passCommand(ss.str());
    ss.str("");
    ss << "slat " <<  ui->LatitudeSpinbox->value()/100.0 << "\n";
    this->cli->passCommand(ss.str());
    ss.str("");
    ss << "slon " <<  ui->LongitudeSpinbox->value()/100.0 << "\n";
    this->cli->passCommand(ss.str());
}


/**
 * @brief MainWindow::on_Auto_button_clicked
 * @param checked Auto button has been selected.
 *
 * Configures the CLI to no longer use the controller.
 */
void MainWindow::on_Auto_button_clicked(bool checked)
{
    if(checked){
        if(this->cli->usingController()){

            this->ui->ManualThrottle_checkBox->blockSignals(false);
            this->cli->setUsingController(false);

            if(this->cli->is_started()){
                std::cerr << "Auto control started!\n";
                this->cli->passCommand("sman false"); /* Auto mode re-enabled, put auto throttle back on */
                this->cli->stopController();
            }
        }
    }
}

/**
 * @brief MainWindow::on_Manual_button_clicked
 * @param checked Manual option has been selected.
 *
 * Configures the CLI to use the controller as primary input.
 *
 */
void MainWindow::on_Manual_button_clicked(bool checked)
{
    if(checked){
        if(!this->cli->usingController()){
            this->ui->ManualThrottle_checkBox->blockSignals(true);

            /* Start controller */
            this->cli->setUsingController(true);


            if(this->cli->is_started()){
                std::cerr << "Manual control started!\n";
                this->cli->passCommand("sman true"); /* Manual throttle needed in controller mode */
                this->cli->setupUSBController();
                this->cli->startController();
            }
        }
    }
}
