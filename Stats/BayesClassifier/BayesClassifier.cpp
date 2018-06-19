#include "BayesClassifier.h"

using namespace mhe;

BayesClassifier::BayesClassifier()
	// FIXME: necessary ?
	// : m_dictionary({})
	// , m_responses({})
	// , m_wordList({})
	// , m_responseList({})
{
}

void BayesClassifier::train(const std::string &sample, const std::string &response)
{
	if (m_responses.find(response) == m_responses.end())
	{
		// Create new response field
		// m_responses.emplace()
	}
}