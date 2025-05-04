#pragma once

#include <string>
#include <memory>

#include "states.h"


/**
* @file RegexFSM.h
* @brief Declares the RegexFSM class for constructing and evaluating finite state machines
*        based on a simplified regular expression syntax.
*/


/**
* @class RegexFSM
* @brief A finite state machine (FSM) that simulates simplified regular expressions.
*
* This class constructs a state graph from a regex pattern (supporting characters, '.', '*', and '+'),
* and provides a method to test whether input strings match the pattern.
*/
class RegexFSM {
private:
	std::shared_ptr<StartState> startingState = nullptr;

	/**
	* @brief Builds the FSM based on the provided regex pattern.
	*
	* @param regexExpression The regular expression to parse.
	*/
	void initializeRegex(const std::string& regex);

	/**
	* @brief Creates and returns a new State based on the specified operation.
	*
	* @param operation A character representing the operation to parse and create a new State.
	*
	* @return A shared pointer to the newly created State.
	*/
	std::shared_ptr<State> parseNewState(const char& operation);

	/**
	* @brief Parses a character class from the regex and constructs a ClassState.
	*
	* @param regex The full regex pattern.
	* @param index A reference to the current index in the regex string; this will be updated as characters are consumed.
	* @return A shared pointer to the constructed ClassState.
	*
	* @throws std::runtime_error if the class is improperly formatted or not closed.
	*/
	std::shared_ptr<State> RegexFSM::parseClassState(const std::string& regex, size_t& index);

	/**
	* @brief Connects a sequence of states.
	*
	* This function accepts a list of states and connects them in the specified order.
	* The exact connection mechanism depends on the implementation of the State class.
	* This operation may modify the states or their relationships as required by the system.
	*
	* @param states A vector of shared pointers to the states that need to be connected.
	*/
	void connectStates(const std::vector<std::shared_ptr<State>>& states);

public:

	/**
	* @brief Constructs the RegexFSM with a given regex pattern.
	*
	* @param regexExpression The regular expression used to build the FSM.
	*/
	RegexFSM(const std::string regexExpression);

	/**
	* @brief Checks whether a given string is accepted by the FSM.
	*
	* @param input The input string to evaluate.
	* @return true if the input matches the regex pattern; otherwise, false.
	*/
	bool checkString(const std::string& input) const;
};