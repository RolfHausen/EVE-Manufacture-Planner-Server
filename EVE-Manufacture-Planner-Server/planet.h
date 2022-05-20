#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QMap>
#include <QMetaEnum>

class Planet: public QObject
{
    Q_OBJECT
public:    
    enum PlanetTypes
    {
        Barren,Gas,Ice,Lava,Oceanic,Plasma,Storm,Temperate
    };Q_ENUM(PlanetTypes)

    const QStringList BarrenSources = {"Aqueous Liquids","Base Metals","Carbon Compounds","Micro Organisms","Noble Metals"};
    const QStringList GasSources = {"Aqueous Liquids","Base Metals","Ionic Solutions","Noble Gas","Reactive Gas"};
    const QStringList IceSources = {"Aqueous Liquids","Heavy Metals","Micro Organisms","Noble Gas","Planktic Colonies"};
    const QStringList LavaSources = {"Base Metals","Felsic Magma","Heavy Metals","Non-CS Crystals","Suspended Plasma"};
    const QStringList OceanicSources = {"Aqueous Liquids","Carbon Compounds","Complex Organisms","Micro Organisms","Planktic Colonies"};
    const QStringList PlasmaSources = {"Base Metals","Heavy Metals","Noble Metals","Non-CS Crystals","Suspended Plasma"};
    const QStringList StromSources = {"Aqueous Liquids","Base Metals","Ionic Solutions","Noble Gas","Suspended Plasma"};
    const QStringList TemperateSources = {"Aqueous Liquids","Autotrophs","Carbon Compounds","Complex Organisms","Micro Organisms"};

    Planet();
    ~Planet();

    const QString &PlanetName() const;
    void setPlanetName(const QString &newPlanetName);
    const QString &SystemName() const;
    void setSystemName(const QString &newSystemName);
    PlanetTypes PlanetType() const;
    void setPlanetType(PlanetTypes newPlanetType);

    QMap<QString,uint> &getSources();
    void addSource(QString name,uint value);

    const QString &PlanetFilename() const;
    void setPlanetFilename(const QString &newPlanetFilename);
    const QByteArray &PlanetFile() const;
    void setPlanetFile(const QByteArray &newPlanetFile);

private:
    QString m_PlanetName;
    QString m_SystemName;
    PlanetTypes m_PlanetType;
    QMap<QString,uint> m_Sources;

    QString m_PlanetFilename; //preparation for the later stored images
    QByteArray m_PlanetFile;

};

#endif // PLANET_H
