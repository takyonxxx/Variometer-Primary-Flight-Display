#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

using namespace std;
const QChar degreeChar(0260);

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow )
{   
    ui->setupUi( this );

    if (!requestFineLocationPermission())
            qApp->quit();
    if (!requestStorageWritePermission())
            qApp->quit();

    //create menubar
    QMenuBar *menuBar=new QMenuBar(this);
    QMenu *menu=new QMenu(tr("Menu"),this);
    QAction *action  =new QAction(tr("Settings"),this);
    connect(action,SIGNAL(triggered()),this,SLOT( settingsDialog()));
    menu->addAction(action);
    menuBar->addMenu(menu);
    setMenuBar(menuBar);

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#A4A4A4"));
    this->setPalette(pal);

    setScreenOrientation(SCREEN_ORIENTATION_PORTRAIT);
    m_start = false;
    createIgcFile = false;
    m_sensorPressureValid = false;

    ui->label_vario->setStyleSheet("font-size: 12pt; color: #cccccc; background-color: #001a1a;");
    ui->label_status->setStyleSheet("font-size: 12pt; color: white; background-color: #001a1a;");
    ui->label_log->setStyleSheet("font-size: 12pt; color: white; background-color: #001a1a;");
    ui->label_offset->setStyleSheet("font-size: 12pt; color: white; background-color: #001a1a;");
    ui->label_offset->setText("Offset : " + QString::number(0) + QString(" %1").arg(degreeChar));   

    tCount             = 0;
    pressure           = 101325.0;
    altitude           = 0;
    oldaltitude        = 0;
    alpha              = 0;
    beta               = 0;
    roll               = 0;
    pitch              = 0;
    yaw                = 0;
    heading            = 0;
    slipSkid           = 0;
    turnRate           = 0;
    devH               = 0;
    devV               = 0;
    groundspeed        = 0;
    sensoralt          = 0;
    sensorpressure     = 0;
    climbRate          = 0;
    machNo             = 0;
    adf                = 0;
    distance           = 0;
    offset             = 0;
    lastPressTimestamp = 0;
    pDeltaT            = 0;
    lastAccTimestamp   = 0;
    aDeltaT            = 0;
    lastGyroTimestamp  = 0;
    gDeltaT            = 0;

    m_gpsMode = QGeoPositionInfoSource::SatellitePositioningMethods;
    m_gpsInterval = 1000;

    mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");

    QDir dir(mediaDir.toString() + "/VarioLog");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    m_beepThread = new BeepThread(this);
    m_beepThread->setVolume(100.);
    m_beepThread->startBeep();
    m_beepThread->start();

    loadSensors();    
}

MainWindow::~MainWindow()
{
    if ( ui ) delete ui; ui = 0;
}

void MainWindow::settingsDialog()
{
    SettingsDialog *settingsDialog = new SettingsDialog(this);
    connect(settingsDialog, SIGNAL(gpsPowerChanged(QString)),
                   this, SLOT(onChangedGpsPower(const QString &)));
    connect(settingsDialog, SIGNAL(gpsIntervalChanged(QString)),
                   this, SLOT(onChangedGpsInterval(const QString &)));

    QString gPower;
    QString gInterval;

    if(m_gpsMode == QGeoPositionInfoSource::AllPositioningMethods)
        gPower = QString("High");
    else if(m_gpsMode == QGeoPositionInfoSource::SatellitePositioningMethods)
        gPower = QString("Medium");
    else if(m_gpsMode == QGeoPositionInfoSource::NonSatellitePositioningMethods)
        gPower = QString("Low");

    settingsDialog->setCurrentGpsPower(gPower);

    if(m_gpsInterval == 1000)
        gInterval = QString("1");
    else if(m_gpsInterval == 3000)
        gInterval = QString("3");
    else if(m_gpsInterval == 5000)
        gInterval = QString("5");

    settingsDialog->setCurrentGpsInterval(gInterval);
    settingsDialog->init();
    settingsDialog->exec();
}

void MainWindow::onChangedGpsPower(const QString & text)
{
    if(text == QString("High"))
        m_gpsMode = QGeoPositionInfoSource::AllPositioningMethods;
    else if(text == QString("Medium"))
        m_gpsMode = QGeoPositionInfoSource::SatellitePositioningMethods;
    else if(text == QString("Low"))
        m_gpsMode = QGeoPositionInfoSource::NonSatellitePositioningMethods;

    if ( ui->pushButton_start->text() == "Stop Gps")
    {
        m_posSource->stopUpdates();
        m_posSource->setPreferredPositioningMethods(m_gpsMode);
        m_posSource->startUpdates();
    }
    else
    {
        m_posSource->setPreferredPositioningMethods(m_gpsMode);
    }
}

