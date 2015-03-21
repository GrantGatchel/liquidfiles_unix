#pragma once

#include <cmd/command.h>

namespace lf {

class engine;

/**
 * @class download_command.
 * @brief Class for 'download' command.
 */
class download_command : public cmd::command
{
public:
    /// @brief Constructor.
    /// @param e Engine.
    download_command(engine& e);

public:
    /// @brief Executes command by given arguments.
    virtual void execute(const cmd::arguments& args);

private:
    engine& m_engine;
};

}
