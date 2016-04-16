#include "raspoznavayka.h"

int main() {
    std::string a = "../resources/test.wav";
    CInputAudio inputAudio = CInputAudio(a);
    auto samples = inputAudio.getSignal();
    std::cout << std::endl << std::endl;
    for ( int i = 0; i < 100/*samples.size()*/; ++i )
        std::cout << samples[ i ] << ' ';
    std::cout << std::endl;

    std::cout << "Success!" << std::endl;
    return 0;
}
