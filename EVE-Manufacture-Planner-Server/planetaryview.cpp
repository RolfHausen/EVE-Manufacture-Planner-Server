#include "planetaryview.h"


PlanetaryView::PlanetaryView(QWidget *parent)
    :QDialog(parent)
{    
    //to have a table Sitting right next to our Adding Fields we Make a horizontal Layout
    PlanetaryViewHLayout = new QHBoxLayout(this);

    //This is our Stack for the horizontal Layouts
    AddPlanetsVLayout = new QVBoxLayout();

    PlanetHLayout = new QHBoxLayout();

    PlanetLabel = new QLabel("Planet:");
    PlanetLineEdit = new QLineEdit();

    PlanetHLayout->addWidget(PlanetLabel);
    PlanetHLayout->addWidget(PlanetLineEdit);

    AddPlanetsVLayout->addLayout(PlanetHLayout);

    SystemHLayout = new QHBoxLayout();

    SystemLineEdit = new QLineEdit();
    SystemLabel = new QLabel("System:");

    SystemHLayout->addWidget(SystemLabel);
    SystemHLayout->addWidget(SystemLineEdit);

    AddPlanetsVLayout->addLayout(SystemHLayout);

    PlanetTypeHLayout = new QHBoxLayout();

    PlanetTypeComboBox = new QComboBox();
    PlanetTypeLabel = new QLabel("Planet-Type:");


    PlanetTypeHLayout->addWidget(PlanetTypeLabel);
    PlanetTypeHLayout->addWidget(PlanetTypeComboBox);

    AddPlanetsVLayout->addLayout(PlanetTypeHLayout);

    SourcesGridLayout = new QGridLayout();


    Source1Label = new QLabel();
    Source1LineEdit = new QLineEdit();
    Source1LineEdit->setValidator( new QIntValidator(0, 100, this) );
    //the validator allows technically to enter 3 digits up to 999 but it will be checked at saving that the value is between 0 and 100

    Source2Label = new QLabel();
    Source2LineEdit = new QLineEdit();
    Source2LineEdit->setValidator( new QIntValidator(0, 100, this) );

    Source3Label = new QLabel("SOURCE 3:");
    Source3LineEdit = new QLineEdit();
    Source3LineEdit-> setValidator( new QIntValidator(0, 100, this) );

    Source4Label = new QLabel("SOURCE 4:");
    Source4LineEdit = new QLineEdit();
    Source4LineEdit->setValidator( new QIntValidator(0, 100, this) );

    Source5Label = new QLabel("SOURCE 5:");
    Source5LineEdit = new QLineEdit();
    Source5LineEdit->setValidator( new QIntValidator(0, 100, this) );

    SourcesGridLayout->addWidget(Source1Label,0,0);
    SourcesGridLayout->addWidget(Source1LineEdit,0,1);
    SourcesGridLayout->addWidget(Source2Label,1,0);
    SourcesGridLayout->addWidget(Source2LineEdit,1,1);
    SourcesGridLayout->addWidget(Source3Label,2,0);
    SourcesGridLayout->addWidget(Source3LineEdit,2,1);
    SourcesGridLayout->addWidget(Source4Label,3,0);
    SourcesGridLayout->addWidget(Source4LineEdit,3,1);
    SourcesGridLayout->addWidget(Source5Label,4,0);
    SourcesGridLayout->addWidget(Source5LineEdit,4,1);

    AddPlanetsVLayout->addLayout(SourcesGridLayout);

    ButtonsLayout = new QHBoxLayout();
    SavePushButton = new QPushButton();
    SavePushButton->setText("Save");
    ButtonsLayout->addWidget(SavePushButton);

    ResetPushButton = new QPushButton();
    ResetPushButton->setText("Reset");
    ButtonsLayout->addWidget(ResetPushButton);

    ClosePushButton = new QPushButton();
    ClosePushButton->setText("Close");
    ButtonsLayout->addWidget(ClosePushButton);

    AddPlanetsVLayout->addLayout(ButtonsLayout);

    VerticalSpacer = new QSpacerItem(200,300);
    AddPlanetsVLayout->addItem(VerticalSpacer);

    PlanetaryViewHLayout->addLayout(AddPlanetsVLayout);

    //here comes our Table to View the saved Planets
    SavedPlanetsTableView = new QTableView();

    PlanetaryViewHLayout->addWidget(SavedPlanetsTableView);

    PlanetaryViewStatusBar = new QStatusBar(this);
    PlanetaryViewHLayout->addWidget(PlanetaryViewStatusBar);

    //connect the comboboxCurrentIndexChanged to our own slot to handle changed PlanetTypes.
    connect(PlanetTypeComboBox,SIGNAL(currentIndexChanged(int)),SLOT(onPlanetTypeComboBoxSelectionChanged(int)));
    connect(SavePushButton,SIGNAL(clicked()),SLOT(onSavePlanetData()));
    connect(ResetPushButton,SIGNAL(clicked()),SLOT(onResetPlanetaryView()));
    connect(ClosePushButton,SIGNAL(clicked()),SLOT(close()));


    if(!m_DM.openDb()) // prepare DB
    {
        QMessageBox QMsg;
        QMsg.setIcon(QMessageBox::Icon::Critical);
        QMsg.setWindowTitle("Database Connection Error");
        QMsg.setText(m_DM.LastError());

    }
    initialize();
}

