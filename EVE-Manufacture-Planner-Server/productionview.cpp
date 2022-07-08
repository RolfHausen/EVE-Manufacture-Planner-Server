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
    m_ProductStringList=m_DM.getProductStringList();
    m_ProductSelectionModel = new QStringListModel();
    m_ProductSelectionModel->setStringList(m_ProductStringList);
    m_BPProxyModel = new QSortFilterProxyModel();
    m_BPProxyModel->setSourceModel(m_ProductSelectionModel);
    m_BPProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QCompleter* ProductSearchCompleter = new QCompleter();
    ProductSearchCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ProductSearchCompleter->setModel(m_BPProxyModel);
    ProductSearchCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

    ui->ProductSearchLineEdit->setCompleter(ProductSearchCompleter);

    //activate the controls
    ui->ProductSearchLineEdit->setEnabled(true);
    ui->AddpushButton->setEnabled(true);
}

void ProductionView::on_ClearPushButton_clicked()
{
    ui->ProductionDetailsTreeWidget->clear();
}

void ProductionView::on_AddpushButton_clicked()
{
        AddTreeWidgetItem();
}

void ProductionView::AddTreeWidgetItem()
{
    QString Product = ui->ProductSearchLineEdit->text();
    QList<Blueprint> Blueprints = m_DM.Blueprints();
    QList<PIProduct> PiProducts = m_DM.getPIData().getAll();
    int i=0;
    bool found = false;
    int ProdAmount = 0;
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(ui->ProdAmountLineEdit->text())) //if it consists only of numbers
    {
        ProdAmount= ui->ProdAmountLineEdit->text().toUInt();
    }
    else
    {
        return;
    }

    while(!found && i < Blueprints.count())
    {
        if(Blueprints[i].BPProduct()==Product)
        {
            found=true;
            m_DM.getBlueprintMaterialsTreeItem(ui->ProductionDetailsTreeWidget,Blueprints[i],ProdAmount);
        }
        i++;
    }
    i=0;
    while(!found && i < PiProducts.count())
    {
        if(PiProducts[i].getPIName()==Product)
        {
            found = true;
            m_DM.getPIDataTreeItem(ui->ProductionDetailsTreeWidget,PiProducts[i],ProdAmount);
        }
        i++;
    }


    //Blueprint bp = m_DM.getBlueprintByName(ui->ProductSearchLineEdit->text());
    //m_DM.getBlueprintMaterialsTreeItem(ui->ProductionDetailsTreeWidget,bp);
}




