// *********************************************************************************************************************
// Description:		RandomShuffle algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	BeA
//
// *********************************************************************************************************************

#ifndef RANDOMSHUFFLE_HPP
#define RANDOMSHUFFLE_HPP

#pragma once

#include <algorithm>
#include <random>

#include "STLIteratorConnection.hpp"

namespace GS {

template <class Ran>
void	 RandomShuffle (Ran first, Ran last)
{
	std::random_device rd;
	std::mt19937 g (rd ());
	std::shuffle (first, last, g);
}


template <class Ran>
void	 DeterministicRandomShuffle (Ran first, Ran last, typename std::mt19937::result_type seed = std::mt19937::default_seed)
{
	std::mt19937 g (seed);
	std::shuffle (first, last, g);
}

}	// namespace GS


#endif