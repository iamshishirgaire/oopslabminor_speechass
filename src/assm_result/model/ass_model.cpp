//
// Created by shishirg on 2/18/23.
//

#include <iostream>
#include <vector>
#include <string>
#include "../../../ext_lib/json.hpp"
using json = nlohmann::json;

class PronunciationAssessment
{
public:
    double AccuracyScore{};
    double FluencyScore{};
    double CompletenessScore{};
    double PronScore{};
    std::string ErrorType;
};

class Syllable
{
public:
    std::string Syllable;
    PronunciationAssessment Pronunciation;
    int Offset{};
    int Duration{};
};

class Phoneme
{
public:
    std::string Phoneme;
    PronunciationAssessment Pronunciation;
    int Offset{};
    int Duration{};
};

class Word
{
public:
    std::string Word;
    int Offset{};
    int Duration{};
    PronunciationAssessment Pronunciation;
    std::vector<Syllable> Syllables;
    std::vector<Phoneme> Phonemes;
};

class NBest
{
public:
    double Confidence{};
    std::string Lexical;
    std::string ITN;
    std::string MaskedITN;
    std::string Display;
    PronunciationAssessment pronunciationAssessment;
    std::vector<Word> Words;
};

class TranscriptionResult
{
public:
    std::string Id;
    std::string RecognitionStatus;
    int Offset;
    int Duration;
    int Channel;
    std::string DisplayText;
    double SNR;
    std::vector<NBest> nBest;

    explicit TranscriptionResult(const std::string &jsonStr)
    {
        json j = json::parse(jsonStr);
        Id = j["Id"];
        RecognitionStatus = j["RecognitionStatus"];
        Offset = j["Offset"];
        Duration = j["Duration"];
        Channel = j["Channel"];
        DisplayText = j["DisplayText"];
        SNR = j["SNR"];
        for (auto nb : j["NBest"])
        {
            class NBest nbest;
            nbest.Confidence = nb["Confidence"];
            nbest.Lexical = nb["Lexical"];
            nbest.ITN = nb["ITN"];
            nbest.MaskedITN = nb["MaskedITN"];
            nbest.Display = nb["Display"];
            auto pa = nb["PronunciationAssessment"];
            nbest.pronunciationAssessment.AccuracyScore = pa["AccuracyScore"];
            nbest.pronunciationAssessment.FluencyScore = pa["FluencyScore"];
            nbest.pronunciationAssessment.CompletenessScore = pa["CompletenessScore"];
            nbest.pronunciationAssessment.PronScore = pa["PronScore"];

            for (auto word : nb["Words"])
            {
                Word w;
                w.Word = word["Word"];
                w.Offset = word["Offset"];
                w.Duration = word["Duration"];
                auto paa = word["PronunciationAssessment"];
                w.Pronunciation.AccuracyScore = paa["AccuracyScore"];
                w.Pronunciation.ErrorType = paa["ErrorType"];
                for (auto syl : word["Syllables"])
                {
                    Syllable s;
                    s.Syllable = syl["Syllable"];
                    s.Offset = syl["Offset"];
                    s.Duration = syl["Duration"];
                    auto syl1 = syl["PronunciationAssessment"];

                    s.Pronunciation.AccuracyScore = syl1["AccuracyScore"];

                    w.Syllables.push_back(s);
                }
                for (auto phon : word["Phonemes"])
                {
                    Phoneme p;
                    p.Phoneme = phon["Phoneme"];
                    p.Offset = phon["Offset"];
                    p.Duration = phon["Duration"];
                    auto phon2 = phon["PronunciationAssessment"];
                    p.Pronunciation.AccuracyScore = phon2["AccuracyScore"];
                    w.Phonemes.push_back(p);
                }
                nbest.Words.push_back(w);
            }
            nBest.push_back(nbest);
        }
    };
};
