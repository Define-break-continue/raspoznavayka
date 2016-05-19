#include "raspoznavayka.h"

//#define cdatabase_main main
//#define cinputaudio_main main
//#define levenshtein_main main
#define the_mainest_main main

int the_mainest_main( int argc, char *argv[] ) {
    
    for( int argn = 1; argn < argc; ++argn ) {
        std::string args = std::string( argv[argn] );
        if( args == "-a" ) { // add to database
            if( argn < argc ) {
                std::string audio_file = std::string( argv[++argn] );
                CInputAudio inputAudio = CInputAudio( audio_file );
                auto samples = inputAudio.getSignal();
                CMelody melody( samples );
                //CIDTag idtag = CIDTag( "title", "artist", "album", 1999 );
                CIDTag idtag = CIDTag(); // ask for tag values
                idtag.interactive_fill();
                CInDBMelody DBmelody( melody, idtag );
                if( CDataBase::getInstance().addMelody( DBmelody ) ) {
                    std::cout << "Melody added to database\n";
                } else {
                    std::cout << "Something has gone wrong\n";
                }
            }
            else {
                std::cout << "No audio file name to add provided!\n";
            }
        }
        else if( args == "-s" ) { // sarch
            if( argn + 1 < argc ) {
                std::string audio_file = std::string( argv[++argn] );
                CInputAudio inputAudio = CInputAudio( audio_file );
                auto samples = inputAudio.getSignal();
                CRecordedMelody rec_melody( samples );
                CHash hash ( rec_melody ); 
                std::vector< CInDBMelody > db_search =
                    CDataBase::getInstance().searchByHash( hash );
                for( std::vector< CInDBMelody >::iterator i = db_search.begin();
                        i < db_search.end(); ++i ) {
                    std::cout << "intervals: ";
                    (*i).printIntervals();
                    std::cout << (*i).getIDTag().artist << " - " 
                              << (*i).getIDTag().title << " : "
                              << Raspoznavayka::Math::getLevenshtein( 
                                      rec_melody, (*i) ) 
                              << '\n';
                }
            }
            else {
                std::cout << "No audio file name to add provided!\n";
            }
        }
        else if( args == "-k" ) { // kostyl sarch
            if( argn + 1 < argc ) {
                std::string audio_file = std::string( argv[++argn] );
                CInputAudio inputAudio = CInputAudio( audio_file );
                auto samples = inputAudio.getSignal();
                CRecordedMelody rec_melody( samples );
                CHash hash ( rec_melody ); 
                std::vector< CInDBMelody > db_search =
                    CDataBase::getInstance().getEverything();
                for( std::vector< CInDBMelody >::iterator i = db_search.begin();
                        i < db_search.end(); ++i ) {
                    std::cout << "intervals: ";
                    (*i).printIntervals();
                    std::cout << (*i).getIDTag().artist << " - " 
                              << (*i).getIDTag().title << " : "
                              << Raspoznavayka::Math::getLevenshtein( 
                                      rec_melody, (*i) ) 
                              << '\n';
                }
            }
            else {
                std::cout << "No audio file name to add provided!\n";
            }
        }
        else if( args == "-ms" ) { // microphone search
            CInput micInput;
            auto samples = micInput.RecordMelody();
			CRecordedMelody rec_melody( samples );
			CHash hash ( rec_melody ); 
			std::vector< CInDBMelody > db_search =
				CDataBase::getInstance().searchByHash( hash );
			for( std::vector< CInDBMelody >::iterator i = db_search.begin();
					i < db_search.end(); ++i ) {
				std::cout << "intervals: ";
				(*i).printIntervals();
				std::cout << (*i).getIDTag().artist << " - " 
						  << (*i).getIDTag().title << " : "
						  << Raspoznavayka::Math::getLevenshtein( 
								  rec_melody, (*i) ) 
						  << '\n';
			}
        }
        else if( args == "-mk" ) { // microphone kostyl search
            CInput micInput;
            auto samples = micInput.RecordMelody();
            CRecordedMelody rec_melody( samples );
            CHash hash ( rec_melody ); 
            std::vector< CInDBMelody > db_search =
                CDataBase::getInstance().getEverything();
            for( std::vector< CInDBMelody >::iterator i = db_search.begin();
                    i < db_search.end(); ++i ) {
                std::cout << "intervals: ";
                (*i).printIntervals();
                std::cout << (*i).getIDTag().artist << " - " 
                          << (*i).getIDTag().title << " : "
                          << Raspoznavayka::Math::getLevenshtein( 
                                  rec_melody, (*i) ) 
                          << '\n';
            }
        }
    }
    
    return 0;
}


int levenshtein_main() {
    std::vector< Raspoznavayka::interval_t > a( 0 ), b( 0 );
    for( int i = 0; i < 5; ++i ) {
        a.push_back( static_cast< Raspoznavayka::interval_t >( i ) );
    }
    for( int i = 0; i < 5; ++i ) {
        b.push_back( static_cast< Raspoznavayka::interval_t >( i ) );
    }
    b[3] = static_cast< Raspoznavayka::interval_t >( 0 );
    std::vector< Raspoznavayka::interval_t > c( 0 );
    c.push_back( static_cast< Raspoznavayka::interval_t >( 3 ) );
    std::cout << Raspoznavayka::Math::levenshtein( a, b ) << std::endl;
	return 0;
}

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

int cdatabase_main( int argc, char *argv[] ) {
    
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
    if( argc > 1 && std::string( argv[1] ) == "-a" )
        CDataBase::getInstance().addMelody( DBmelody );
    CHash hash ( melody ); 
    CDataBase::getInstance().searchByHash( hash );
    std::cout << "OK\n";

    return 0;
}
