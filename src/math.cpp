#include "raspoznavayka.h"

namespace Raspoznavayka{
    namespace Math {
        inline std::uint8_t replaceCost( Raspoznavayka::interval_t a, Raspoznavayka::interval_t b ) {
            return static_cast< std::uint8_t >( abs( static_cast< std::int8_t > ( a ) - static_cast< std::int8_t > ( b ) ) ) * LEVENSHTEIN_REPLACE_COST_COEFFICIENT;
	}

        // pure Levenshtein distance
        std::uint16_t levenshtein( std::vector< Raspoznavayka::interval_t >& recordedIntervals, std::vector< Raspoznavayka::interval_t >& databaseIntervals ) {
	    std::size_t M = recordedIntervals.size() + 1;
	    std::size_t N = databaseIntervals.size() + 1;
	    std::vector< std::vector< std::int8_t > > D( M, std::vector< std::int8_t >( N ) );
	    D[ 0 ][ 0 ] = 0;
	    for( std::size_t j = 1; j <= N; ++j ) {
                D[ 0 ][ j ] = D[ 0 ][ j - 1 ] + LEVENSHTEIN_INSERT_COST;
	    }
	    for( std::size_t i = 1; i <= M; ++i ) {
                D[ i ][ 0 ] = D[ i - 1 ][ 0 ] + LEVENSHTEIN_DELETE_COST;
		for( std::size_t j = 1; j <= N; ++j ) {
                    D[ i ][ j ] = std::min( {
                        D[ i - 1 ][ j ] + LEVENSHTEIN_DELETE_COST,
			D[ i ][ j - 1 ] + LEVENSHTEIN_INSERT_COST,
			D[ i - 1 ][ j - 1 ] + replaceCost( recordedIntervals[ i ], databaseIntervals[ j ] )
		    } );
		}
	    }
	    return D[ M ][ N ];
	}

        std::uint16_t getLevenshtein( CRecordedMelody& recordedMelody, CInDBMelody& databaseMelody, std::size_t begin, std::size_t end ) {
	    if( end == 0 )
	        end = recordedMelody.getLength();
            auto recordedIntervals = recordedMelody.getIntervals();
	    auto databaseIntervalsFull = databaseMelody.getIntervals();
	    if( begin >= databaseIntervalsFull.size() || end < begin )
	        return std::numeric_limits< std::uint16_t >::max();
	    if( end - begin >= databaseIntervalsFull.size() )
	        end = databaseIntervalsFull.size() - begin;
            auto databaseIntervals = std::vector< Raspoznavayka::interval_t >( databaseIntervalsFull.begin() + begin, databaseIntervalsFull.begin() + end );
            return levenshtein( recordedIntervals, databaseIntervals );
	}
    }
}
