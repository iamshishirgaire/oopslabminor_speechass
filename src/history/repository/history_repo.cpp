#include "vector"
#include "../../../ext_lib/json.hpp"
#include "string"
#include "../../core/utils/file_operations.cpp"
using namespace std;
using json = nlohmann::json;

class HistoryRepo
{
    string historyFile = "/home/iamshishirg/Documents/oopslabminor_speechass/database/history/history.csv";
    AuthController _ac;

public:
    vector<json> getHistory(const string &userName)
    {
        vector<json> result;

        auto hrFile = FileOperations::openFileForReading(historyFile);
        auto res = FileOperations::readEntireFile(hrFile);
        string user = res[0]["username"];
        FileOperations::closeFile(hrFile);

        for (int i = 0; i < res.size(); i++)
        {
            if (res[i]["username"] == userName)
            {
                result.push_back(res[i]);
            }
        }
        return result;
    };
    void postHistory(const json &assessmentResult)
    {
        json user = _ac.getcurrentUser();
        string userName = user["username"];
        auto hrFile = FileOperations::openFileForWriting(historyFile, true);
        json jsonData;
        jsonData["username"] = userName;
        jsonData["result"] = assessmentResult;
        FileOperations::writeFile(hrFile, jsonData);
        FileOperations::closeFile(hrFile);
    };
};