void MainWindow::onChangedGpsInterval(const QString & text)
{
    if(text == QString("1"))
        m_gpsInterval = 1000;
    else if(text == QString("3"))
        m_gpsInterval = 3000;
    else if(text == QString("5"))
        m_gpsInterval = 5000;

    if ( ui->pushButton_start->text() == "Stop Gps")
    {
        m_posSource->stopUpdates();
        m_posSource->setUpdateInterval(m_gpsInterval);
        m_posSource->startUpdates();
    }
    else
    {
         m_posSource->setUpdateInterval(m_gpsInterval);
    }
}

bool MainWindow::setScreenOrientation(int orientation)
{
    QAndroidJniObject activity = QtAndroid::androidActivity();

    if(activity.isValid())
    {
        activity.callMethod<void>("setRequestedOrientation", "(I)V", orientation);
        keep_screen_on(true);
        return true;
    }
    return false;
}

void MainWindow::loadSensors()
{
    QString status;
    status.append("Searching sensors.");
    status.append("\n");

    foreach (const QByteArray &type, QSensor::sensorTypes()) {
        foreach (const QByteArray &identifier, QSensor::sensorsForType(type)) {
            // Don't put in sensors we can't connect to
            QSensor sensor(type);
            sensor.setIdentifier(identifier);
            if (!sensor.connectToBackend()) {
                 status.append("Couldn't connect to " + identifier + "\n");
                continue;
            }

            QString sensor_type = type;
            if(sensor_type.contains("Pressure"))
            {
                m_sensorPressureValid = true;

                sensorPress = new QPressureSensor(this);
                connect(sensorPress, SIGNAL(readingChanged()), this, SLOT(pressure_changed()));
                sensorPress->setIdentifier(identifier);

                if (!sensorPress->connectToBackend()) {
                    status.append("Can't connect to Backend sensor: " + sensor_type + "\n");
                    delete sensorPress;
                    sensorPress = 0;
                    return;
                }

                if(sensorPress->start())
                {
                     status.append(sensor_type + " started succesfully.\n");
                     p_start = QDateTime::currentDateTime();
                     pressure_filter = new KalmanFilter(KF_VAR_ACCEL);
                     pressure_filter->Reset(pressure);
                     altitude_filter = new KalmanFilter(KF_VAR_ACCEL);
                     altitude_filter->Reset(altitude);
                }
            }
            else if(sensor_type.contains("Accelerometer"))
            {
                sensorAcc = new QAccelerometer(this);
                connect(sensorAcc, SIGNAL(readingChanged()), this, SLOT(accelerometer_changed()));
                sensorAcc->setIdentifier(identifier);

                if (!sensorAcc->connectToBackend()) {
                    status.append("Can't connect to Backend sensor: " + sensor_type + "\n");
                    delete sensorAcc;
                    sensorAcc = 0;
                    return;
                }

                if(sensorAcc->start())
                {
                     status.append(sensor_type + " started succesfully.\n");
                     a_start = QDateTime::currentDateTime();
                     yaw_filter = new KalmanFilter(KF_VAR_ACCEL);
                     yaw_filter->Reset(yaw);
                     pitch_filter = new KalmanFilter(KF_VAR_ACCEL);
                     pitch_filter->Reset(pitch);
                     roll_filter = new KalmanFilter(KF_VAR_ACCEL);
                     roll_filter->Reset(roll);
                }
            }
            else if(sensor_type.contains("Gyroscope"))
            {
                sensorGyr = new QGyroscope(this);
                connect(sensorGyr, SIGNAL(readingChanged()), this, SLOT(gyroscope_changed()));
                sensorGyr->setIdentifier(identifier);

                if (!sensorGyr->connectToBackend()) {
                    status.append("Can't connect to Backend sensor: " + sensor_type + "\n");
                    delete sensorGyr;
                    sensorGyr = 0;
                    return;
                }

                if(sensorGyr->start())
                {
                     status.append(sensor_type + " started succesfully.\n");
                     g_start = QDateTime::currentDateTime();
                     slipskid_filter = new KalmanFilter(KF_VAR_ACCEL);
                     slipskid_filter->Reset(slipSkid);
                     turnrate_filter = new KalmanFilter(KF_VAR_ACCEL);
                     turnrate_filter->Reset(turnRate);
                }
            }
        }
    }

    startGps();
    ui->label_status->setText(status);
}

void MainWindow::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos)
{
    foreach (const QGeoSatelliteInfo &info, infos)
    {
        ui->label_log->setText("InView " + info.satelliteIdentifier());
    }
}

