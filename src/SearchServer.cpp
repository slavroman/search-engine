#include "SearchServer.h"
#include <iostream>
#include <sstream>
#include <algorithm>

SearchServer::SearchServer(std::unique_ptr<InvertedIndex> idx, size_t responsesLimit)
	: invIdx(std::move(idx)), maxResponses(responsesLimit)
{
}

SearchServer::~SearchServer()
{
}

std::vector<std::vector<RelativeIndex>> SearchServer::Search(const std::vector<std::string>& queriesInput)
{
    std::vector<std::vector<RelativeIndex>> result;  

    // Query words string
    for (const auto& query : queriesInput)
    {
        auto uniqueWords = SplitIntoUniqueWords(query);        

        std::map<size_t/*docId*/, size_t/*wordCount*/> absRelevances;

        size_t absRelevanceMax{ 0 };

        for (const auto& word : uniqueWords)
        {
            auto wordFrequency = invIdx->GetWordCount(word);

            for (const auto& [id, count] : wordFrequency)
            {
                if (absRelevances.count(id))
                {
                    absRelevances[id] += count;
                }
                else
                {
                    absRelevances.insert(std::pair(id, count));
                }

                // Calculating absolute relevance
                absRelevanceMax = std::max(absRelevanceMax, absRelevances[id]);
            }                
        }
                        
        std::vector<RelativeIndex> relRelevances;

        // Fill relative relevances
        if (absRelevances.size())
        {
            for (const auto& [id, absRel] : absRelevances)
            {
                auto relRelevance = static_cast<float>(absRel) / absRelevanceMax;

                RelativeIndex newRelativeIndex{ /*docId*/id , /*rank*/relRelevance };
                relRelevances.push_back(newRelativeIndex);                    
            }

            // Sort relative relevances by rank
            std::sort(relRelevances.begin(), relRelevances.end(), RelativeIndex::reverseCompareByRank);                
        }            
            
        // Maximum number of responses per request
        if (relRelevances.size() > maxResponses)
        {
            relRelevances.resize(maxResponses);
        }        

        result.push_back(relRelevances);
    }

    return result;
}

std::vector<std::string> SearchServer::SplitIntoUniqueWords(const std::string& inText)
{
    std::vector<std::string> uniqueWords{};

    std::string word{};

    std::stringstream ss(inText);

    while (ss >> word)
    {
        if (!uniqueWords.empty())
        {
            // Word not found
            if (std::find(uniqueWords.begin(), uniqueWords.end(), word) == uniqueWords.end())
            {
                uniqueWords.push_back(word);
            }
        }
        else
        {
            uniqueWords.push_back(word);
        }
    }

    return uniqueWords;
}
