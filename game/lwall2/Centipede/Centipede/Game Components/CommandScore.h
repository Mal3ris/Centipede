#pragma once

class CommandScore
{
public:
	CommandScore() = default;
	CommandScore(const CommandScore&) = delete;
	CommandScore& operator=(const CommandScore&) = delete;
	virtual ~CommandScore() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};
