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
#include <QDialog>
#include <math.h>
#include <kalmanfilter.h>
#include "BeepThread.h"
#include "SettingsDialog.h";

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

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    bool IsNan( float value )
    {
        return ((*(uint*)&value) & 0x7fffffff) > 0x7f800000;
    }

    void keep_screen_on(bool on) {
      QtAndroid::runOnAndroidThread([on]{
        QAndroidJniObject activity = QtAndroid::androidActivity();
        if (activity.isValid()) {
          QAndroidJniObject window =
              activity.callObjectMethod("getWindow", "()Landroid/view/Window;");

          if (window.isValid()) {
            const int FLAG_KEEP_SCREEN_ON = 128;
            if (on) {
              window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            } else {
              window.callMethod<void>("clearFlags", "(I)V", FLAG_KEEP_SCREEN_ON);
            }
          }
        }
        QAndroidJniEnvironment env;
        if (env->ExceptionCheck()) {
          env->ExceptionClear();
        }
      });
    }

    bool requestFineLocationPermission()
    {
        QtAndroid::PermissionResult request = QtAndroid::checkPermission("android.permission.ACCESS_FINE_LOCATION");
        if (request == QtAndroid::PermissionResult::Denied){
            QtAndroid::requestPermissionsSync(QStringList() <<  "android.permission.ACCESS_FINE_LOCATION");
            request = QtAndroid::checkPermission("android.permission.ACCESS_FINE_LOCATION");
            if (request == QtAndroid::PermissionResult::Denied)
            {
                qDebug() << "FineLocation Permission denied";
                return false;
            }
        }
        qDebug() << "FineLocation Permissions granted!";
        return true;
    }

    bool requestStorageWritePermission() {
        QtAndroid::PermissionResult request = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
        if(request == QtAndroid::PermissionResult::Denied) {
            QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
            request = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
            if(request == QtAndroid::PermissionResult::Denied)
            {
                qDebug() << "StorageWrite Permission denied";
                return false;
            }
        }
        qDebug() << "StorageWrite Permissions granted!";
        return true;
    }

    
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
    void keyPressEvent(QKeyEvent *k);
    void settingsDialog();
    void onChangedGpsPower(const QString & item);
    void onChangedGpsInterval(const QString & text);

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_exit_clicked();
    void on_pushButton_increase_clicked();
    void on_pushButton_decrease_clicked();

private:
    QGeoPositionInfoSource *m_posSource;
    QGeoPositionInfo m_gpsPos;
    QGeoCoordinate m_coord;
    QGeoCoordinate m_startCoord;
    QGeoPositionInfoSource::PositioningMethod m_gpsMode;
    int m_gpsInterval;
    BeepThread *m_beepThread;

    bool m_start;
    bool createIgcFile;
    bool m_sensorPressureValid;

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
    qreal groundspeed          ;
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
