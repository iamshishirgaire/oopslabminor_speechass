#include "vector"
#include "../../../ext_lib/json.hpp"
#include "../repository/history_repo.cpp"
#include "string"
using namespace std;
using json = nlohmann::json;

class HistoryController
{
    HistoryRepo _hr;

public:
    vector<json> getHistory(const string &userName)
    {
        return _hr.getHistory(userName);
    }

    void postHistory(const string &userName, const json &assessmentResult)
    {
        _hr.postHistory(userName, assessmentResult);
    };
};