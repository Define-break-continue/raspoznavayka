#include "raspoznavayka.h"

int main() {
    std::string a = "../resources/test.wav";
    CInputAudio inputAudio = CInputAudio(a);
    auto samples = inputAudio.getSignal();
    std::cout << std::endl << std::endl;
//    for ( int i = 0; i < 500/*samples.size()*/; ++i )
//        std::cout << samples[ i ] << ' ';
//    std::cout << std::endl;
    CMelody melody( samples );
    auto ints = melody.getIntervals();
    std::cout << "The Intervals:\n";
    for( auto i : ints ) std::cout << i << ' ';

    std::cout << "Success!" << std::endl;
    return 0;
}

