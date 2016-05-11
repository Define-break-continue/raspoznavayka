#include "raspoznavayka.h"

#define cdatabase_main main
//#define cinputaudio_main main

int cinputaudio_main() {
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

int cdatabase_main() {
    
    std::string a = "../resources/test.wav";
    CInputAudio inputAudio = CInputAudio(a);
    auto samples = inputAudio.getSignal();
    CMelody melody( samples );
    
    /*
    std::vector< Raspoznavayka::interval_t > intervals(11);
    //for( Raspoznavayka::interval_t i = Raspoznavayka::dP4_interval; i < Raspoznavayka::A4_interval; i++ )
    for( uint8_t i = -5; i < 6; i++ )
        intervals.push_back( static_cast<Raspoznavayka::interval_t>(i) );
    CMelody melody( intervals );
    */
	CIDTag idtag = CIDTag( "title", "artist", "album", 1999 );
    CInDBMelody DBmelody( melody, idtag );
    CDataBase::getInstance().addMelody( DBmelody );
    std::cout << "OK\n";

    return 0;
}
