#include "Dictionary.h"

#include <fstream>

bool Dictionary::Load( const std::string &filename )
{
	std::ifstream dictFile( filename );
	if( !dictFile )
	{
		return false;
	}

	for( std::string line; std::getline( dictFile,line ); )
	{
		if( !line.empty() )
		{
			werdz.push_back( line );
		}
	}

	dictFile.close();
	return true;
}

const std::string &Dictionary::RandomWerd( std::mt19937 &rng ) const
{
	std::uniform_int_distribution<size_t> dist( 0,werdz.size() - 1 );
	return werdz[dist( rng )];
}

bool Dictionary::IzRealWerd( const std::string &werd )
{
	for( const auto& w : werdz )
	{
		if( w == werd )
		{
			return true;
		}
	}
	return false;
}
