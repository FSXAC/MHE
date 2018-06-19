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
	void increment(const std::string &token, const std::string &response);
	void compute();

private:
	struct responseData
	{
		unsigned int count = 1;
		unsigned int tokenCount = 0;
	};

	struct wordData
	{
		unsigned int wordCount = 0;
	};

private:
	std::map<std::string, std::string> m_dictionary;
	std::map<std::string, std::string> m_responses;

	std::vector<std::string> m_wordList;
	std::vector<std::string> m_responseList;

};
} // mhe
