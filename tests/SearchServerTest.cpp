#include "SearchServer.h"
#include "InvertedIndex.h"
#include <gtest/gtest.h>
#include <memory>

void TestSearchServerFunctionality(const std::vector<std::string>& docs,
								   const std::vector<std::string>& request,
								   const std::vector<std::vector<RelativeIndex>>& expected,
								   const size_t responsesLimit)
{
	auto idx{ std::make_unique<InvertedIndex>() };

	idx->UpdateDocumentBase(docs);

	auto srv = std::make_unique<SearchServer>(std::move(idx), responsesLimit);

	std::vector<std::vector<RelativeIndex>> result = srv->Search(request);

	ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestSimple)
{
	const std::vector<std::string> docs =
	{
		"milk milk milk milk water water water",                  // Doc Id: 0
		"milk water water",                                       // Doc Id: 1
		"milk milk milk milk milk water water water water water", // Doc Id: 2
		"americano cappuccino"                                    // Doc Id: 3
	};

	const std::vector<std::string> request = { "milk water", "sugar" };

	const std::vector<std::vector<RelativeIndex>> expected =
	{
		{
			{2, 1},   // R_abs: 5 + 5 = 10, R_rels: 10 / 10 = 1
			{0, 0.7}, // R_abs: 4 + 3 =  7, R_rels:  7 / 10 = 0.7
			{1, 0.3}  // R_abs: 1 + 2 =  3, R_rels:  3 / 10 = 0.3
		},
		{
		}
	};

	TestSearchServerFunctionality(docs, request, expected, 3);
}

TEST(TestCaseSearchServer, TestTop5)
{
	const std::vector<std::string> docs =
	{
		"london is the capital of great britain",                 // Doc Id: 0
		"paris is the capital of france",                         // Doc Id: 1
		"berlin is the capital of germany",                       // Doc Id: 2
		"rome is the capital of italy",                           // Doc Id: 3
		"madrid is the capital of spain",                         // Doc Id: 4
		"lisboa is the capital of portugal",                      // Doc Id: 5
		"bern is the capital of switzerland",                     // Doc Id: 6
		"moscow is the capital of russia",                        // Doc Id: 7
		"kiev is the capital of ukraine",                         // Doc Id: 8
		"minsk is the capital of belarus",                        // Doc Id: 9
		"astana is the capital of kazakhstan",                    // Doc Id: 10
		"beijing is the capital of china",                        // Doc Id: 11
		"tokyo is the capital of japan",                          // Doc Id: 12
		"bangkok is the capital of thailand",                     // Doc Id: 13
		"welcome to moscow the capital of russia the third rome", // Doc Id: 14
		"amsterdam is the capital of netherlands",                // Doc Id: 15
		"helsinki is the capital of finland",                     // Doc Id: 16
		"oslo is the capital of norway",                          // Doc Id: 17
		"stockholm is the capital of sweden",                     // Doc Id: 18
		"riga is the capital of latvia",                          // Doc Id: 19
		"tallinn is the capital of estonia",                      // Doc Id: 20
		"warsaw is the capital of poland"                         // Doc Id: 21
	};

	const std::vector<std::string> request = { "moscow is the capital of russia" };

	const std::vector<std::vector<RelativeIndex>> expected =
	{
		{
			{7, 1},           // Doc Id: 7  | R_abs: 1 + 1 + 1 + 1 + 1 + 1 = 6 | R_rels: 6 / 6 = 1
			{14, 1},          // Doc Id: 14 | R_abs: 1 + 2 + 1 + 1 + 1     = 6 | R_rels: 6 / 6 = 1
			{0, 0.666666687}, // Doc Id: 0  | R_abs: 1 + 1 + 1 + 1         = 4 | R_rels: 4 / 6 = 0.666666687
			{1, 0.666666687}, // Doc Id: 1  | R_abs: 1 + 1 + 1 + 1         = 4 | R_rels: 4 / 6 = 0.666666687
			{2, 0.666666687}  // Doc Id: 2  | R_abs: 1 + 1 + 1 + 1         = 4 | R_rels: 4 / 6 = 0.666666687
		}
	};
	
	TestSearchServerFunctionality(docs, request, expected, 5);
}
