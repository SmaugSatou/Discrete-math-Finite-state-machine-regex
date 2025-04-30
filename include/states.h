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
class State : public std::enable_shared_from_this<State> {
private:
	std::vector<std::shared_ptr<State>> nextStates;

public:
	State() = default;
	virtual ~State() = default;

	/// @brief Checks whether the current state accepts a given symbol.
	virtual bool checkSelf(const char symbol) const = 0;

	/// @brief Returns all valid next states that accept the given symbol.
	virtual std::vector<std::shared_ptr<State>> checkNext(const char symbol) const;

	/// @brief Adds a transition to another state.
	void addNextState(std::shared_ptr<State> state);
};

/**
* @class StartState
* @brief Starting state of the automaton.
*/
class StartState : public State {
public:
	virtual ~StartState() = default;
	bool checkSelf(const char symbol) const override;
};

/**
* @class TerminationState
* @brief Ending state of the automaton.
*/
class TerminationState : public State {
public:
	virtual ~TerminationState() = default;
	bool checkSelf(const char symbol) const override;
};

/**
* @class DotState
* @brief Matches any character.
*/
class DotState : public State {
public:
	virtual ~DotState() = default;
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
	virtual ~AsciiState() = default;
	bool checkSelf(const char symbol) const override;
};

/**
* @class StarState
* @brief Matches 0 or more occurrences of the checking states.
*/
class StarState : public State {
private:
	std::vector<std::shared_ptr<State>> checkingStates;

public:
	StarState(const std::vector<std::shared_ptr<State>>& checkingStates);
	virtual ~StarState() = default;
};

/**
* @class PlusState
* @brief Matches 1 or more occurrences of the checking states.
*/
class PlusState : public State {
private:
	std::vector<std::shared_ptr<State>> checkingStates;

public:
	PlusState(const std::vector<std::shared_ptr<State>>& checkingStates);
	virtual ~PlusState() = default;
};
