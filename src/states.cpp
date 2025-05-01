/**
 * @file states.cpp
 * @brief Implements the state classes defined in states.h
 * @ingroup AutomatonStates
 */

#include <stdexcept>
#include "states.h"

std::vector<std::shared_ptr<State>> State::checkNext(const char symbol) const {
	std::vector<std::shared_ptr<State>> validNextStates;

	for (const auto& nextState : this->nextStates) {
		if (nextState->checkSelf(symbol)) {
			validNextStates.push_back(nextState);
		}
	}

	return validNextStates;
}

bool State::checkSelf(const char symbol) const {
	return false;
}

void State::addNextState(std::shared_ptr<State> state) {
	this->nextStates.push_back(std::move(state));
}

std::vector<std::shared_ptr<State>> State::getNextStates() const {
	return this->nextStates;
}

// ---------- Derived State Implementations ---------- //

bool DotState::checkSelf(const char symbol) const {
	return true;
}

AsciiState::AsciiState(const char symbol) : symbol(symbol) {}

bool AsciiState::checkSelf(const char symbol) const {
	return this->symbol == symbol;
}
