//
// Created by shishirg on 2/19/23.
//

#include "iostream"
#include "../../assm_result/model/ass_model.cpp"
using namespace std;

class AssessmentView
{
public:
    static void viewAssessmentResult(const TranscriptionResult &trs)
    {
        cout << "--------------------------------Assessment Result------------------------------------------" << endl;

        cout << "Id : " << trs.Id << endl;
        cout << "Recognition status :" << trs.RecognitionStatus << endl;
        cout << "Display Text :" << trs.DisplayText << endl;
        cout << "SNR :" << trs.SNR << endl;
        cout << "Confidence : " << trs.nBest[0].Confidence << endl;
        cout << "--------------------------------Pronunciation Assessment-----------------------------------" << endl;

        auto pronAss = trs.nBest[0].pronunciationAssessment;
        cout << "      Accuracy Score : " << pronAss.AccuracyScore << endl;
        cout << "      Fluency Score : " << pronAss.FluencyScore << endl;
        cout << "      Completeness Score : " << pronAss.CompletenessScore << endl;
        cout << "      Pronunciation Score : " << pronAss.PronScore << endl;
        cout << "-----------Words Assessment------------" << endl;
        auto words = trs.nBest[0].Words;

        for (auto &wrd : words)
        {

            cout << "               Word : " << wrd.Word << endl;
            cout << "               Pronunciation Score : " << wrd.Pronunciation.PronScore << endl;
            cout << "               Completeness Score : " << wrd.Pronunciation.CompletenessScore << endl;
            cout << "               Fluency Score : " << wrd.Pronunciation.FluencyScore << endl;
            cout << "               Error type : " << wrd.Pronunciation.ErrorType << endl;
            auto syllables = wrd.Syllables;

            for (auto &syll : syllables)
            {
                cout << "                                    Syllable : " << syll.Syllable << endl;
                cout << "                                    Accuracy Score : " << syll.Pronunciation.AccuracyScore << endl;
                cout << "                                    Duration : " << syll.Duration << endl;
                cout << "                                    Offset : " << syll.Offset << endl
                     << endl;
            }
        }
    }
};
