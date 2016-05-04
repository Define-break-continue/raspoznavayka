#include "raspoznavayka.h"

//#define cdatabase_main main
#define cinputaudio_main main

int cinputaudio_main() {
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

int cdatabase_main() {
//	CDataBase::getInstance();
	std::cout << "OK\n";

	return 0;
}
