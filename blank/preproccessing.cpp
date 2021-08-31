#include "preproccessing.h"

#include <QJsonArray>
#include <QVariantMap>
#include <qfile.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QDebug>

Preproccessing::Preproccessing()
{

}
void  Preproccessing::LoadConfigFromFile(QString file){
     cout << "Load config from json file" << endl;
    QFile jsonData;
    jsonData.setFileName(file);
    jsonData.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = jsonData.readAll();
    jsonData.close();
    QJsonDocument doc= QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jObject = doc.object();
    QVariantMap mainMap = jObject.toVariantMap();
    Config config ;
    config.neuronNumber= jObject["neuronNumber"].toInt();
    config.layerNumber= jObject["layerNumber"].toInt();
    config.trainPrcentage= jObject["trainPrcentage"].toInt();
    config.testPrcentage= jObject["testPrcentage"].toInt();
    config.validationPrcentage= jObject["validationPrcentage"].toInt();
    config.learningRate= jObject["learningRate"].toInt();
    config.allowedRrror= jObject["allowedRrror"].toInt();
    QJsonArray trainingActivationFunctionList = jObject.value("trainingActivationFunctions").toArray();
    vector<int> trainingActivationFunction;
    for (int i =0; i<trainingActivationFunctionList.size(); i++ )    {
        trainingActivationFunction.push_back(trainingActivationFunctionList.at(i).toInt());
    }
    config.trainingActivationFunctions=trainingActivationFunction;
    QJsonArray traingingStrategyList = jObject.value("traingingStrategy").toArray();
    vector<int> traingingStrategy;
    for (int i =0; i<traingingStrategyList.size(); i++ )    {
        traingingStrategy.push_back(traingingStrategyList.at(i).toInt());
    }
    config.traingingStrategy=traingingStrategy;
    QJsonArray optimizationMethodeList = jObject.value("optimizationMethode").toArray();
    vector<int> optimizationMethode;
    for (int i =0; i<optimizationMethodeList.size(); i++ )    {
        optimizationMethode.push_back(optimizationMethodeList.at(i).toInt());
    }
    config.optimizationMethode=optimizationMethode;
    QJsonArray outActivationFunctionsList = jObject.value("outActivationFunctions").toArray();
    vector<int> outActivationFunctions;
    for (int i =0; i<outActivationFunctionsList.size(); i++ )    {
        outActivationFunctions.push_back(outActivationFunctionsList.at(i).toInt());
    }
    config.outActivationFunctions=outActivationFunctions;

    config.autoSplitData= mainMap["autoSplitData"].toBool();
    config.datasetPath= mainMap["mainDatasetPath"].toString();
    config.testDatasetPath= mainMap["testDatasetPath"].toString();
    config.trainDatasetPath= mainMap["trainDatasetPath"].toString();
    config.validationDatasetPath= mainMap["validationDatasetPath"].toString();
    config.databasePath= mainMap["databasePath"].toString();
    config.delimatedCharachter = mainMap["delimatedCharachter"].toString().toStdString()[0];
    for (int i = 0; i < this->config.dataset_columns.size(); i++) {
          if (this->config.dataset_columns[i] == 1) {
              this->config.numberInput++;
          }
          if (this->config.dataset_columns[i] == 2) {
            this->config.numberOutput++;
          }
        }
    this->config=config;
}

bool Preproccessing::CheckDatabase()
{
     cout << "Start check database" << endl;
    if (!QFile::exists(this->config.databasePath)) {
        this->db = QSqlDatabase::addDatabase("QSQLITE");
         this->db.setDatabaseName(this->config.databasePath);
        if (!this->db.tables().contains(QLatin1String("Topologys")) && !this->db.tables().contains(QLatin1String("Topologys_temp"))) {
          this->db.open();
          QSqlQuery temp_db;
          string query = "CREATE TABLE Topologys (id INTEGER NOT NULL,Inputs TEXT,Outputs TEXT,Layer1Neurons TEXT,Layer2Neurons TEXT,Layer3Neurons TEXT,Layer1Activation TEXT,Layer2Activation TEXT,Layer3Activation TEXT,LastLayerActivation TEXT,Loss TEXT,Paramerter TEXT,Name TEXT,Loss_Chart_Data TEXT,Desc_input TEXT,Desc_output TEXT,Train_R2 TEXT,Train_ME TEXT,Train_MAPE TEXT,Train_MSE TEXT,Test_R2 TEXT,Test_ME TEXT,Test_MAPE TEXT,Test_MSE TEXT,Vaidation_R2 TEXT,Vaidation_ME TEXT,Vaidation_MAPE TEXT,Vaidation_MSE TEXT,PRIMARY KEY (id));";
          temp_db.exec(QString::fromStdString(query));
          temp_db.clear();

          query = "CREATE TABLE Topologys_temp (id INTEGER NOT NULL,Inputs TEXT,Outputs TEXT,Layer1Neurons TEXT,Layer2Neurons TEXT,Layer3Neurons TEXT,Layer1Activation TEXT,Layer2Activation TEXT,Layer3Activation TEXT,LastLayerActivation TEXT,Loss TEXT,Paramerter TEXT,Name TEXT,Loss_Chart_Data TEXT,Desc_input TEXT,Desc_output TEXT,Train_R2 TEXT,Train_ME TEXT,Train_MAPE TEXT,Train_MSE TEXT,Test_R2 TEXT,Test_ME TEXT,Test_MAPE TEXT,Test_MSE TEXT,Vaidation_R2 TEXT,Vaidation_ME TEXT,Vaidation_MAPE TEXT,Vaidation_MSE TEXT,PRIMARY KEY (id));";
          temp_db.exec(QString::fromStdString(query));
          temp_db.clear();
          this->db.close();
        }
    }
}
void Preproccessing::LoadDataset(){
    cout << "Start load dataset" << endl;
    DataSet temp_date_set(this->config.datasetPath.toStdString(),this->config.delimatedCharachter,true);
    cout << "set column use" << endl;
    for (int i = 0; i < this->config.dataset_columns.size(); i++) {
        switch (this->config.dataset_columns[i]) {
        case 1:
            temp_date_set.set_column_use(i,DataSet::VariableUse::Input);
            break;
        case 2:
            temp_date_set.set_column_use(i,DataSet::VariableUse::Target);
            break;
        case 0:
            temp_date_set.set_column_use(i,DataSet::VariableUse::UnusedVariable);
            break;
        default:
            temp_date_set.set_column_use(i,DataSet::VariableUse::UnusedVariable);
            break;

        }

        }
    cout << "set train test precentage " << endl;
    temp_date_set.split_samples_random(this->config.trainPrcentage,this->config.testPrcentage);
    cout << "create train file" << endl;
    int a = this->config.numberInput;
    Tensor < double,2 > training_input = temp_date_set.get_training_input_data();
    Tensor < double ,2> training_target = temp_date_set.get_training_target_data();
    cout << "create train file" << endl;



}
