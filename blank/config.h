#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <QCoreApplication>
#include "enums.h"
using namespace std;


class Config
{
public:
    Config();
    int neuronNumber =  3;
    int layerNumber = 4;

    int numberInput =  3;
    int numberOutput = 1;
    double trainPrcentage = 1;
    double testPrcentage = 1;
    double validationPrcentage = 0.3;
    double learningRate = 0.001;
    double allowedRrror = 0.000001;
    vector<int> trainingActivationFunctions ={activationFunctionEnums::Linear,activationFunctionEnums::Logistic};
    vector<int> traingingStrategy ={trainingStrategyEnums::MINKOWSKI_ERROR,trainingStrategyEnums::SUM_SQUARED_ERROR};
    vector<int> optimizationMethode ={trainingStrategyEnums::MINKOWSKI_ERROR,trainingStrategyEnums::SUM_SQUARED_ERROR};
    vector<int> outActivationFunctions ={activationFunctionEnums::Linear,activationFunctionEnums::Logistic};
    bool autoSplitData=true;
    QString datasetPath = "";
    QString testDatasetPath = "";
    QString trainDatasetPath= "";
    QString validationDatasetPath= "";
    QString databasePath= "";
    char delimatedCharachter = ',';
    vector<int> dataset_columns = {1,1,1,2};
};

#endif // CONFIG_H
