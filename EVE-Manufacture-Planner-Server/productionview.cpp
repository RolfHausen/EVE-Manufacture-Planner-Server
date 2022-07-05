#include "productionview.h"
#include "ui_productionview.h"


ProductionView::ProductionView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductionView)
{
    ui->setupUi(this);
}

ProductionView::~ProductionView()
{
    delete ui;
}

void ProductionView::setDataModel(DataModel dm)
{
    m_DM = dm;
}

void ProductionView::ShowData()
{
    //here we need no Mutex Lock for now because this only runs when the backgroundworker is done

    //get Data from Model
    m_PISelectionModel = new QStringListModel();
    m_PISelectionModel->setStringList(m_DM.getPIDataStringList());


    m_BlueprintStringList = m_DM.getBlueprintStringList();
    m_BpSelectionModel = new QStringListModel();
    m_BpSelectionModel->setStringList(m_BlueprintStringList);
    m_BPProxyModel = new QSortFilterProxyModel();
    m_BPProxyModel->setSourceModel(m_BpSelectionModel);
    m_BPProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QCompleter* BpSearchCompleter = new QCompleter();
    BpSearchCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    BpSearchCompleter->setModel(m_BPProxyModel);
    BpSearchCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);    

    ui->BlueprintSearchLineEdit->setCompleter(BpSearchCompleter);

    //activate the controls
    ui->BlueprintSearchLineEdit->setEnabled(true);
    ui->AddpushButton->setEnabled(true);
}

void ProductionView::on_ClearPushButton_clicked()
{
    ui->ProductionDetailsTreeWidget->clear();
}

void ProductionView::on_BlueprintSearchLineEdit_returnPressed()
{
    AddTreeWidgetItem();

}


void ProductionView::on_AddpushButton_clicked()
{
    AddTreeWidgetItem();
}

void ProductionView::AddTreeWidgetItem()
{
    //this will list the needed ressources for the selected blueprint within the TreeWidget
    Blueprint bp = m_DM.getBlueprintByName(ui->BlueprintSearchLineEdit->text());
    m_DM.getBlueprintMaterialsTreeItem(ui->ProductionDetailsTreeWidget,bp);
    ui->setupUi(this); //for a LineEdit it appears to be needed to refresh the ui for showing the Tree.
}

