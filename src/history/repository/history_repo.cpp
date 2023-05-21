#include "vector"
#include "../../../ext_lib/json.hpp"
#include "string"
#include "../../core/utils/file_operations.cpp"
using namespace std;
using json = nlohmann::json;

class HistoryRepo
{
    string historyFile = "/home/iamshishirg/Documents/oopslabminor_speechass/database/history/history.csv";

public:
    vector<json> getHistory(const string &userName)
    {
        ifstream file(historyFile);
        return FileOperations::readEntireFile(file);
    };
    void postHistory(const string &userName, const json &assessmentResult)
    {
        ofstream file(historyFile);

        auto temp = FileOperations::openFileForWriting(historyFile, assessmentResult);
        json jsonData;
        jsonData["userName"] = userName;
        jsonData["assessmentResult"] = assessmentResult;
        FileOperations::writeFile(file, jsonData);
        FileOperations::closeFile(file);
    };
};