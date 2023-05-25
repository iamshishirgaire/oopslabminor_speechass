//
// Created by shishirg on 2/19/23.
//

#include "iostream"
#include "colors.cpp"
#include "../../assm_result/model/ass_model.cpp"
using namespace std;

class AssessmentView
{

    ColorPalette _cp;

public:
    void viewAssessmentResult(const TranscriptionResult &trs)
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

            cout << _cp.Green << "               Word : " << wrd.Word << _cp.Green << endl;
            cout << _cp.Red << "               Pronunciation Score : " << wrd.Pronunciation.PronScore << _cp.Reset << endl;
            cout << _cp.Red << "               Completeness Score : " << wrd.Pronunciation.CompletenessScore << _cp.Reset << endl;
            cout << _cp.Red << "               Fluency Score : " << wrd.Pronunciation.FluencyScore << _cp.Reset << endl;
            cout << _cp.Red << "               Error type : " << wrd.Pronunciation.ErrorType << _cp.Reset << endl;
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
