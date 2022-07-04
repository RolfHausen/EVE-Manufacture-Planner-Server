#ifndef PLANETARYVIEW_H
#define PLANETARYVIEW_H
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QStringListModel>
#include <QSpacerItem>
#include <QGridLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QTableView>
#include <QMessageBox>
#include <QHeaderView>

#include <datamodel.h>

class PlanetaryView : public QDialog

{
    Q_OBJECT
public:
    explicit PlanetaryView(QWidget *parent = nullptr);
    void setDataModel(DataModel& dm);

private:
    QHBoxLayout* PlanetaryViewHLayout;
    QVBoxLayout* AddPlanetsVLayout;
    QHBoxLayout* PlanetHLayout;
    QHBoxLayout* SystemHLayout;
    QHBoxLayout* PlanetTypeHLayout;
    QGridLayout* SourcesGridLayout;
    QHBoxLayout* ButtonsLayout;
    QLabel* SystemLabel;
    QLineEdit* SystemLineEdit;
    QLabel* PlanetLabel;
    QLineEdit* PlanetLineEdit;

    QLabel* PlanetTypeLabel;
    QComboBox* PlanetTypeComboBox;
    DataModel m_DM;

    QLabel* Source1Label;
    QLabel* Source2Label;
    QLabel* Source3Label;
    QLabel* Source4Label;
    QLabel* Source5Label;

    QLineEdit* Source1LineEdit;
    QLineEdit* Source2LineEdit;
    QLineEdit* Source3LineEdit;
    QLineEdit* Source4LineEdit;
    QLineEdit* Source5LineEdit;

    QPushButton* SavePushButton;
    QPushButton* ResetPushButton;
    QPushButton* ClosePushButton;

    QSpacerItem* VerticalSpacer;

    QTableView* SavedPlanetsTableView;

    QStatusBar* PlanetaryViewStatusBar;

    void initialize();

public slots:
    void onPlanetTypeComboBoxSelectionChanged(int index);
    void onSavePlanetData();
    void onResetPlanetaryView();



};

#endif // PLANETARYVIEW_H
