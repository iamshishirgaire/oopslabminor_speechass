// /*
#include <iostream>
#include <stdlib.h>
#include <speechapi_cxx.h>
#include <string>
#include "../../../ext_lib/json.hpp"
using namespace std;
using json = nlohmann::json;
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

string getRes(string refrenceText)
{
    // This example requires environment variables named "SPEECH_KEY" and "SPEECH_REGION"
    auto speechKey = "e1c8701870cc4f6489dc9013048dd3f3";
    auto speechRegion = "southeastasia";

    auto speechConfig = SpeechConfig::FromSubscription(speechKey, speechRegion);

    speechConfig->SetSpeechRecognitionLanguage("en-US");

    auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
    auto pronunciationAssessmentConfig = PronunciationAssessmentConfig::CreateFromJson("{\"referenceText\":\"" + refrenceText + "\",\"gradingSystem\":\"HundredMark\",\"granularity\":\"Phoneme\",\"phonemeAlphabet\":\"IPA\"}");
    // auto audioConfig = AudioConfig::FromWavFileInput("assets/test2.wav");
    std::cout << "Speak into your microphone.\n";

    auto recognizer = SpeechRecognizer::FromConfig(speechConfig, audioConfig);

    pronunciationAssessmentConfig->ApplyTo(recognizer);
    auto speechRecognitionResult = recognizer->RecognizeOnceAsync().get();

    auto pronunciationAssessmentResultJson = speechRecognitionResult->Properties.GetProperty(PropertyId::SpeechServiceResponse_JsonResult);
    cout << pronunciationAssessmentResultJson;
    return pronunciationAssessmentResultJson;
};
