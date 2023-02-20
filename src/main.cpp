
#include "repository/ass_repo.cpp"
#include "models/ass_model.cpp"
#include "core/utils/ass_view.cpp"

using namespace std;

int main()
{
    AssessmentView::viewAssessmentResult(TranscriptionResult(getRes()));
    return 0;
}