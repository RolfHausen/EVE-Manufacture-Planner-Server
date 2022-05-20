#include "productionview.h"
#include "ui_productionview.h"

ProductionView::ProductionView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductionView)
{
    ui->setupUi(this);    
    //Initialize Data to Show up in the View.
    if (!m_DM.openDb())
    {
        QMessageBox QMsg;
        QMsg.setIcon(QMessageBox::Icon::Critical);
        QMsg.setWindowTitle("Database Connection Error");
        QMsg.setText(m_DM.LastError());
    }
    m_DM.LoadPIData();

    //get Data from Model
    PISelectionModel = new QStringListModel();
    PISelectionModel->setStringList(m_DM.getPIDataStringList());
    ui->PISelectionTreeView->setModel(PISelectionModel);
}

ProductionView::~ProductionView()
{
    delete ui;
}

void ProductionView::on_PISelectionTreeView_doubleClicked(const QModelIndex &index)
{
    /*  Gets the selected Item from PISelectionList via GetByName
    //  Reason is: in the future this will be a List Sorted by Types
    //  and Filters so that index will not correspond with the index in PIData
    */
    PIProduct p=m_DM.getPIData().getItemByName(PISelectionModel->data(index).toString());
    m_DM.getPIDataTreeItem(ui->ProductionDetailsTreeWidget,p);
}

void ProductionView::on_ClearPushButton_clicked()
{
    ui->ProductionDetailsTreeWidget->clear();
}

