/********************************************************************************
** Form generated from reading UI file 'pi_production_view.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PI_PRODUCTION_VIEW_H
#define UI_PI_PRODUCTION_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_PI_Production_View
{
public:
    QTreeView *PISelectionTreeView;
    QTreeWidget *ProductionDetailsTreeWidget;
    QPushButton *ClearPushButton;
    QPushButton *ClosePushButton;

    void setupUi(QDialog *PI_Production_View)
    {
        if (PI_Production_View->objectName().isEmpty())
            PI_Production_View->setObjectName(QString::fromUtf8("PI_Production_View"));
        PI_Production_View->resize(765, 372);
        PISelectionTreeView = new QTreeView(PI_Production_View);
        PISelectionTreeView->setObjectName(QString::fromUtf8("PISelectionTreeView"));
        PISelectionTreeView->setGeometry(QRect(0, 10, 251, 311));
        ProductionDetailsTreeWidget = new QTreeWidget(PI_Production_View);
        ProductionDetailsTreeWidget->setObjectName(QString::fromUtf8("ProductionDetailsTreeWidget"));
        ProductionDetailsTreeWidget->setGeometry(QRect(250, 10, 501, 311));
        ClearPushButton = new QPushButton(PI_Production_View);
        ClearPushButton->setObjectName(QString::fromUtf8("ClearPushButton"));
        ClearPushButton->setGeometry(QRect(500, 330, 121, 31));
        ClosePushButton = new QPushButton(PI_Production_View);
        ClosePushButton->setObjectName(QString::fromUtf8("ClosePushButton"));
        ClosePushButton->setGeometry(QRect(630, 330, 121, 31));

        retranslateUi(PI_Production_View);
        QObject::connect(ClosePushButton, SIGNAL(clicked()), PI_Production_View, SLOT(close()));

        QMetaObject::connectSlotsByName(PI_Production_View);
    } // setupUi

    void retranslateUi(QDialog *PI_Production_View)
    {
        PI_Production_View->setWindowTitle(QCoreApplication::translate("PI_Production_View", "Dialog", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = ProductionDetailsTreeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("PI_Production_View", "Outputamount", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("PI_Production_View", "Inputamount", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PI_Production_View", "Products", nullptr));
        ClearPushButton->setText(QCoreApplication::translate("PI_Production_View", "Clear", nullptr));
        ClosePushButton->setText(QCoreApplication::translate("PI_Production_View", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PI_Production_View: public Ui_PI_Production_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PI_PRODUCTION_VIEW_H
