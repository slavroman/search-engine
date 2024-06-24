#include "ConverterJSON.h"
#include "ProjectExceptions.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

// For convenience
using json = nlohmann::json;
using orderedJson = nlohmann::ordered_json;

ConverterJSON::ConverterJSON()
    : responsesLimit(0)
{
}

ConverterJSON::~ConverterJSON()
{
}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::vector<std::string> filePaths;

    std::ifstream configurationJsonFile(".\\json\\config.json");    
    
    try
    {
        if (configurationJsonFile.is_open())
        {
            auto inputJsonData = json::parse(configurationJsonFile);

            if (inputJsonData.contains("config"))
            {
                std::cout << "\n\tStarting " << inputJsonData["config"]["name"] << ' ';
                std::cout << "(ver. " << inputJsonData["config"]["version"] << ")\n";

                responsesLimit = inputJsonData["config"]["max_responses"];

                filePaths = inputJsonData["files"];
            }
            else
            {
                throw ConfigFileEmptyException();
            }

            configurationJsonFile.close();
        }
        else
        {
            throw ConfigFileMissingException();      
        }
    }
    catch (const ConfigFileMissingException& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (const json::parse_error& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (const ConfigFileEmptyException& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return filePaths;
}

size_t ConverterJSON::GetResponsesLimit()
{
    return responsesLimit;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> requests;

    std::ifstream requestsJsonFile(".\\json\\requests.json");

    try
    {
        if (requestsJsonFile.is_open())
        {
            auto inputJsonData = json::parse(requestsJsonFile);

            for (const auto& it : inputJsonData["requests"])
            {
                requests.push_back(it);
            }

            requestsJsonFile.close();
        }
        else
        {
            throw RequestsFileMissingException();
        }

    }
    catch (const json::parse_error& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (const RequestsFileMissingException& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers)
{
    try
    {
        if (!answers.empty())
        {
            std::ofstream answersJsonFile(".\\json\\answers.json", std::ios_base::trunc);

            if (answersJsonFile.is_open())
            {
                orderedJson answerJsonData;

                auto requestId{ 1 };

                for (const auto& request : answers)
                {
                    // TODO: Need make construction below more elegant

                    std::string requestNumber{ "000" };

                    if (requestId >= 1 && requestId < 10)
                    {
                        requestNumber.replace(2, 1, std::to_string(requestId));
                    }

                    if (requestId >= 10 && requestId < 100)
                    {
                        requestNumber.replace(1, 2, std::to_string(requestId));
                    }

                    if (requestId >= 100)
                    {
                        requestNumber = std::to_string(requestId);
                    }

                    answerJsonData["answers"]["request" + requestNumber]["result"] = !request.empty();

                    for (const auto& [docid, rank] : request)
                    {
                        auto doubleRank = static_cast<double>(rank);
                        doubleRank = std::round(doubleRank * 1000.0) / 1000.0;

                        if (request.size() == 1)
                        {
                            answerJsonData["answers"]["request" + requestNumber]["docid"] = docid;
                            answerJsonData["answers"]["request" + requestNumber]["rank"] = doubleRank;

                        }
                        else
                        {
                            orderedJson item = { {"docid", docid}, {"rank", doubleRank} };
                            answerJsonData["answers"]["request" + requestNumber]["relevance"] += item;
                        }
                    }

                    ++requestId;
                }

                answersJsonFile << std::setw(4) << answerJsonData << std::endl;

                answersJsonFile.close();
            }
            else
            {
                std::cerr << "\tCan't open answers file!\n";
            }
        }
        else
        {
            throw AnswersEmptyException();
        }
    }
    catch (const AnswersEmptyException& ex)
    {
        std::cerr << ex.what() << std::endl;
    }    
}
