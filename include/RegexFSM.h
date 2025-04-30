#pragma once

#include <string>
#include <memory>

#include "include/states.h"


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
	void initializeRegex(const std::string&);

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
	bool checkString(const std::string) const;
};