/***************************************************************************//**
 * @file example/MainWindow.h
 * @author  Marek M. Cel <marekcel@marekcel.pl>
 *
 * @section LICENSE
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * This file is part of QFlightInstruments. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTableWidget>
#include <qsensor.h>
#include <QPressureReading>
#include <QDateTime>
#include <QTableWidget>
#include <QTimer>
#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>
#include <QAccelerometer>
#include <QGyroscope>
#include <QChar>
#include <QFile>
#include <QtAndroid>
#include <math.h>
#include <kalmanfilter.h>
#include "BeepThread.h"

namespace Ui
{
    class MainWindow;
}

#define KF_VAR_ACCEL 0.0075 // Variance of pressure acceleration noise input.
#define KF_VAR_MEASUREMENT 0.05 // Variance of pressure measurement noise.
#define SEA_LEVEL_PRESSURE 101325.0 // Pressure at sea level (Pa)

#define SCREEN_ORIENTATION_LANDSCAPE 0
#define SCREEN_ORIENTATION_PORTRAIT 1
#define RADIANS_TO_DEGREES 57.2957795

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;   

private:   
    void fillVario();
    void fillStatus();
    void updateIGC();
    void createIgcHeader();    
    void startGps();
    void updatePFD();
    bool setScreenOrientation(int orientation);

    QString decimalToDDDMMMMMLat(qreal angle);
    QString decimalToDDDMMMMMLon(qreal angle);

public slots:
    void loadSensors();
    void position_changed(QGeoPositionInfo gpsPos);
    void gyroscope_changed();
    void pressure_changed();
    void accelerometer_changed();
    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos);
    void satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &infos);
    void on_pushButton_exit_clicked();
    void on_buttonStart_clicked();
    void on_pushButton_increase_clicked();
    void on_pushButton_decrease_clicked();
    void keyPressEvent(QKeyEvent *k);

private:      
    QGeoPositionInfoSource *m_posSource;
    QGeoPositionInfo m_gpsPos;
    QGeoCoordinate m_coord;
    QGeoCoordinate m_startCoord;

    BeepThread *mBeepThread;

    bool m_start;
    bool createIgcFile;

    QPressureSensor *sensorPress;
    QPressureReading *pressureReading;

    QAccelerometer *sensorAcc;
    QAccelerometerReading *accelerometerReading;

    QGyroscope *sensorGyr;
    QGyroscopeReading * gyroscopeReading;

    QString text_presssure;
    QDateTime p_start;
    QDateTime p_end;
    QDateTime a_start;
    QDateTime a_end;
    QDateTime g_start;
    QDateTime g_end;
    QTableWidget *tableSensor;
    QTableWidget *tableGps;

    KalmanFilter *pitch_filter;
    KalmanFilter *roll_filter;
    KalmanFilter *yaw_filter;
    KalmanFilter *slipskid_filter;
    KalmanFilter *turnrate_filter;
    KalmanFilter *pressure_filter;
    KalmanFilter *altitude_filter;
    qreal p_dt;
    qreal a_dt;
    qreal g_dt;
    qreal pressure;
    qreal temperature;
    qreal baroaltitude;
    qreal altitude;
    qreal vario;   
    qreal offset;
    qreal oldaltitude;
    QFile * igcFile;
    QAndroidJniObject mediaDir;
    QString currentTime;

    int tCount;

    qreal alpha             ;
    qreal beta              ;
    qreal roll              ;
    qreal pitch             ;
    qreal yaw               ;
    qreal heading           ;
    qreal slipSkid          ;
    qreal turnRate          ;
    qreal devH              ;
    qreal devV              ;
    qreal airspeed          ;
    qreal sensoralt         ;
    qreal sensorpressure    ;
    qreal climbRate         ;
    qreal machNo            ;
    qreal adf               ;
    qreal distance          ;

    quint64 lastPressTimestamp ;
    qreal pDeltaT ;

    quint64 lastAccTimestamp ;
    qreal aDeltaT ;

    quint64 lastGyroTimestamp;      ///< Most recent gyroscope measurement timestamp
    qreal gDeltaT;                  ///< Latest time slice for angular velocity
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