void MainWindow::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &infos)
{
    foreach (const QGeoSatelliteInfo &info, infos)
    {
        ui->label_log->setText("InUse " + info.satelliteIdentifier());
    }
}

void MainWindow::startGps()
{   
    m_posSource = QGeoPositionInfoSource::createDefaultSource(this);
    if (m_posSource)
    {
        m_posSource->setPreferredPositioningMethods(m_gpsMode);
        m_posSource->setUpdateInterval(m_gpsInterval);

        connect(m_posSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(position_changed(QGeoPositionInfo)));

    }
   else
        qFatal("No Position Source created!");
}

void MainWindow::fillStatus()
{
    QString status;   

    status.append("<span style='font-size:32pt; font-weight:600; color:#00cccc;'>"
                  + QString::number(altitude, 'f', 0)
                  + "</span><span style='font-size:24pt; font-weight:600; color:#00cccc;'> m</span>");

    if(m_gpsPos.isValid())
    status.append("<span style='font-size:32pt; font-weight:600; color:#00cccc;'> - "
                  + QString::number(groundspeed, 'f', 0)
                  + "</span><span style='font-size:24pt; font-weight:600; color:#00cccc;'> km/h</span>");

    ui->label_status->setText(status);
}

void MainWindow::fillVario()
{
    ui->label_vario->setText(
                "<span style='font-size:76pt; font-weight:600;'>"
               + QString::number(vario, 'f', 1) +"</span>"
               + "<span style='font-size:36pt; font-weight:600; color:#00cccc;'> m/s</span>"
               );

}

void MainWindow::updateIGC()
{
    if(!createIgcFile)
    {       
        QString sdate = QDate::currentDate().toString("ddMMyy");
        QString stime = QTime::currentTime().toString("hhmmss");
        igcFile = new QFile(mediaDir.toString() + "/VarioLog/" + sdate + "-" + stime +"_flightlog.igc");
        createIgcHeader();
        createIgcFile = true;
        tCount = 0;
    }

    QDateTime timestamp = m_gpsPos.timestamp();
    //QDateTime local = timestamp.toLocalTime();
    QString dateTimeString = timestamp.toString("hhmmss");

    igcFile->open(QIODevice::Append | QIODevice::Text);

    if(!igcFile->isOpen()){
       qDebug() << "- Error, unable to open" << "outputFilename" << "for output";
    }

    QTextStream out(igcFile);
    QString str;

    //B,110135,5206343N,00006198W,A,00587,00558

        QString record  = "B";

        record.append(dateTimeString);
        record.append(decimalToDDDMMMMMLat(m_coord.latitude()));
        record.append(decimalToDDDMMMMMLon(m_coord.longitude()));
        record.append("A");
        str.sprintf("%05d",(int)m_coord.altitude());
        record.append(str);
        str.sprintf("%05d",(int)altitude);
        record.append(str);
        out << record << endl;        
        tCount++;
        ui->label_log->setText(
                    "<span style='font-size:16pt; font-weight:600;'> Track : "
                   + QString::number(tCount) +"</span>"
                   );

    igcFile->close();
}

void MainWindow::createIgcHeader()
{
    igcFile->open(QIODevice::Append | QIODevice::Text);

    if(!igcFile->isOpen()){
       qDebug() << "- Error, unable to open" << "outputFilename" << "for output";
    }

    QFileInfo fileInfo(igcFile->fileName());
    qDebug() << "igc file path: " << fileInfo.absoluteFilePath();

    QTextStream out(igcFile);

    QDateTime timestamp = m_gpsPos.timestamp();
    QString dateString = timestamp.toString("ddMMyy");

    QString header  = "AXGD000 XcVario v1.0\n";
    header.append("HFDTE" + dateString + "\n");
    header.append("HODTM100GPSDATUM: WGS-84\n");
    header.append("HFFTYFRTYPE: XcVario by Türkay Biliyor");
    out << header << endl;
    igcFile->close();
}

QString MainWindow::decimalToDDDMMMMMLat(qreal angle)
{
        QString output, strdegree, strminutes, hemisphere;

        if (angle < 0) {
            angle = -1 * angle;
            hemisphere = "S";
        } else {
            hemisphere = "N";
        }

        int degree = (int) angle;
        double minutes = (angle - (qreal)degree) * 60.;
        strdegree.sprintf("%02d",(int)degree);
        strminutes.sprintf("%2.3f",minutes);
        output = strdegree + strminutes.remove(".") + hemisphere;

        //int seconds = (int)(angle - (float)degree - (float)minutes/60.f) * 60.f * 60.f); // ignore this line if you don't need seconds
        return output;
}

