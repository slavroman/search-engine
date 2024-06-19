#pragma once

#include <string>
#include <vector>
#include <map>
#include <mutex>

struct Entry
{
	size_t docId; 
	size_t wordCount;	

	// This operator is required to run test scenarios
	bool operator ==(const Entry& other) const
	{
		return (docId == other.docId && wordCount == other.wordCount);
	}

	static bool compareDocId(const Entry& one, const Entry& two)
	{
		return one.docId < two.docId;
	}

	static bool compareWordCount(const Entry& one, const Entry& two)
	{
		return one.wordCount < two.wordCount;
	}
};

class InvertedIndex
{
public:
	InvertedIndex();
	~InvertedIndex();

	// Update or fill the document database that we will search
	// @param texts_input document contents
	void UpdateDocumentBase(std::vector<std::string> inputDocs);

	// The method determines the number of occurrences of the word word in the loaded document database
	// @param word is the word whose frequency of occurrences needs to be determined
	// @return returns the prepared list with the frequency of words
	std::vector<Entry> GetWordCount(const std::string& word);

private:
	std::mutex fregDicAccess;
	std::vector<std::string> textsOfDocs; // List of document contents
	std::map<std::string, std::vector<Entry>> freqDictionary; // Frequency dictionary	
	
	size_t CountingWordOccurrences(const std::string& inText, const std::string& inWord);
};

