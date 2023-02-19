
#include "repository/get_data.h"
#include "core/utils/json_to_obj.h"
#include "core/utils/obj_to_console.h"
using namespace std;

int main()
{
    string data = getRes();
    TranscriptionResult trs = TranscriptionResult(data);
    Utilities::objToConsole(trs);
    return 0;
}