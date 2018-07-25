#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = 0);

private:
    QLabel *labelGpsPower;
    QLabel *labelGpsInterval;
    QPushButton *okButton;
    QComboBox *createComboBox(const QString &text = QString());
    QComboBox *gpsPowerComboBox;
    QComboBox *gpsIntervalComboBox;

private slots:   
    void dialogIsFinished(int result);

signals:
     void gpsPowerChanged(const QString&);
     void gpsIntervalChanged(const QString&);
};

#endif // SETTINGSDIALOG_H

