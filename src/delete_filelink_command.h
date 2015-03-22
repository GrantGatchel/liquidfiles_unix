#pragma once

#include <cmd/command.h>

namespace lf {

class engine;

/**
 * @class delete_filelink_command.
 * @brief Class for 'delete_filelink' command.
 */
class delete_filelink_command : public cmd::command
{
public:
    /// @brief Constructor.
    /// @param e Engine.
    delete_filelink_command(engine& e);

public:
    /// @brief Executes command by given arguments.
    virtual void execute(const cmd::arguments& args);

private:
    engine& m_engine;
};

}