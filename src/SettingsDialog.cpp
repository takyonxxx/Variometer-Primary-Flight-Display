<<<<<<< HEAD
#include <QtGui>
#include<QDebug>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QObject::connect(this, SIGNAL(finished (int)), this, SLOT(dialogIsFinished(int)));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labelGpsPower = new QLabel(tr(" Gps Power : "));
    labelGpsInterval = new QLabel(tr(" Gps Interval : "));

    gpsPowerComboBox = createComboBox(tr("High"));
    gpsPowerComboBox->addItem(QString("High"));
    gpsPowerComboBox->addItem(QString("Medium"));
    gpsPowerComboBox->addItem(QString("Low"));
    gpsPowerComboBox->setEditable(false);
    connect(gpsPowerComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
        [=](const QString &text){ gpsPowerChanged(text); });

    gpsIntervalComboBox = createComboBox(tr("1"));
    gpsIntervalComboBox->addItem(QString("1"));
    gpsIntervalComboBox->addItem(QString("3"));
    gpsIntervalComboBox->addItem(QString("5"));
    gpsIntervalComboBox->setEditable(false);
    connect(gpsIntervalComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
        [=](const QString &text){ gpsIntervalChanged(text); });

    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    //QObject::connect(rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(okButton, QDialogButtonBox::ActionRole);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(labelGpsPower, 0, 0);
    mainLayout->addWidget(gpsPowerComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(labelGpsInterval, 1, 0);
    mainLayout->addWidget(gpsIntervalComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(buttonBox, 2, 2);
    mainLayout->setRowStretch(2, 1);
    setLayout(mainLayout);
    setWindowTitle(tr("Settings"));
}

void SettingsDialog::dialogIsFinished(int result)
{
   if(result == QDialog::Accepted)
   {
       return;
   }
}

QComboBox *SettingsDialog::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return comboBox;
}
=======
#include <QtGui>
#include<QDebug>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    QObject::connect(this, SIGNAL(finished (int)), this, SLOT(dialogIsFinished(int)));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    labelGpsPower = new QLabel(tr(" Gps Power : "));
    labelGpsInterval = new QLabel(tr(" Gps Interval : "));

    gpsPowerComboBox = createComboBox(tr("*"));
    gpsPowerComboBox->addItem(QString("High"));
    gpsPowerComboBox->addItem(QString("Medium"));
    gpsPowerComboBox->addItem(QString("Low"));
    gpsPowerComboBox->setEditable(false);
    connect(gpsPowerComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
        [=](const QString &text){ gpsPowerChanged(text); });

    gpsIntervalComboBox = createComboBox(tr("*"));
    gpsIntervalComboBox->addItem(QString("1"));
    gpsIntervalComboBox->addItem(QString("3"));
    gpsIntervalComboBox->addItem(QString("5"));
    gpsIntervalComboBox->setEditable(false);
    connect(gpsIntervalComboBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
        [=](const QString &text){ gpsIntervalChanged(text); });

    okButton = new QPushButton(tr("&Ok"));
    okButton->setDefault(true);
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    //QObject::connect(rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(okButton, QDialogButtonBox::ActionRole);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(labelGpsPower, 0, 0);
    mainLayout->addWidget(gpsPowerComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(labelGpsInterval, 1, 0);
    mainLayout->addWidget(gpsIntervalComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(buttonBox, 2, 2);
    mainLayout->setRowStretch(2, 1);
    setLayout(mainLayout);
    setWindowTitle(tr("Settings"));
}

void SettingsDialog::dialogIsFinished(int result)
{
   if(result == QDialog::Accepted)
   {
       return;
   }
}

QComboBox *SettingsDialog::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return comboBox;
}
>>>>>>> 21491701d214685c2f64806df2193c14a5320ca8
