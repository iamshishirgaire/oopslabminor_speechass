#include "string"
#include <fstream>
#include "../../../ext_lib/json.hpp"

using json = nlohmann::json;
using namespace nlohmann::literals;
using namespace std;
class FileOperations
{
public:
    void readOneLine(ofstream File)
    {
        string line;
        getline(File, line);
    }
    void writeFile(string fileName, json content)
    {
        ofstream infile(fileName);
        infile << content;
        infile.close();
    }
    static ifstream openFile(const string &fileName)
    {
        ifstream file(fileName);
        ;
        return file;
    }
    static ifstream openFile(const string &fileName)
    {
        ifstream file(fileName);

        return file;
    }
    void closeFile(ofstream &file)
    {
        file.close();
    }
    void closeFile(ifstream &file)
    {
        file.close();
    }
    vector<json> readEntireFile(ifstream &file)
    {
        string line;
        vector<json> jsonData;
        while (getline(file, line))
        {
            auto jsonDat = json::parse(line);
            jsonData.push_back(jsonDat);
        }
        return jsonData;
    }
}