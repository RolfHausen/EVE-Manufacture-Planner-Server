#ifndef PRODUCTIONVIEW_H
#define PRODUCTIONVIEW_H

#include <QDialog>
#include <QFile>
#include<QStringListModel>
#include<QMessageBox>
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

private slots:

    void on_PISelectionTreeView_doubleClicked(const QModelIndex &index);
    void on_BlueprintSelectionComboBox_activated(int index);

    void on_ClearPushButton_clicked();

private:
    Ui::ProductionView *ui;
    DataModel m_DM;
    QStringListModel* m_PISelectionModel;
    QStringList m_BlueprintStringList;
};

#endif // PRODUCTIONVIEW_H
