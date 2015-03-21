#pragma once

#include <cmd/command.h>

#include <map>

namespace cmd {
class command_processor;
}

namespace lf {

/**
 * @class help_command.
 * @brief Class for 'help' command.
 */
class help_command : public cmd::command
{
public:
    /// @brief Constructor.
    help_command(cmd::command_processor& p);

public:
    /// @brief Executes command by given arguments.
    virtual void execute(const cmd::arguments& args);

private:
    void print_help() const;

private:
    cmd::command_processor& m_command_processor;
};

}
