#ifndef PREPROCCESSING_H
#define PREPROCCESSING_H
#include "config.h"

#include <iostream>
#include <QCoreApplication>

using namespace std;
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "../opennn/opennn.h"

using namespace OpenNN;

class Preproccessing
{
public:
    Preproccessing();
    void LoadConfigFromFile(QString file);
    bool CheckDatabase();
    Config config;
    QSqlDatabase db;
    void LoadDataset();
    DatasetStructure datasetModel;

};


#endif // PREPROCCESSING_H
