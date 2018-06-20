#include <sstream>
#include <locale>
#include "BayesClassifier.h"

using namespace mhe;

BayesClassifier::BayesClassifier()
	// FIXME: necessary ?
	: m_dictionary({})
	, m_responses({})
	, m_wordList({})
	, m_responseList({})
{
}

void BayesClassifier::train(const std::string &sample, const std::string &response)
{
	checkResponse(response);

	// Get list of sample broken down into tokens
	const std::vector<std::string> tokens = splitString(sample);

	for (auto token : tokens)
	{
		token = toLower(token);
		increment(token, response);
	}

}

void BayesClassifier::checkResponse(const std::string &response)
{
	if (m_responses.find(response) == m_responses.end())
	{
		// Create new response field
		ResponseData newRespData = {1, 0};
		m_responses.emplace(response, newRespData);
		m_responseList.emplace_back(response);
	}
	else
	{
		m_responses[response].count++;
	}
}

std::vector<std::string> BayesClassifier::splitString(const std::string &str, char delimiter = ' ')
{
	// TODO: delimiter

	std::vector<std::string> wordList;
	std::istringstream iss(str);
	while (iss)
	{
		std::string word;
		iss >> word;
		wordList.emplace_back(word);
	}

	return wordList;
}

std::string BayesClassifier::toLower(const std::string &str)
{
	std::string newStr;
	std::locale loc;
	for (std::string::size_type i = 0; i < str.length(); ++i)
		newStr.push_back(std::tolower(str[i], loc));
	return newStr;
}

void BayesClassifier::increment(const std::string &token, const std::string &response)
{
	m_responses[response].tokenCount++;
	
	if (m_dictionary.find(token) == m_dictionary.end())
	{
		WordData newWordData = {
			token,
			response,
			1
		};
		m_dictionary.emplace(token, newWordData);
		m_wordList.emplace_back(token);
	}
	else
	{
		WordData wd = m_dictionary[token];
		// TODO:
	}
	
	
}