#ifndef DATALOADWORKER_H
#define DATALOADWORKER_H

#include <QObject>
#include <datamodel.h>
#include <globals.h>

class DataLoadWorker: public QObject
{
    Q_OBJECT
public:
    DataLoadWorker();
    ~DataLoadWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void deployData(DataModel dm);

private:
    DataModel m_DM;
};

#endif // DATALOADWORKER_H
