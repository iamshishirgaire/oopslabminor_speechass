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

        auto hrFile = FileOperations::openFileForReading(historyFile);

        auto res = FileOperations::readEntireFile(hrFile);
        FileOperations::closeFile(hrFile);
        return res;
    };
    void postHistory(const string &userName, const json &assessmentResult)
    {
        auto hrFile = FileOperations::openFileForWriting(historyFile, true);
        json jsonData;
        jsonData["userName"] = userName;
        jsonData["assessmentResult"] = assessmentResult;
        FileOperations::writeFile(hrFile, jsonData);
        FileOperations::closeFile(hrFile);
    };
};