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
    auto speechKey = "1751c5d21b2241ac96c610c759b9d33e";
    auto speechRegion = "southeastasia";

    string jsonResult;
    auto config = SpeechConfig::FromSubscription(speechKey, speechRegion);

    // The pronunciation assessment service has a longer default end silence timeout (5 seconds) than normal STT
    // as the pronunciation assessment is widely used in education scenario where kids have longer break in reading.
    // You can adjust the end silence timeout based on your real scenario.
    config->SetProperty(PropertyId::SpeechServiceConnection_EndSilenceTimeoutMs, "3000");

    std::string referenceText = "";
    // auto pronunciationConfig = PronunciationAssessmentConfig::CreateFromJson("{\"referenceText\":\"" + refrenceText + "\",\"gradingSystem\":\"HundredMark\",\"granularity\":\"Phoneme\",\"phonemeAlphabet\":\"IPA\"}");

    // create pronunciation assessment config, set grading system, granularity and if enable miscue based on your requirement.
    auto pronunciationConfig = PronunciationAssessmentConfig::Create(referenceText,
                                                                     PronunciationAssessmentGradingSystem::HundredMark,
                                                                     PronunciationAssessmentGranularity::Phoneme, true);

    // Creates a speech recognizer using microphone as audio input.
    auto recognizer = SpeechRecognizer::FromConfig(config);

    // Receives reference text from console input.
    cout << "Enter reference text that you want to assess, or enter empty text to exit." << std::endl;
    cout << "> ";
    getline(cin, referenceText);
    if (referenceText.empty())
    {
        cout << "Empty Text Found";
        exit(0);
    }

    pronunciationConfig->SetReferenceText(referenceText);
    cout << "Read out \"" << referenceText << "\" for pronunciation assessment ..." << endl;

    pronunciationConfig->ApplyTo(recognizer);

    // Starts speech recognition, and returns after a single utterance is recognized.
    // For long-running multi-utterance recognition, use StartContinuousRecognitionAsync() instead.
    auto result = recognizer->RecognizeOnceAsync().get();

    // Checks result.
    if (result->Reason == ResultReason::RecognizedSpeech)
    {
        cout << "RECOGNIZED: Text=" << result->Text << std::endl
             << "  PRONUNCIATION ASSESSMENT RESULTS:";

        // auto pronunciationResult = PronunciationAssessmentResult::FromResult(result);
        auto pronunciationAssessmentResultJson = result->Properties.GetProperty(PropertyId::SpeechServiceResponse_JsonResult);

        // cout << "    Accuracy score: " << pronunciationResult->AccuracyScore << ", Pronunciation score: "
        //      << pronunciationResult->PronunciationScore << ", Completeness score : " << pronunciationResult->CompletenessScore
        //      << ", FluencyScore: " << pronunciationResult->FluencyScore << endl;

        jsonResult = pronunciationAssessmentResultJson;
    }
    else if (result->Reason == ResultReason::NoMatch)
    {
        cout << "NOMATCH: Speech could not be recognized." << std::endl;
    }
    else if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = CancellationDetails::FromResult(result);
        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails << std::endl;
            cout << "CANCELED: Did you update the subscription info?" << std::endl;
        }
    }

    return jsonResult;
}
