#include "vector"
#include "../../../ext_lib/json.hpp"
#include "string"
#include "../../core/utils/file_operations.cpp"
using namespace std;
using json = nlohmann::json;

class HistoryRepo
{

    FileOperations fos;
    vector<json> getHistory(string userName)
    {
        return fos.readEntireFile()
    }

    void postHistory(string userName, json assessmentResult)
    {

        json jsonData;
        jsonData["userName"] = userName;
        jsonData["assessmentResult"] = assessmentResult;
    }

public:
}