void PlanetaryView::initialize()
{
    //Fill PlanetTypeComboBox with Data
    QStringList PlanetTypStringList=m_DM.getPlanetTypes();
    QStringListModel* PlanetTypeStringListModel = new QStringListModel();
    PlanetTypeStringListModel->setStringList(PlanetTypStringList);
    PlanetTypeComboBox->setModel(PlanetTypeStringListModel);

    //load the saved Planets from DB for TableView
    m_DM.LoadPlanetData();
    QStandardItemModel *model = m_DM.getPlanetItemModel();
    SavedPlanetsTableView->setModel(model);
    SavedPlanetsTableView->resizeColumnsToContents();

}

void PlanetaryView::onPlanetTypeComboBoxSelectionChanged(int index)
{

    QStringList Sources;

    if(index == Planet::PlanetTypes::Barren) Sources = m_DM.getBarrenSources();
    if(index == Planet::PlanetTypes::Gas) Sources = m_DM.getGasSources();
    if(index == Planet::PlanetTypes::Ice) Sources = m_DM.getIceSources();
    if(index == Planet::PlanetTypes::Lava) Sources = m_DM.getLavaSources();
    if(index == Planet::PlanetTypes::Oceanic) Sources = m_DM.getOceanicSources();
    if(index == Planet::PlanetTypes::Plasma) Sources = m_DM.getPlasmaSources();
    if(index == Planet::PlanetTypes::Storm) Sources = m_DM.getStormSources();
    if(index == Planet::PlanetTypes::Temperate) Sources = m_DM.getTemperateSources();


    Source1Label->setText(Sources[0]);
    Source2Label->setText(Sources[1]);
    Source3Label->setText(Sources[2]);
    Source4Label->setText(Sources[3]);
    Source5Label->setText(Sources[4]);

    AddPlanetsVLayout->update();

}

void PlanetaryView::onSavePlanetData()
{
    //first check valid information
    QString name = PlanetLineEdit->text();
    QString systemname = SystemLineEdit->text();
    //because EVE has different names with words in High- & Low-Security-Space and kind of IDs like ABC-123 in Null-Security-Space
    //we do not validate the names for Planet and System.
    //maybe later we add some security against SQL-Injections.
    QString type =PlanetTypeComboBox->currentText();

    QMap<QString,uint> Sources;
    Sources.insert(Source1Label->text(),Source1LineEdit->text().toInt());
    Sources.insert(Source2Label->text(),Source2LineEdit->text().toInt());
    Sources.insert(Source3Label->text(),Source3LineEdit->text().toInt());
    Sources.insert(Source4Label->text(),Source4LineEdit->text().toInt());
    Sources.insert(Source5Label->text(),Source5LineEdit->text().toInt());

    //get also the Names for correct ErrorMessage:    
    bool hasErrors = false;

    QMapIterator<QString,uint> SourcesIterator(Sources);
    while(SourcesIterator.hasNext())
    {
        SourcesIterator.next();
        if(SourcesIterator.value() > 100)
        {
            //if anything is found put up an Errormessage;
            QString Error = "Invalid value at "+ SourcesIterator.key() +"!";
            PlanetaryViewStatusBar->showMessage(Error);
            hasErrors=true;
        }
    }

    //Save the data to Database
    if(!hasErrors)
    {
        m_DM.SavePlanet(name,systemname,type,Sources);
    }

}

void PlanetaryView::onResetPlanetaryView()
{
    
}

void PlanetaryView::setDataModel(DataModel &dm)
{
    m_DM = dm;
}



