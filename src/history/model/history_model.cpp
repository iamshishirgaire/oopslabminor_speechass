

#include "../../../ext_lib/json.hpp"
#include "string"
using namespace std;
using json = nlohmann::json;

class History
{

public:
    string userName;
    json assessmentResult;

    json toJson()
    {
        json jsonData;
        jsonData["userName"] = userName;
        jsonData["assessmentResult"] = assessmentResult;
        return jsonData;
    };

    History(json jsonData)
    {
        userName = jsonData["userName"];
        assessmentResult = jsonData["assessmentResult"];
    };
};