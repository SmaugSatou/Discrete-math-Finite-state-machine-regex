#pragma once

#include <vector>
#include <memory>


/**
* @file states.h
* @brief Contains the definitions for finite automaton state classes.
* These classes are part of a regex-like state machine engine.
*/


/**
* @class State
* @brief Base class for all finite automaton states.
*/
class State {
private:
	std::vector<std::shared_ptr<State>> nextStates;

public:
	State() = default;
	virtual ~State() = default;

	/// @brief Checks whether the current state accepts a given symbol.
	virtual bool checkSelf(const char symbol) const;

	/// @brief Returns all valid next states that accept the given symbol.
	virtual std::vector<std::shared_ptr<State>> checkNext(const char symbol) const;

	/// @brief Adds a transition to another state.
	void addNextState(std::shared_ptr<State> state);

	/// @brief Returns a vector of next states.
	std::vector<std::shared_ptr<State>> getNextStates() const;
};

/**
* @class StartState
* @brief Starting state of the automaton.
*/
class StartState : public State {};

/**
* @class TerminationState
* @brief Ending state of the automaton.
*/
class TerminationState : public State {};

/**
* @class StarState
* @brief Star state-util of the automaton.
*/
class StarState : public State {};

/**
* @class PlusState
* @brief Plus state-util of the automaton.
*/
class PlusState : public State {};

/**
* @class DotState
* @brief Matches any character.
*/
class DotState : public State {
public:
	bool checkSelf(const char symbol) const override;
};

/**
* @class AsciiState
* @brief Matches a specific character.
*/
class AsciiState : public State {
private:
	char symbol;

public:
	AsciiState(const char symbol);

	bool checkSelf(const char symbol) const override;
};