QString MainWindow::decimalToDDDMMMMMLon(qreal angle)
{
         QString output, strdegree, strminutes, hemisphere;

        if (angle < 0) {
            angle = -1 * angle;
            hemisphere = "W";
        } else {
            hemisphere = "E";
        }

        int degree = (int) angle;
        double minutes = (angle - (qreal)degree) * 60.;
        strdegree.sprintf("%03d",(int)degree);
        strminutes.sprintf("%2.3f",minutes);
        output = strdegree + strminutes.remove(".") + hemisphere;

        //int seconds = (int)(angle - (float)degree - (float)minutes/60.f) * 60.f * 60.f); // ignore this line if you don't need seconds
        return output;
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if( k->key() == Qt::Key_MediaPrevious )
    {
       return;
    }
}

void MainWindow::position_changed(QGeoPositionInfo gpsPos)
{
    m_gpsPos = gpsPos;

    if(m_gpsPos.isValid())
    {
        m_coord = gpsPos.coordinate();
        if(!m_start)
        {
            m_startCoord = gpsPos.coordinate();
            m_start = true;
        }

        if(m_start)
        {
            distance = m_coord.distanceTo(m_startCoord);
        }

        groundspeed = 3.6 * m_gpsPos.attribute(QGeoPositionInfo::GroundSpeed);
        if(IsNan((float)groundspeed)) groundspeed = 0;

        heading = m_gpsPos.attribute(QGeoPositionInfo::Direction);
        if(IsNan((float)heading))  heading = 0;
        
        altitude = m_coord.altitude();
        if(IsNan((float)altitude))  altitude = 0;

        if(!m_sensorPressureValid)
        fillStatus();

        updateIGC();
    }
}

void MainWindow::pressure_changed()
{
    quint64 timestamp = sensorPress->reading()->timestamp();

    if(lastGyroTimestamp > 0)
    {
        pDeltaT = ((qreal)(timestamp - lastPressTimestamp))/1000000.0f;
        if(pDeltaT > 0)
        {
            pressureReading = sensorPress->reading();
            p_end = QDateTime::currentDateTime();
            p_dt = p_start.msecsTo(p_end) / 1000.;

            if(pressureReading != 0 && p_dt > 0)
            {
                pressure = pressureReading->pressure();
                //sensorpressure = pressure * 0.000145037738; //per square inch
                temperature = pressureReading->temperature();
                pressure_filter->Update(pressure, KF_VAR_MEASUREMENT, p_dt);
                pressure = pressure_filter->GetXAbs();
                sensorpressure = pressure * 0.01; //hpa

                baroaltitude = 44330.0 * (1.0 - powf(pressure /SEA_LEVEL_PRESSURE, 0.19));
                altitude_filter->Update(baroaltitude, KF_VAR_MEASUREMENT, p_dt);
                altitude = altitude_filter->GetXAbs();
                sensoralt = altitude;
                vario = altitude_filter->GetXVel();
                climbRate = vario ;

                if(m_beepThread)
                    m_beepThread->SetVario(vario, p_dt);

                fillVario();
                fillStatus();
                oldaltitude = altitude;
                p_start = p_end;
            }
        }
    }
    lastPressTimestamp = timestamp;
}

void MainWindow::gyroscope_changed()
{   
    quint64 timestamp = sensorGyr->reading()->timestamp();

    if(lastGyroTimestamp > 0)
    {
        gDeltaT = ((qreal)(timestamp - lastGyroTimestamp))/1000000.0f;
        if(gDeltaT > 0)
        {
            gyroscopeReading = sensorGyr->reading();
            g_end = QDateTime::currentDateTime();
            g_dt = g_start.msecsTo(g_end) / 1000.;

            if(gyroscopeReading != 0 && g_dt > 0)
            {
                //qreal x = qDegreesToRadians(gyroscopeReading->property("x").value<qreal>());
                qreal y = qDegreesToRadians(gyroscopeReading->property("y").value<qreal>());
                qreal z = qDegreesToRadians(gyroscopeReading->property("z").value<qreal>());

                slipskid_filter->Update(z, KF_VAR_MEASUREMENT, g_dt);
                slipSkid = slipskid_filter->GetXAbs();

                turnrate_filter->Update(y, KF_VAR_MEASUREMENT, g_dt);
                turnRate = turnrate_filter->GetXAbs();

                g_start = g_end;
            }
        }
    }
    lastGyroTimestamp = timestamp;
}

