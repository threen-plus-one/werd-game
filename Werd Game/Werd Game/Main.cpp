#include <algorithm>
#include <cassert>
#include "Dictionary.h"
#include <iostream>

std::vector<int> LetterHistogram( const std::string &werd )
{
	std::vector<int> hist( 26,0 );
	for( char c : werd )
	{
		assert( c >= 'a' && c <= 'z' );
		hist[c - 'a']++;
	}
	return hist;
}

int ScoreWerd( const std::string &guess,const std::string &target )
{
	const auto guessHist = LetterHistogram( guess );
	const auto targetHist = LetterHistogram( target );

	int score = 0;

	for( int i = 0; i < 26; i++ )
	{
		score += std::min( guessHist[i],targetHist[i] );
	}

	for( int i = 0; i < 5; i++ )
	{
		if( guess[i] == target[i] )
		{
			score++;
		}
	}

	return score;
}

int main()
{
	Dictionary dict;
	if( !dict.Load( "sgb-words.txt" ) )
	{
		std::cout << "Error loading dictionary" << std::endl;
		std::cin.get();
		return -1;
	}

	std::random_device rd;
	std::mt19937 rng( rd() );
	const std::string target = dict.RandomWerd( rng );
	std::string guess;
	int score;

	std::cout << "Guess the word. It is 5 letters." << std::endl;
	while( true )
	{
		std::getline( std::cin,guess );
		for( char& c : guess )
		{
			c = tolower( c );
		}

		if( guess.size() != 5 )
		{
			std::cout << "I said FIVE letter word, please." << std::endl;
			continue;
		}

		if( !dict.IzRealWerd( guess ) )
		{
			std::cout << "That's not a word, dumbass." << std::endl;
			continue;
		}

		score = ScoreWerd( guess,target );
		if( score != 10 )
		{
			std::cout << "That ain't it, but I'll give you " << score << (score == 1 ? " point" : " points") << " for effort." << std::endl;
		}
		else
		{
			std::cout << "You did it! The word is " << target << "." << std::endl;
			break;
		}
	}

	std::cin.get();
	return 0;
}