// /*
#include <iostream>
#include <stdlib.h>
#include <speechapi_cxx.h>
#include <string>
using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

string getRes()
{
    // This example requires environment variables named "SPEECH_KEY" and "SPEECH_REGION"
    auto speechKey = "e1c8701870cc4f6489dc9013048dd3f3";
    auto speechRegion = "southeastasia";

    auto speechConfig = SpeechConfig::FromSubscription(speechKey, speechRegion);

    speechConfig->SetSpeechRecognitionLanguage("en-US");

    auto pronunciationAssessmentConfig = PronunciationAssessmentConfig::CreateFromJson("{\"referenceText\":\"good morning\",\"gradingSystem\":\"HundredMark\",\"granularity\":\"Phoneme\",\"phonemeAlphabet\":\"IPA\"}");

    // auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
    auto audioConfig = AudioConfig::FromWavFileInput("assets/test1.wav");

    auto recognizer = SpeechRecognizer::FromConfig(speechConfig, audioConfig);

    // std::cout << "Speak into your microphone.\n";
    pronunciationAssessmentConfig->ApplyTo(recognizer);
    auto speechRecognitionResult = recognizer->RecognizeOnceAsync().get();

    auto pronunciationAssessmentResultJson = speechRecognitionResult->Properties.GetProperty(PropertyId::SpeechServiceResponse_JsonResult);
    cout << pronunciationAssessmentResultJson;
    return pronunciationAssessmentResultJson;
};
