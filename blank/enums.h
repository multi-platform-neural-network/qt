#ifndef ENUMS_H
#define ENUMS_H
#include <iostream>
#include <QCoreApplication>
#include "../opennn/opennn.h"
using namespace OpenNN;
using namespace std;
class activationFunctionEnums{
public:
       enum ProjectType{Threshold, SymmetricThreshold, Logistic, HyperbolicTangent, Linear,RectifiedLinear,ExponentialLinear,ScaledExponentialLinear,SoftPlus,SoftSign,HardSigmoid};
};

class trainingStrategyEnums{
public:

    enum ProjectType{SUM_SQUARED_ERROR, MEAN_SQUARED_ERROR, NORMALIZED_SQUARED_ERROR, MINKOWSKI_ERROR, WEIGHTED_SQUARED_ERROR,CROSS_ENTROPY_ERROR};

};
class optimizationMethodeEnums{
public:
        enum ProjectType{GRADIENT_DESCENT, CONJUGATE_GRADIENT, QUASI_NEWTON_METHOD, LEVENBERG_MARQUARDT_ALGORITHM, STOCHASTIC_GRADIENT_DESCENT,ADAPTIVE_MOMENT_ESTIMATION};
};

class DatasetStructure{
public:
    DataSet date_set;
    Tensor<Descriptives, 1> inputs_descriptives,target_descriptives;
    Index input_variables_number,target_variables_number;
    Tensor<string, 1> targets_names,inputs_names;
    Tensor<string, 1> scaling_inputs_methods,scaling_target_methods;
};


class enums
{
public:
    enums();



private:
};

#endif // ENUMS_H
