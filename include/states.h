#pragma once

#include <vector>
#include <memory>
#include <unordered_set>

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
	bool isStar = false;
	bool isPlus = false;

public:
    State() = default;
    virtual ~State() = default;

    /// @brief Checks whether the current state accepts a given symbol.
    /// @param symbol The character to check.
    /// @return True if the symbol is accepted by the state.
    virtual bool checkSelf(const char& symbol) const;

    /// @brief Returns all valid next states that accept the given symbol.
    /// @param symbol The character to check transitions with.
    /// @return A vector of states that can be transitioned to with the given symbol.
    virtual std::vector<std::shared_ptr<State>> checkNext(const char symbol) const;

    /// @brief Adds a transition to another state.
    /// @param state The state to transition to.
    void addNextState(std::shared_ptr<State> state);

    /// @brief Returns a vector of next states.
    /// @return A vector containing all next states.
    std::vector<std::shared_ptr<State>> getNextStates() const;

    /// @brief Marks this state as having the Kleene star ('*') behavior.
    /// This allows the state to repeat zero or more times.
    void markStar();

    /// @brief Marks this state as having the plus ('+') behavior.
    /// This allows the state to repeat one or more times.
    void markPlus();

    /// @brief Checks if this state is marked with the Kleene star ('*').
    /// @return True if the state repeats zero or more times.
    bool getStar() const;

    /// @brief Checks if this state is marked with the plus ('+') operator.
    /// @return True if the state repeats one or more times.
    bool getPlus() const;
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
* @class DotState
* @brief Matches any character.
*/
class DotState : public State {
public:
	bool checkSelf(const char& symbol) const override;
};

/**
* @class AsciiState
* @brief Matches a specific character.
*/
class AsciiState : public State {
private:
	char symbol;

public:
	AsciiState(const char& symbol);

	bool checkSelf(const char& symbol) const override;
};

class AsciiRangeState : public State {
private:
	bool isNegated;
	std::vector<std::pair<int, int>> charRanges;

public:
	AsciiRangeState(const std::vector<std::pair<int, int>>& charRanges, const bool& isNegated);

	bool checkSelf(const char& symbol) const override;
};

/**
* @class ClassState
* @brief Composite state that matches if any of its sub-states match.
*
* A ClassState is used to implement regex character classes such as `[abc]`, `[a-z]`, or `[^0-9]`.
* It contains a list of sub-states (such as AsciiState or AsciiRangeState) and optionally negates the result.
*
* If `isNegated` is false, the ClassState matches if **any** sub-state matches.
* If `isNegated` is true (e.g., for `[^abc]`), it matches if **none** of the sub-states match.
*/
class ClassState : public State {
private:
	std::vector<std::shared_ptr<State>> checkingStates;
	bool isNegated;

public:
	ClassState(const std::vector<std::shared_ptr<State>>& checkingStates, bool isNegated = false);

	bool checkSelf(const char& symbol) const override;
};