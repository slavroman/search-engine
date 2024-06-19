#include "InvertedIndex.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <regex>

InvertedIndex::InvertedIndex()
{
}

InvertedIndex::~InvertedIndex()
{
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs)
{
    if (!textsOfDocs.empty())
    {
        textsOfDocs.clear();
    }
    
    // Fill List of document contents
    textsOfDocs = inputDocs;

    freqDictionary.clear();

    std::vector<std::thread> poolThreads;

    // Fill Frequency dictionary
    for (size_t docIdx = 0; docIdx < textsOfDocs.size(); ++docIdx)
    {
        poolThreads.emplace_back(std::thread([this, docIdx]()
        {
            std::string wordForSearch{};

            std::stringstream ss(textsOfDocs[docIdx]);

            while (ss >> wordForSearch)
            {
                // Convert word to lowercase
                std::for_each(wordForSearch.begin(), wordForSearch.end(), [](char& ch)
                {
                    ch = tolower(ch);
                });

                // Getting number occurrences word in the current doc
                auto countOccurrences = CountingWordOccurrences(textsOfDocs[docIdx], wordForSearch);

                if (countOccurrences)
                {
                    Entry newEntry{ docIdx, countOccurrences };

                    {
                        std::scoped_lock guard(fregDicAccess); // According C++17 standard

                        // Check if word key present in Frequency dictionary
                        auto dictionaryIt = freqDictionary.find(wordForSearch);

                        if (dictionaryIt != freqDictionary.end())
                        {
                            // Check if doc id value present in Frequency dictionary
                            auto vecEntryIt = std::find_if(dictionaryIt->second.begin(), dictionaryIt->second.end(), [&docIdx](const Entry& obj)
                            {
                                return obj.docId == docIdx;
                            });

                            // Value not present in Frequency dictionary
                            if (vecEntryIt == dictionaryIt->second.end())
                            {
                                dictionaryIt->second.push_back(newEntry);

                                std::sort(dictionaryIt->second.begin(), dictionaryIt->second.end(), Entry::compareDocId);
                            }
                        }
                        else
                        {
                            freqDictionary.insert(std::pair<std::string, std::vector<Entry>>(wordForSearch, std::vector<Entry>{newEntry}));
                        }
                    }
                }           
            }
        }));
    }    

    for (auto& currThread : poolThreads)
    {
        currThread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> wordFrequencyList{};

    //   Key: string word
    // Value: vector structures Entry {size_t DocId, size_t wordCount}

    if (!textsOfDocs.empty() && !freqDictionary.empty())
    { 
        if (freqDictionary.count(word))
        {
            for (const auto& entry : freqDictionary[word])
            {
                wordFrequencyList.emplace_back(entry);
            }
        }        
    }    

    return wordFrequencyList;
}

size_t InvertedIndex::CountingWordOccurrences(const std::string& inText, const std::string& inWord)
{
    size_t wordsCount{ 0 };
    
    std::regex word("\\b" + inWord + "\\b");

    auto matchCount(
        std::distance(std::sregex_iterator(inText.begin(), inText.end(), word),
        std::sregex_iterator()));

    wordsCount = matchCount;

    return wordsCount;
}
