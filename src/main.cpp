
#include "assm_result/model/ass_model.cpp"
#include "assm_result/repository/ass_repo.cpp"

#include "core/utils/ass_view.cpp"

using namespace std;

int main()
{
    AssessmentView::viewAssessmentResult(TranscriptionResult(getRes()));
    return 0;
}