#include "vector"
#include "../../../ext_lib/json.hpp"
#include "string"
#include "../../core/utils/file_operations.cpp"
using namespace std;
using json = nlohmann::json;

class HistoryRepo
{
    string historyFile = "../../../database/history/history.csv";
    FileOperations fos;

public:
    vector<json> getHistory(string userName)
    {
        return fos.readEntireFile(historyFile);
    };
    void postHistory(string userName, json assessmentResult)
    {
        auto temp = fos.openFileForWriting(historyFile);
        json jsonData;
        jsonData["userName"] = userName;
        jsonData["assessmentResult"] = assessmentResult;
        fos.writeFile(historyFile, jsonData);
        fos.closeFile(historyFile);
    };
};