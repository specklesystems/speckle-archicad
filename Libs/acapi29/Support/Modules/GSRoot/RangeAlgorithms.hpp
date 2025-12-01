
// *****************************************************************************
//
//                                Range algorithms
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	NN
//
// SG compatible
//
// *****************************************************************************


#if !defined RANGEALGORITHMS_HPP
#define RANGEALGORITHMS_HPP

#pragma once

// ============================== Range algorithms ==============================

namespace GS {

	// --- Partition ---

template<typename InputRange, typename OutputContainer, typename PartitionFunction>
void Partition (const InputRange& inputRange, OutputContainer& trueContainer, OutputContainer& falseContainer, const PartitionFunction& partitionFunction)
{
	auto trueInserter = GetInserter (trueContainer);
	auto falseInserter = GetInserter (falseContainer);

	for (const auto& elem : inputRange) {
		if (partitionFunction (elem)) {
			trueInserter (elem);
		} else {
			falseInserter (elem);
		}
	}
}

}	// namespace GS
// ______________________________ Range algorithms ______________________________


#endif
