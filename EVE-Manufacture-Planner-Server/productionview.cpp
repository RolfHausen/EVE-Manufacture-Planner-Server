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
    QString ProductName = ui->ProductSearchLineEdit->text();    
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
    ProductionTreeItem ProductTreeItem;
    while(!found && i < m_DM.ProductionTrees().count())
    {
        qDebug() << m_DM.ProductionTrees()[i].Product()->Name() << "\t" << i;
        if(m_DM.ProductionTrees()[i].Product()->Name() == ProductName)
        {
            found = true;
            ProductTreeItem = m_DM.ProductionTrees()[i];
        }
        i++;
    }



    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem* ItemRoot = new QTreeWidgetItem(ui->ProductionDetailsTreeWidget);
    ItemRoot->setText(COLPRODUCTNAME,ProductTreeItem.Product()->Name());

    for(int i=0; i < ProductTreeItem.TreeItems().count();i++)
    {
        QTreeWidgetItem* treeitem = new QTreeWidgetItem(ItemRoot);
        treeitem->setText(COLPRODUCTNAME,ProductTreeItem.TreeItems()[i]->Product()->Name());

        BuildTreeWidgetItemTree(treeitem,ProductTreeItem.TreeItems()[i]);
    }

}

void ProductionView::BuildTreeWidgetItemTree(QTreeWidgetItem *wparent, ProductionTreeItem* pparent)
{
    const int COLPRODUCTNAME =0;
    const int COLINPUTAMOUNT =1;
    const int COLOUTPUTAMOUNT =2;

    QTreeWidgetItem* wchild = new QTreeWidgetItem(wparent);
    wchild->setText(COLPRODUCTNAME,pparent->Product()->Name());

    for(int i=0; i < pparent->TreeItems().count();i++)
    {
        QTreeWidgetItem* treeitem = new QTreeWidgetItem(wchild);
        treeitem->setText(COLPRODUCTNAME,pparent->TreeItems()[i]->Product()->Name());

        BuildTreeWidgetItemTree(treeitem,pparent->TreeItems()[i]);
    }
}





