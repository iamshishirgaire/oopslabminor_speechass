#include "string"
#include "../repository/ass_repo.cpp"
using namespace std;

class AssessmentController
{

public:
    static string getAssessmentRes()
    {
        return getRes();
    };
};