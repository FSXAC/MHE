// Inspired by D. Shiffman
// https://github.com/shiffman/bayes-classifier-js/blob/master/classifier.js

#pragma once

#include <functional>
#include <string>
#include <map>
#include <vector>

namespace mhe
{

class BayesClassifier
{
public:
	BayesClassifier();
	~BayesClassifier() = default;

	void train(const std::string &sample, const std::string &response);
	void predict(const std::string &input, std::string &output) const;

private:
	void checkResponse(const std::string &response);
	std::vector<std::string> splitString(const std::string &str, char delimiter = ' ');
	std::string toLower(const std::string &str);
	void increment(const std::string &token, const std::string &response);
	void compute();

private:
	struct ResponseData
	{
		unsigned int count;
		unsigned int tokenCount;
	};

	struct WordData
	{
		std::string word;
		std::string response;
		unsigned int count;
	};

private:
	std::map<std::string, WordData> m_dictionary;
	std::map<std::string, ResponseData> m_responses;

	std::vector<std::string> m_wordList;
	std::vector<std::string> m_responseList;

};
} // mhe
