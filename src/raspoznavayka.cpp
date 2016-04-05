#include "raspoznavayka.h"

int main() {

    CInputAudio inputAudio = CInputAudio("test.wav");
    auto samples = inputAudio.getSignal();
    for ( int i = 0; i < samples.size(); ++i )
        std::cout << samples[ i ] << ' ';
    std::cout << std::endl;

    std::cout << "Success!" << std::endl;
    return 0;
}
