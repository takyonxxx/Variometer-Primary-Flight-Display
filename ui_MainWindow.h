/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "WidgetNAV.h"
#include "WidgetPFD.h"
#include "WidgetSix.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QSplitter *splitter;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_8;
    QDoubleSpinBox *spinBoxPitch;
    QLabel *label_9;
    QDoubleSpinBox *spinBoxClimb;
    QLabel *label_13;
    QDoubleSpinBox *spinBoxSlip;
    QDoubleSpinBox *spinBoxPress;
    QDoubleSpinBox *spinBoxDevV;
    QDoubleSpinBox *spinBoxRoll;
    QLabel *label_10;
    QDoubleSpinBox *spinBoxSpeed;
    QDoubleSpinBox *spinBoxBeta;
    QLabel *label_3;
    QPushButton *pushButtonAuto;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_15;
    QDoubleSpinBox *spinBoxHead;
    QLabel *label;
    QDoubleSpinBox *spinBoxTurn;
    QLabel *label_7;
    QLabel *label_4;
    QFrame *line;
    QDoubleSpinBox *spinBoxMach;
    QLabel *label_2;
    QDoubleSpinBox *spinBoxAlpha;
    QDoubleSpinBox *spinBoxDevH;
    QDoubleSpinBox *spinBoxADF;
    QLabel *label_12;
    QDoubleSpinBox *spinBoxAlt;
    QLabel *label_14;
    QLabel *label_16;
    QDoubleSpinBox *spinBoxDME;
    QFrame *frame_2;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    WidgetSix *widgetSix;
    WidgetPFD *widgetPFD;
    WidgetNAV *widgetNAV;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(16777215, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 9, 0, 1, 1);

        spinBoxPitch = new QDoubleSpinBox(frame);
        spinBoxPitch->setObjectName(QStringLiteral("spinBoxPitch"));
        spinBoxPitch->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPitch->setMinimum(-90);
        spinBoxPitch->setMaximum(90);

        gridLayout->addWidget(spinBoxPitch, 3, 1, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 11, 0, 1, 1);

        spinBoxClimb = new QDoubleSpinBox(frame);
        spinBoxClimb->setObjectName(QStringLiteral("spinBoxClimb"));
        spinBoxClimb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxClimb->setMinimum(-650);
        spinBoxClimb->setMaximum(650);
        spinBoxClimb->setSingleStep(5);

        gridLayout->addWidget(spinBoxClimb, 13, 1, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 0, 0, 1, 1);

        spinBoxSlip = new QDoubleSpinBox(frame);
        spinBoxSlip->setObjectName(QStringLiteral("spinBoxSlip"));
        spinBoxSlip->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSlip->setMinimum(-1);
        spinBoxSlip->setMaximum(1);
        spinBoxSlip->setSingleStep(0.05);

        gridLayout->addWidget(spinBoxSlip, 5, 1, 1, 1);

        spinBoxPress = new QDoubleSpinBox(frame);
        spinBoxPress->setObjectName(QStringLiteral("spinBoxPress"));
        spinBoxPress->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxPress->setMinimum(28);
        spinBoxPress->setMaximum(31.5);

        gridLayout->addWidget(spinBoxPress, 12, 1, 1, 1);

        spinBoxDevV = new QDoubleSpinBox(frame);
        spinBoxDevV->setObjectName(QStringLiteral("spinBoxDevV"));
        spinBoxDevV->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxDevV->setMinimum(-1);
        spinBoxDevV->setMaximum(1);
        spinBoxDevV->setSingleStep(0.05);

        gridLayout->addWidget(spinBoxDevV, 8, 1, 1, 1);

        spinBoxRoll = new QDoubleSpinBox(frame);
        spinBoxRoll->setObjectName(QStringLiteral("spinBoxRoll"));
        spinBoxRoll->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxRoll->setMinimum(-180);
        spinBoxRoll->setMaximum(180);

        gridLayout->addWidget(spinBoxRoll, 2, 1, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 13, 0, 1, 1);

        spinBoxSpeed = new QDoubleSpinBox(frame);
        spinBoxSpeed->setObjectName(QStringLiteral("spinBoxSpeed"));
        spinBoxSpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxSpeed->setMaximum(9999);

        gridLayout->addWidget(spinBoxSpeed, 9, 1, 1, 1);

        spinBoxBeta = new QDoubleSpinBox(frame);
        spinBoxBeta->setObjectName(QStringLiteral("spinBoxBeta"));
        spinBoxBeta->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxBeta->setMinimum(-15);
        spinBoxBeta->setMaximum(15);

        gridLayout->addWidget(spinBoxBeta, 1, 1, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        pushButtonAuto = new QPushButton(frame);
        pushButtonAuto->setObjectName(QStringLiteral("pushButtonAuto"));
        pushButtonAuto->setCheckable(true);

        gridLayout->addWidget(pushButtonAuto, 17, 0, 1, 3);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 10, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        label_15 = new QLabel(frame);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 14, 0, 1, 1);

        spinBoxHead = new QDoubleSpinBox(frame);
        spinBoxHead->setObjectName(QStringLiteral("spinBoxHead"));
        spinBoxHead->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxHead->setMinimum(-360);
        spinBoxHead->setMaximum(360);

        gridLayout->addWidget(spinBoxHead, 4, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        spinBoxTurn = new QDoubleSpinBox(frame);
        spinBoxTurn->setObjectName(QStringLiteral("spinBoxTurn"));
        spinBoxTurn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTurn->setMinimum(-7);
        spinBoxTurn->setMaximum(7);
        spinBoxTurn->setSingleStep(0.1);

        gridLayout->addWidget(spinBoxTurn, 6, 1, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 8, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        line = new QFrame(frame);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 16, 0, 1, 3);

        spinBoxMach = new QDoubleSpinBox(frame);
        spinBoxMach->setObjectName(QStringLiteral("spinBoxMach"));
        spinBoxMach->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxMach->setMaximum(20);

        gridLayout->addWidget(spinBoxMach, 10, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        spinBoxAlpha = new QDoubleSpinBox(frame);
        spinBoxAlpha->setObjectName(QStringLiteral("spinBoxAlpha"));
        spinBoxAlpha->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxAlpha->setMinimum(-20);
        spinBoxAlpha->setMaximum(20);

        gridLayout->addWidget(spinBoxAlpha, 0, 1, 1, 1);

        spinBoxDevH = new QDoubleSpinBox(frame);
        spinBoxDevH->setObjectName(QStringLiteral("spinBoxDevH"));
        spinBoxDevH->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxDevH->setMinimum(-1);
        spinBoxDevH->setMaximum(1);
        spinBoxDevH->setSingleStep(0.05);

        gridLayout->addWidget(spinBoxDevH, 7, 1, 1, 1);

        spinBoxADF = new QDoubleSpinBox(frame);
        spinBoxADF->setObjectName(QStringLiteral("spinBoxADF"));
        spinBoxADF->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxADF->setMinimum(-360);
        spinBoxADF->setMaximum(360);

        gridLayout->addWidget(spinBoxADF, 14, 1, 1, 1);

        label_12 = new QLabel(frame);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 12, 0, 1, 1);

        spinBoxAlt = new QDoubleSpinBox(frame);
        spinBoxAlt->setObjectName(QStringLiteral("spinBoxAlt"));
        spinBoxAlt->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxAlt->setMinimum(-1000);
        spinBoxAlt->setMaximum(99999);
        spinBoxAlt->setSingleStep(10);

        gridLayout->addWidget(spinBoxAlt, 11, 1, 1, 1);

        label_14 = new QLabel(frame);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_14, 1, 0, 1, 1);

        label_16 = new QLabel(frame);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_16, 15, 0, 1, 1);

        spinBoxDME = new QDoubleSpinBox(frame);
        spinBoxDME->setObjectName(QStringLiteral("spinBoxDME"));
        spinBoxDME->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxDME->setMaximum(999);

        gridLayout->addWidget(spinBoxDME, 15, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        splitter->addWidget(frame);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widgetSix = new WidgetSix(frame_2);
        widgetSix->setObjectName(QStringLiteral("widgetSix"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetSix->sizePolicy().hasHeightForWidth());
        widgetSix->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(widgetSix, 0, 2, 2, 1);

        widgetPFD = new WidgetPFD(frame_2);
        widgetPFD->setObjectName(QStringLiteral("widgetPFD"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetPFD->sizePolicy().hasHeightForWidth());
        widgetPFD->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(widgetPFD, 0, 0, 2, 1);

        widgetNAV = new WidgetNAV(frame_2);
        widgetNAV->setObjectName(QStringLiteral("widgetNAV"));
        sizePolicy2.setHeightForWidth(widgetNAV->sizePolicy().hasHeightForWidth());
        widgetNAV->setSizePolicy(sizePolicy2);
        widgetNAV->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(widgetNAV, 0, 1, 2, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        splitter->addWidget(frame_2);

        gridLayout_5->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(spinBoxDevH);
        label_8->setBuddy(spinBoxSpeed);
        label_9->setBuddy(spinBoxAlt);
        label_10->setBuddy(spinBoxClimb);
        label_3->setBuddy(spinBoxHead);
        label_11->setBuddy(spinBoxMach);
        label_5->setBuddy(spinBoxTurn);
        label->setBuddy(spinBoxRoll);
        label_7->setBuddy(spinBoxDevV);
        label_4->setBuddy(spinBoxSlip);
        label_2->setBuddy(spinBoxPitch);
        label_12->setBuddy(spinBoxPress);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(spinBoxRoll, spinBoxPitch);
        QWidget::setTabOrder(spinBoxPitch, spinBoxHead);
        QWidget::setTabOrder(spinBoxHead, spinBoxSlip);
        QWidget::setTabOrder(spinBoxSlip, spinBoxTurn);
        QWidget::setTabOrder(spinBoxTurn, spinBoxDevH);
        QWidget::setTabOrder(spinBoxDevH, spinBoxDevV);
        QWidget::setTabOrder(spinBoxDevV, spinBoxSpeed);
        QWidget::setTabOrder(spinBoxSpeed, spinBoxMach);
        QWidget::setTabOrder(spinBoxMach, spinBoxAlt);
        QWidget::setTabOrder(spinBoxAlt, spinBoxPress);
        QWidget::setTabOrder(spinBoxPress, spinBoxClimb);
        QWidget::setTabOrder(spinBoxClimb, pushButtonAuto);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QFlightInstruments Example", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Horizontal Deviation [-]:", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Airspeed [kts]:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Altitude [ft]:", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Angle of Attack [deg]:", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Climb Rate [ft/min]:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Heading [deg]:", nullptr));
        pushButtonAuto->setText(QApplication::translate("MainWindow", "AUTO", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Mach Number [-]:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Turn Rate [deg/s]:", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "ADF Bearing [deg]:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Roll [deg]:", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Vertical Deviation [-]:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Sideslip [-]:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Pitch [deg]:", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Pressure [inHg]:", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Angle of Sideslip [deg]:", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "DME distance [nm]:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
