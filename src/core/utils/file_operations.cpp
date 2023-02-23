#include "string"
#include <fstream>
#include "../../../ext_lib/json.hpp"

using json = nlohmann::json;
using namespace nlohmann::literals;
using namespace std;
class FileOperations
{
public:
    string readOneLine(ifstream &File)
    {
        string line;
        getline(File, line);
        return line;
    }
    void writeFile(ofstream &infile, json content)
    {
        infile << content;
        infile.close();
    }
    static ifstream openFileForReading(const string &fileName)
    {
        ifstream file(fileName);
        ;
        return file;
    }
    static ofstream openFileForWriting(const string &fileName, bool append)
    {
        if (append)
        {
            ofstream file(fileName, ios::app);
            return file;
        }
        else
        {
            ofstream file(fileName);
            return file;
        }
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
};