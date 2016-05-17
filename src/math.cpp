#include "raspoznavayka.h"

namespace Raspoznavayka{
    namespace Math {
        inline std::uint8_t replaceCost( Raspoznavayka::interval_t a, Raspoznavayka::interval_t b ) {
            return abs( static_cast< std::int16_t > ( a ) - static_cast< std::int16_t > ( b ) );
    }

        // pure Levenshtein distance
        std::uint16_t levenshtein( const std::vector< Raspoznavayka::interval_t >& recordedIntervals, const std::vector< Raspoznavayka::interval_t >& databaseIntervals ) {
			std::size_t M = recordedIntervals.size();
			std::size_t N = databaseIntervals.size();
			std::vector< std::vector< std::int16_t > > D( M + 1, std::vector< std::int16_t >( N + 1 ) );
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

        std::uint16_t getLevenshtein( const CRecordedMelody& recordedMelody, const CInDBMelody& databaseMelody ) {
            auto recordedIntervals = recordedMelody.getIntervals();
			auto databaseIntervals = databaseMelody.getIntervals();
            return levenshtein( recordedIntervals, databaseIntervals );
		}

        std::uint16_t getLevenshtein( const CRecordedMelody& recordedMelody, const CInDBMelody& databaseMelody, std::int64_t offset ) {
//        if( offset < 0 )
//            offset = 0;
            auto recordedIntervals = recordedMelody.getIntervals();
			auto databaseIntervalsFull = databaseMelody.getIntervals();
			if( offset >= databaseIntervalsFull.size() )
				return std::numeric_limits< std::uint16_t >::max();
            auto databaseIntervals = std::vector< Raspoznavayka::interval_t >( databaseIntervalsFull.end() + offset, databaseIntervalsFull.end() );
            return levenshtein( recordedIntervals, databaseIntervals );
		}

        std::uint16_t getLevenshtein( const CRecordedMelody& recordedMelody, const CInDBMelody& databaseMelody, std::int64_t begin, std::int64_t end ) {
            auto recordedIntervals = recordedMelody.getIntervals();
        auto databaseIntervalsFull = databaseMelody.getIntervals();
        if( begin >= databaseIntervalsFull.size() || end < 0 )
            return std::numeric_limits< std::uint16_t >::max();
        if( end + begin > databaseIntervalsFull.size() )
            end = databaseIntervalsFull.size() - begin;
            auto databaseIntervals = std::vector< Raspoznavayka::interval_t >( databaseIntervalsFull.begin() + begin, databaseIntervalsFull.begin() + begin + end );
            return levenshtein( recordedIntervals, databaseIntervals );
    }

    std::uint16_t getLevenshtein( const CRecordedMelody& recordedMelody, const CHashMatch& hashMatch ) {
            return getLevenshtein( recordedMelody, *( hashMatch.melody ), hashMatch.offset );
    }

    std::uint16_t getLevenshtein( const CRecordedMelody& recordedMelody, const CHashMatch& hashMatch, std::int64_t end ) {
            return getLevenshtein( recordedMelody, *( hashMatch.melody ), hashMatch.offset, end );
    }

        std::uint16_t getLevenshteinFixed( const CRecordedMelody& recordedMelody, const CInDBMelody& databaseMelody, std::int64_t offset ) {
        return getLevenshtein( recordedMelody, databaseMelody, offset, recordedMelody.getLength() );
    }

    std::uint16_t getLevenshteinFixed( const CRecordedMelody& recordedMelody, const CHashMatch& hashMatch ) {
            return getLevenshteinFixed( recordedMelody, *( hashMatch.melody ), hashMatch.offset );
    }
    }
}
