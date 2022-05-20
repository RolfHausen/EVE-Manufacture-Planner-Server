#include "planet.h"


Planet::Planet()
{

}

Planet::~Planet()
{

}

const QString &Planet::PlanetName() const
{
    return m_PlanetName;
}

void Planet::setPlanetName(const QString &newPlanetName)
{
    m_PlanetName = newPlanetName;
}

const QString &Planet::SystemName() const
{
    return m_SystemName;
}

void Planet::setSystemName(const QString &newSystemName)
{
    m_SystemName = newSystemName;
}

Planet::PlanetTypes Planet::PlanetType() const
{
    return m_PlanetType;
}

void Planet::setPlanetType(PlanetTypes newPlanetType)
{
    m_PlanetType = newPlanetType;
}

QMap<QString, uint> &Planet::getSources()
{
    return m_Sources;
}

void Planet::addSource(QString name, uint value)
{
    m_Sources.insert(name,value);
}

const QString &Planet::PlanetFilename() const
{
    return m_PlanetFilename;
}

void Planet::setPlanetFilename(const QString &newPlanetFilename)
{
    m_PlanetFilename = newPlanetFilename;
}

const QByteArray &Planet::PlanetFile() const
{
    return m_PlanetFile;
}

void Planet::setPlanetFile(const QByteArray &newPlanetFile)
{
    m_PlanetFile = newPlanetFile;
}
