#include "MCTUtilities.h"
#include "MCTStructures.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

bool cus_nancheck( double var ) {
    volatile double d = var;
    if( d != d) {
        std::cout << "NAN encountered" <<std::cout;
        return true;
    } else {
        return false;
    }
}

std::string GPS_TO_STRING(double coord, bool lat)
{
    char temp[80];
    int deg, min;
    double sec;
    deg = (int) coord;
    min = (int) ((coord-(double)deg) * 60);
    sec = ((((coord-(double)deg) * 60) - (double)min) *60);
    if(lat == false) {
        if(deg > 0)
            sprintf(temp,"N %dd%dm%.2fs", deg, min, sec);
        else
            sprintf(temp,"S %dd%dm%.2fs", deg, min, sec);
    } else {
        if(deg > 0 )
            sprintf(temp,"E %dd%dm%.2fs", deg, min, sec);
        else
            sprintf(temp,"W %dd%dm%.2fs", deg, min, sec);
    }
    return temp;
}

std::string DIST_FROM_GPS(double lat_a, double long_a, double lat_b, double long_b, bool lat)
{
    char temp[80];
    double x;
    if(lat_b == -1000) {
        sprintf(temp, "GPS N/A");
    } else {
        if(lat)
            x = DEG_TO_RAD(lat_b-lat_a);
        else
            x = DEG_TO_RAD(long_b-long_a) * cos(DEG_TO_RAD((lat_a+lat_b)/2));
        double dist = sqrt(x*x) * 6371000;

        sprintf(temp,"%.4fm",dist);
    }
    return temp;
}

int get_USB_port(std::string dev_id)
{
    FILE *fp;
    char line[80];
    char num[3];
    int ret = -1;
    std::string comm = "lsusb -d " + dev_id;
    fp = popen(comm.c_str(), "r");

    if(fgets(line, sizeof line, fp)) {
        num[0] = line[15];
        num[1] = line[16];
        num[2] = line[17];
        ret = atoi(num);
    }

    pclose(fp);
    return ret;
}

MCTUAV read_UAV_model(std::string filename)
{
    std::fstream profile (filename.c_str(), std::fstream::in);
    MCTUAV tmp;
    int fpos = 14;

    std::string line;

    getline(profile, line);
    tmp.roll.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.roll.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.roll.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.roll.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.roll.Kt = atof(line.substr(fpos).c_str());

    getline(profile, line);
    tmp.pitch.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.pitch.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.pitch.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.pitch.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.pitch.Kt = atof(line.substr(fpos).c_str());

    getline(profile, line);
    tmp.yaw.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.yaw.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.yaw.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.yaw.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.yaw.Kt = atof(line.substr(fpos).c_str());

    getline(profile, line);
    tmp.altitude.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.altitude.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.altitude.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.altitude.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.altitude.Kt = atof(line.substr(fpos).c_str());

    getline(profile, line);
    tmp.longitude.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.longitude.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.longitude.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.longitude.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.longitude.Kt = atof(line.substr(fpos).c_str());

    getline(profile, line);
    tmp.latitude.Kp = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.latitude.Ki = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.latitude.Kd = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.latitude.Kf = atof(line.substr(fpos).c_str());
    getline(profile, line);
    tmp.latitude.Kt = atof(line.substr(fpos).c_str());

    profile.close();

    return tmp;

}

void write_UAV_model(std::string filename, MCTUAV model)
{
    std::fstream profile (filename.c_str(), std::fstream::out);

    profile << "Roll KP:      " << model.roll.Kp << std::endl;
    profile << "Roll KI:      " << model.roll.Ki << std::endl;
    profile << "Roll KD:      " << model.roll.Kd << std::endl;
    profile << "Roll Kf:      " << model.roll.Kf << std::endl;
    profile << "Roll KT:      " << model.roll.Kt << std::endl;

    profile << "Pitch KP:     " << model.pitch.Kp << std::endl;
    profile << "Pitch KI:     " << model.pitch.Ki << std::endl;
    profile << "Pitch KD:     " << model.pitch.Kd << std::endl;
    profile << "Pitch Kf:     " << model.pitch.Kf << std::endl;
    profile << "Pitch KT:     " << model.pitch.Kt << std::endl;

    profile << "Yaw KP:       " << model.yaw.Kp << std::endl;
    profile << "Yaw KI:       " << model.yaw.Ki << std::endl;
    profile << "Yaw KD:       " << model.yaw.Kd << std::endl;
    profile << "Yaw Kf:       " << model.yaw.Kf << std::endl;
    profile << "Yaw KT:       " << model.yaw.Kt << std::endl;

    profile << "Altitude KP:  " << model.altitude.Kp << std::endl;
    profile << "Altitude KI:  " << model.altitude.Ki << std::endl;
    profile << "Altitude KD:  " << model.altitude.Kd << std::endl;
    profile << "Altitude Kf:  " << model.altitude.Kf << std::endl;
    profile << "Altitude KT:  " << model.altitude.Kt << std::endl;

    profile << "Longitude KP: " << model.longitude.Kp << std::endl;
    profile << "Longitude KI: " << model.longitude.Ki << std::endl;
    profile << "Longitude KD: " << model.longitude.Kd << std::endl;
    profile << "Longitude Kf: " << model.longitude.Kf << std::endl;
    profile << "Longitude KT: " << model.longitude.Kt << std::endl;

    profile << "Latitude KP:  " << model.latitude.Kp << std::endl;
    profile << "Latitude KI:  " << model.latitude.Ki << std::endl;
    profile << "Latitude KD:  " << model.latitude.Kd << std::endl;
    profile << "Latitude Kf:  " << model.latitude.Kf << std::endl;
    profile << "Latitude KT:  " << model.latitude.Kt << std::endl;

    profile.close();
}

void normalize_Orientation(MCTorientation *ori) {
    while( ori->pitch > 90 || ori->pitch < -90 ) {
        if( ori->pitch > 90) {
            ori->pitch -= 180;
        }
        if(ori->pitch < -90) {
            ori->pitch += 180;
        }
    }
    while( ori->roll > 90 || ori->roll < -90 ) {
        if( ori->roll > 90) {
            ori->roll -= 180;
        }
        if(ori->roll < -90) {
            ori->roll += 180;
        }
    }
}

double DEG_TO_RAD(double angle) {
    double temp = angle/180.0*PI;
    while( temp > PI || temp < -PI ) {
        if( temp > PI) {
            temp -= PI;
        }
        if(temp < -PI) {
            temp += PI;
        }
    }
    return temp;
}

double RAD_TO_DEG(double angle) {
    double temp = angle/PI*180.0;
    while( temp > 180.0 || temp < -180.0 ) {
        if( temp > 180) {
            temp -= 180;
        }
        if(temp < -180) {
            temp += 180;
        }
    }
    return temp;
}

void setZero(MCTPIDERR *pid) {
    pid->preverr=0;
    pid->err = 0;
    pid->prevD = 0;
    pid->prevI = 0;
    //problems with include <ctime>
    //clock_gettime(CLOCK_REALTIME, &(pid->mark));
}


