#pragma once

#include <vector>
#include <string>

class ConverterJSON
{
public:
	ConverterJSON();
	~ConverterJSON();
		
	// Method for getting file contents
	// @return Returns a list with the contents
	// of the files listed in "config.json"	
	std::vector<std::string> GetTextDocuments();

	// The method reads the max_responses fiitd to determine
	// the maximum number of responses to one @return request
	size_t GetResponsesLimit();

	// Method for receiving requests from the "requests.json" file
	// @return returns a list of requests from the "requests.json" file
	std::vector<std::string> GetRequests();

	// Put search query results in the "answers.json" file
	void putAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers);

private:		
	size_t responsesLimit;
};
