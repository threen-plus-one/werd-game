#pragma once

#include <vector>
#include <string>
#include <random>

class Dictionary
{
	std::vector<std::string> werdz;

public:
	bool Load( const std::string &filename );
	const std::string &RandomWerd( std::mt19937 &rng ) const;
	bool IzRealWerd( const std::string &werd );
};