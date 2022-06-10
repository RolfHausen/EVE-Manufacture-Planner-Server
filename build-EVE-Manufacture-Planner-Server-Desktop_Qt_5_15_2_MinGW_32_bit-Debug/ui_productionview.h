/********************************************************************************
** Form generated from reading UI file 'productionview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTIONVIEW_H
#define UI_PRODUCTIONVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_ProductionView
{
public:
    QTreeView *PISelectionTreeView;
    QPushButton *ClearPushButton;
    QPushButton *ClosePushButton;
    QTreeWidget *ProductionDetailsTreeWidget;
    QComboBox *BlueprintSelectionComboBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *ProductionView)
    {
        if (ProductionView->objectName().isEmpty())
            ProductionView->setObjectName(QString::fromUtf8("ProductionView"));
        ProductionView->resize(756, 361);
        PISelectionTreeView = new QTreeView(ProductionView);
        PISelectionTreeView->setObjectName(QString::fromUtf8("PISelectionTreeView"));
        PISelectionTreeView->setGeometry(QRect(0, 80, 251, 231));
        ClearPushButton = new QPushButton(ProductionView);
        ClearPushButton->setObjectName(QString::fromUtf8("ClearPushButton"));
        ClearPushButton->setGeometry(QRect(500, 320, 121, 31));
        ClosePushButton = new QPushButton(ProductionView);
        ClosePushButton->setObjectName(QString::fromUtf8("ClosePushButton"));
        ClosePushButton->setGeometry(QRect(630, 320, 121, 31));
        ProductionDetailsTreeWidget = new QTreeWidget(ProductionView);
        ProductionDetailsTreeWidget->setObjectName(QString::fromUtf8("ProductionDetailsTreeWidget"));
        ProductionDetailsTreeWidget->setGeometry(QRect(250, 0, 501, 311));
        BlueprintSelectionComboBox = new QComboBox(ProductionView);
        BlueprintSelectionComboBox->setObjectName(QString::fromUtf8("BlueprintSelectionComboBox"));
        BlueprintSelectionComboBox->setGeometry(QRect(0, 20, 241, 22));
        label = new QLabel(ProductionView);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 241, 16));
        label_2 = new QLabel(ProductionView);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 241, 16));

        retranslateUi(ProductionView);
        QObject::connect(ClosePushButton, SIGNAL(clicked()), ProductionView, SLOT(close()));

        QMetaObject::connectSlotsByName(ProductionView);
    } // setupUi

    void retranslateUi(QDialog *ProductionView)
    {
        ProductionView->setWindowTitle(QCoreApplication::translate("ProductionView", "Dialog", nullptr));
        ClearPushButton->setText(QCoreApplication::translate("ProductionView", "Clear", nullptr));
        ClosePushButton->setText(QCoreApplication::translate("ProductionView", "Close", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = ProductionDetailsTreeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ProductionView", "Outputamount", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ProductionView", "Inputamount", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ProductionView", "Products", nullptr));
        label->setText(QCoreApplication::translate("ProductionView", "Select Blueprint:", nullptr));
        label_2->setText(QCoreApplication::translate("ProductionView", "Select Planetary Product", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductionView: public Ui_ProductionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTIONVIEW_H
