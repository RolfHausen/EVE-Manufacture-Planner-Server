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
    m_PISelectionModel = new QStringListModel();
    m_PISelectionModel->setStringList(m_DM.getPIDataStringList());
    ui->PISelectionTreeView->setModel(m_PISelectionModel);

    //add all Blueprintnames as Items into the Combobox

    m_DM.LoadBlueprints(); //loads all Blueprints from Db
    m_DM.LoadMaterialData(); //loads all Materials from Db
    m_DM.LoadBlueprintMaterials(); //loads the needed Materials for each Blueprint

    m_BlueprintStringList = m_DM.getBlueprintStringList();
    ui->BlueprintSelectionComboBox->addItems(m_BlueprintStringList);
    QObject::connect (ui->BlueprintSelectionComboBox, SIGNAL(activated(int)), this, SLOT( on_BlueprintSelectionComboBox_activated(int index)));
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
    PIProduct p=m_DM.getPIData().getItemByName(m_PISelectionModel->data(index).toString());
    m_DM.getPIDataTreeItem(ui->ProductionDetailsTreeWidget,p);
}

void ProductionView::on_BlueprintSelectionComboBox_activated(int index)
{
    //this will list the needed ressources for the selected blueprint within the TreeWidget
    Blueprint bp = m_DM.getBlueprintByName(m_BlueprintStringList[index]);
    m_DM.getBlueprintMaterialsTreeItem(ui->ProductionDetailsTreeWidget,bp);
}

void ProductionView::on_ClearPushButton_clicked()
{
    ui->ProductionDetailsTreeWidget->clear();
}

