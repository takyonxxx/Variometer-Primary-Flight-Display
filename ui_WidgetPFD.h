/********************************************************************************
** Form generated from reading UI file 'WidgetPFD.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETPFD_H
#define UI_WIDGETPFD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qfi_PFD.h"

QT_BEGIN_NAMESPACE

class Ui_WidgetPFD
{
public:
    QFrame *framePFD;
    QGridLayout *gridLayout;
    qfi_PFD *graphicsPFD;

    void setupUi(QWidget *WidgetPFD)
    {
        if (WidgetPFD->objectName().isEmpty())
            WidgetPFD->setObjectName(QStringLiteral("WidgetPFD"));
        WidgetPFD->resize(400, 400);
        framePFD = new QFrame(WidgetPFD);
        framePFD->setObjectName(QStringLiteral("framePFD"));
        framePFD->setGeometry(QRect(70, 70, 260, 260));
        framePFD->setStyleSheet(QLatin1String("#framePFD\n"
"{\n"
"	background-color: #000;\n"
"	border-radius: 10px;\n"
"}"));
        framePFD->setFrameShape(QFrame::StyledPanel);
        framePFD->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(framePFD);
        gridLayout->setContentsMargins(4, 4, 4, 4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsPFD = new qfi_PFD(framePFD);
        graphicsPFD->setObjectName(QStringLiteral("graphicsPFD"));
        graphicsPFD->setEnabled(false);
        graphicsPFD->setFocusPolicy(Qt::NoFocus);
        graphicsPFD->setFrameShape(QFrame::NoFrame);
        graphicsPFD->setFrameShadow(QFrame::Plain);
        graphicsPFD->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsPFD->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsPFD->setInteractive(false);
        graphicsPFD->setOptimizationFlags(QGraphicsView::IndirectPainting);

        gridLayout->addWidget(graphicsPFD, 0, 0, 1, 1);


        retranslateUi(WidgetPFD);

        QMetaObject::connectSlotsByName(WidgetPFD);
    } // setupUi

    void retranslateUi(QWidget *WidgetPFD)
    {
        WidgetPFD->setWindowTitle(QApplication::translate("WidgetPFD", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetPFD: public Ui_WidgetPFD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETPFD_H
