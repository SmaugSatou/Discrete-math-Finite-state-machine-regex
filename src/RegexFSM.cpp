#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <memory>
#include <cctype>

#include "RegexFSM.h"

void RegexFSM::initializeRegex(const std::string& regex) {
    int regexSize = regex.size();

    this->startingState = std::make_shared<StartState>();

    std::vector<std::shared_ptr<State>> states = {startingState};

    for (int index = 0; index < regexSize; ++index) {
        states.push_back(this->parseNewState(regex[index]));
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
    case '*':
        return std::make_shared<StarState>();
    case '+':
        return std::make_shared<PlusState>();
    default:
        throw std::runtime_error("Invalid operation in regex!");
    }
}

void RegexFSM::connectStates(const std::vector<std::shared_ptr<State>>& states) {
    int statesNumber = states.size();

    int index = 1;

    while (index < statesNumber - 1) {
        std::shared_ptr<State> currState = states[index];
        std::shared_ptr<State> prevState = states[index - 1];
        std::shared_ptr<State> nextState = states[index + 1];


        if (std::dynamic_pointer_cast<StarState>(currState)) {
            if (index - 2 >= 0) {
                std::shared_ptr<State> prevPrevState = states[index - 2];
                prevPrevState->addNextState(nextState);
            }

            prevState->addNextState(prevState);
            prevState->addNextState(nextState);
        }
        else if (std::dynamic_pointer_cast<PlusState>(currState)) {
            prevState->addNextState(prevState);
            prevState->addNextState(nextState);
        }
        else {
            prevState->addNextState(currState);
        }

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
