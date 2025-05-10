/**
 * @file RegexFSM.cpp
 * @brief Implements the Regex Finite State Machine
 * @ingroup RegexImplementation
 */

#include <stdexcept>
#include <unordered_set>

#include "RegexFSM.h"

void RegexFSM::initializeRegex(const std::string& regex) {
    size_t regexSize = regex.size();

    this->startingState = std::make_shared<StartState>();

    std::vector<std::shared_ptr<State>> states = { startingState };

    for (size_t index = 0; index < regexSize; ++index) {
        char current = regex[index];

        if (current == '*') {
            if (states.size() < 2) throw std::runtime_error("Nothing to repeat with '*'");
            states[states.size() - 1]->markStar();
            continue;
        }
        else if (current == '+') {
            if (states.size() < 2) throw std::runtime_error("Nothing to repeat with '+'");
            states[states.size() - 1]->markPlus();
            continue;
        }

        if (current == '[') {
            states.push_back(this->parseClassState(regex, index));
        }
        else {
            states.push_back(this->parseNewState(current));
        }
    }


    std::shared_ptr<TerminationState> endingState = std::make_shared<TerminationState>();
    states.back()->addNextState(endingState);

    states.push_back(endingState);

    this->connectStates(states);
}

std::shared_ptr<State> RegexFSM::parseNewState(const char& operation) {
    if (std::isalnum(static_cast<int>(operation))) {
        return std::make_shared<AsciiState>(operation);
    }

    switch (operation) {
    case '.':
        return std::make_shared<DotState>();
    case '[':
        throw std::runtime_error("Unexpected '[' in parseNewState");
    default:
        throw std::runtime_error("Invalid operation in regex!");
    }
}

std::shared_ptr<State> RegexFSM::parseClassState(const std::string& regex, size_t& index) {
    std::vector<std::shared_ptr<State>> classStates;
    bool isNegated = false;

    ++index;

    if (regex[index] == '^') {
        isNegated = true;
        ++index;
    }

    while (index < regex.size() && regex[index] != ']') {
        if (index + 2 < regex.size() && regex[index + 1] == '-') {
            char start = regex[index];
            char end = regex[index + 2];
            std::vector<std::pair<int, int>> ranges = { {start, end} };
            classStates.push_back(std::make_shared<AsciiRangeState>(ranges, false));
            index += 3;
        }
        else {
            classStates.push_back(std::make_shared<AsciiState>(regex[index]));
            ++index;
        }
    }

    if (index >= regex.size() || regex[index] != ']') {
        throw std::runtime_error("Unterminated character class in regex");
    }

    return std::make_shared<ClassState>(classStates, isNegated);
}

void RegexFSM::connectStates(const std::vector<std::shared_ptr<State>>& states) {
    size_t statesNumber = states.size();

    size_t index = 1;

    while (index < statesNumber - 1) {
        std::shared_ptr<State> currState = states[index];
        std::shared_ptr<State> prevState = states[index - 1];
        std::shared_ptr<State> nextState = states[index + 1];


        if (currState->getStar()) {
            currState->addNextState(currState);
            prevState->addNextState(nextState);
        }
        else if (currState->getPlus()) {
            currState->addNextState(currState);
        }

        prevState->addNextState(currState);

        index++;
    }

}

RegexFSM::RegexFSM(const std::string regexExpression) {
    this->initializeRegex(regexExpression);
}

bool RegexFSM::checkString(const std::string& input) const {
	std::vector<std::shared_ptr<State>> currentStates = { this->startingState };

	for (const char& symbol : input) {
		std::vector<std::shared_ptr<State>> nextStates;

		for (const auto& state : currentStates) {
			std::vector<std::shared_ptr<State>> validNext = state->checkNext(symbol);
			nextStates.insert(nextStates.end(), validNext.begin(), validNext.end());
		}

		if (nextStates.empty()) {
			return false;
		}

		currentStates = nextStates;
	}

    for (const auto& state : currentStates) {
        for (const auto& nextState : state->getNextStates()) {
            if (std::dynamic_pointer_cast<TerminationState>(nextState)) {
                return true;
            }
        }
    }

	return false;
}
