#pragma once

#include "InvertedIndex.h"
#include <string>
#include <vector>
#include <memory>

struct RelativeIndex
{
	size_t docId;
	float rank;

	bool operator ==(const RelativeIndex& other) const
	{
		return (docId == other.docId && rank == other.rank);
	}

	static bool reverseCompareByRank(const RelativeIndex& one, const RelativeIndex& two)
	{
		return one.rank > two.rank;
	}
};

class SearchServer
{
public:
	// @param idx passes a reference to class InvertedIndex to class constructor,
	// so that SearchServer can find out the frequency of words found in the query
	SearchServer(std::unique_ptr<InvertedIndex> idx, size_t responsesLimit);
	~SearchServer();

	// Method for processing search queries
	// @param queriesInput search queries taken from the requests.json file
	// @return returns a sorted list of relevant answers for the given queries
	std::vector<std::vector<RelativeIndex>> Search(const std::vector<std::string>& queriesInput);

private:
	std::unique_ptr<InvertedIndex> invIdx;
	size_t maxResponses;

	std::vector<std::string> SplitIntoUniqueWords(const std::string& inText);
};
