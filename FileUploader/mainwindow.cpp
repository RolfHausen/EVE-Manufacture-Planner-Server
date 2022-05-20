#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_DbMan = new DbManager();
    QObject::connect(m_DbMan,SIGNAL(progressChanged(int value)),SLOT(on_ProgressChanged(int value)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ConnectDbPushButton_clicked()
{
    m_DbMan->setDBServer(ui->ServernameLineEdit->text());
    m_DbMan->setDBUser(ui->UsernameLineEdit->text());
    m_DbMan->setDBpwd(ui->PasswordLineEdit->text());
    m_DbMan->setDBName(ui->DatabaseLineEdit->text());

    if(m_DbMan->openDB())
    {
        QStringList TablesNames=m_DbMan->LoadTables();
        m_TableNamesModel = new QStringListModel();
        m_TableNamesModel->setStringList(TablesNames);
        ui->TableComboBox->setModel(m_TableNamesModel);
    }

}


void MainWindow::on_UploadFilePushButton_clicked()
{
    QFile file(m_FileName);
    if(!file.open(QIODevice::ReadOnly)) return;
    QByteArray filedata = file.readAll();
    if(m_DbMan->StoreFile(m_ItemName ,m_TableName,m_FileName,filedata))
    {
        ui->statusbar->clearMessage();
        ui->statusbar->showMessage("Upload finished");
        m_DbMan->LoadTableRows(m_TableName);
        ui->TableView->setModel(m_DbMan->GetTableData());

    }
    else
    {
        ui->statusbar->showMessage(m_DbMan->LastError());
    }
}


void MainWindow::on_TableComboBox_currentIndexChanged(int index)
{
    ui->statusbar->clearMessage();
    m_TableName = ui->TableComboBox->itemText(index);
    QStringList TableRows = m_DbMan->LoadTableRows(m_TableName);
    QStringListModel* TableRowsModel = new QStringListModel();
    TableRowsModel->setStringList(TableRows);
    ui->TablerowComboBox->setModel(TableRowsModel);
    ui->TableView->setModel(m_DbMan->GetTableData());

}


void MainWindow::on_TablerowComboBox_currentIndexChanged(const QString &arg1)
{
    m_ItemName=arg1;
    ui->FullFileNameLineEdit->clear();
    ui->statusbar->clearMessage();
    ui->UploadFilePushButton->setEnabled(!arg1.isEmpty());
    ui->UploadProgressBar->setValue(0);
}


void MainWindow::on_BrowsePushButton_clicked()
{
    m_FileName = QFileDialog::getOpenFileName(this,"Select Image for this Item");
    ui->FullFileNameLineEdit->setText(m_FileName); //to Show it on the view.
}

void MainWindow::on_ProgressChanged(int value)
{
    ui->UploadProgressBar->setValue(value);
}


