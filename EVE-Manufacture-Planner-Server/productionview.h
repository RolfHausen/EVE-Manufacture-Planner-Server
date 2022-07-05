#ifndef PRODUCTIONVIEW_H
#define PRODUCTIONVIEW_H

#include <QDialog>
#include <QFile>
#include<QStringListModel>
#include<QMessageBox>
#include <QSortFilterProxyModel>
#include <QCompleter>
#include "datamodel.h"

namespace Ui {
class ProductionView;
}

class ProductionView : public QDialog
{
    Q_OBJECT

public:
    explicit ProductionView(QWidget *parent = nullptr);
    ~ProductionView();
    void setDataModel(DataModel dm);
    void ShowData();

private slots:

    void on_ClearPushButton_clicked();
    void on_BlueprintSearchLineEdit_returnPressed();
    void on_AddpushButton_clicked();

private:
    Ui::ProductionView *ui;
    DataModel m_DM;
    QStringListModel* m_PISelectionModel;
    QStringList m_BlueprintStringList;
    QStringListModel* m_BpSelectionModel;
    QSortFilterProxyModel* m_BPProxyModel;
    QSortFilterProxyModel* m_BPProxyModel1;

    void AddTreeWidgetItem();

};

#endif // PRODUCTIONVIEW_H