void MainWindow::accelerometer_changed()
{
    quint64 timestamp = sensorAcc->reading()->timestamp();

    if(lastAccTimestamp > 0)
    {
       aDeltaT = ((qreal)(timestamp - lastAccTimestamp))/1000000.0f;
       if(aDeltaT > 0)
       {
           accelerometerReading = sensorAcc->reading();
           a_end = QDateTime::currentDateTime();
           a_dt = a_start.msecsTo(a_end) / 1000.;

           if(accelerometerReading != 0 && a_dt > 0)
           {
               qreal x = accelerometerReading->property("x").value<qreal>();
               qreal y  =accelerometerReading->property("y").value<qreal>();
               qreal z = accelerometerReading->property("z").value<qreal>();

               pitch = qAtan(y / qSqrt(x * x + z * z)) * RADIANS_TO_DEGREES;
               roll =  qAtan(x / qSqrt(y * y + z * z)) * RADIANS_TO_DEGREES;
               yaw  =  qAtan(z / qSqrt(y * y + x * x)) * RADIANS_TO_DEGREES;

               qreal theta = qAtan(qSqrt(x * x + z * z) / y) * RADIANS_TO_DEGREES;
               if (theta < 0)
               {
                      if (yaw > 0)
                          yaw = 180 - yaw;
                      else
                          yaw = -180 - yaw;
               }

               yaw_filter->Update(yaw,KF_VAR_MEASUREMENT,a_dt);
               yaw = yaw_filter->GetXAbs();

               roll_filter->Update(roll,KF_VAR_MEASUREMENT,a_dt);
               roll = roll_filter->GetXAbs();

               pitch_filter->Update(pitch,KF_VAR_MEASUREMENT,a_dt);
               pitch = pitch_filter->GetXAbs();

               pitch = -1 * yaw;
               roll = -1 * roll;

               updatePFD();
               a_start = a_end;
           }
       }
    }
    lastAccTimestamp = timestamp;
}

void MainWindow::updatePFD()
{
    machNo = groundspeed /60.;

    ui->widgetPFD->setFlightPathMarker  ( alpha, beta    );
    ui->widgetPFD->setRoll              ( roll           );
    ui->widgetPFD->setPitch             ( pitch + offset );
    ui->widgetPFD->setSlipSkid          ( slipSkid       );
    ui->widgetPFD->setTurnRate          ( turnRate       );
    ui->widgetPFD->setDevH              ( devH           );
    ui->widgetPFD->setDevV              ( devV           );
    ui->widgetPFD->setHeading           ( heading        );
    ui->widgetPFD->setAirspeed          ( groundspeed    );
    ui->widgetPFD->setMachNo            ( machNo         );
    ui->widgetPFD->setAltitude          ( sensoralt      );
    ui->widgetPFD->setPressure          ( sensorpressure );//hPa
    ui->widgetPFD->setClimbRate         ( climbRate      ) ;
    ui->widgetPFD->setIdentifier        ( "Dist (km)" , true );
    ui->widgetPFD->setDistance          ( QString::number(distance / 1000., 'f', 1).toDouble() , true );

    ui->widgetPFD->update();    
}


void MainWindow::on_pushButton_start_clicked()
{if ( ui->pushButton_start->text() == "Start Gps")
    {
        if (m_posSource)
        {
            createIgcFile = false;
            m_posSource->startUpdates();
           /* m_beepThread->startBeep();
            m_beepThread->start();*/
            ui->label_log->setText("Waiting Gps");
        }
        ui->pushButton_start->setText("Stop Gps");
    }
    else if ( ui->pushButton_start->text() == "Stop Gps")
    {
        QMessageBox msgBox;
        msgBox.setText(" Logging will stop.");
        msgBox.setInformativeText(" Do you want to exit?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Ok:
              if (m_posSource)
              {
                  m_posSource->stopUpdates();
                 // m_beepThread->stopBeep();
                  ui->label_log->setText("Logging Off");
              }
              ui->pushButton_start->setText("Start Gps");
              break;
          default:
              // should never be reached
              break;
        }
    }

}

void MainWindow::on_pushButton_increase_clicked()
{

    offset = offset - 5;
    ui->label_offset->setText("Offset : " + QString::number( offset) + QString(" %1").arg(degreeChar));
}

void MainWindow::on_pushButton_decrease_clicked()
{
    offset = offset + 5;
    ui->label_offset->setText("Offset : " + QString::number( offset) + QString(" %1").arg(degreeChar));
}


void MainWindow::on_pushButton_exit_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(" Warning.");
    msgBox.setInformativeText(" Do you want to exit?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
          if(m_beepThread)
          {
              m_beepThread->stopBeep();
          }
          exit(0);
          break;
      default:
          // should never be reached
          break;
    }
}
