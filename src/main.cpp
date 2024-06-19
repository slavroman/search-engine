#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

std::string ReadFile(const std::string& filePath);

int main()
{
	auto converter{ std::make_unique<ConverterJSON>() };

	auto docsPath{ converter->GetTextDocuments() };

	auto requests{ converter->GetRequests() };	
	
	//----------------------------------------------------------------------------
	//
	//
	//
	//----------------------------------------------------------------------------

	auto invIndex{ std::make_unique<InvertedIndex>() };

	std::vector<std::string> texts;

	for (const auto& path : docsPath)
	{
		texts.push_back(ReadFile(path));
	}

	invIndex->UpdateDocumentBase(texts);

	//----------------------------------------------------------------------------
	//
	//
	//
	//----------------------------------------------------------------------------

	auto maxResponses = converter->GetResponsesLimit();

	auto searchSrv = std::make_unique<SearchServer>(std::move(invIndex), maxResponses);

	auto result = searchSrv->Search(requests);

	//----------------------------------------------------------------------------
	//
	//
	//
	//----------------------------------------------------------------------------

	std::vector<std::vector<std::pair<size_t, float>>> answersToJSON;

	for (const auto& it : result)
	{
		std::vector<std::pair<size_t, float>> pairs;

		for (const auto& [docId, rank] : it)
		{
			pairs.emplace_back(std::pair(docId, rank));
		}

		answersToJSON.emplace_back(pairs);
	}

	converter->putAnswers(answersToJSON);

	std::cout << "\n\tanswers.json generated\n";	
	
	return 0;
}

std::string ReadFile(const std::string& filePath)
{
	std::string textFromFile{};

	std::ifstream inputFile(filePath);

	if (inputFile.is_open())
	{
		std::stringstream ss;
		ss << inputFile.rdbuf(); //read the file
		textFromFile = ss.str();

		inputFile.close();
	}
	else
	{
		std::cerr << "Can't open file!\n";
	}

	return textFromFile;
}
