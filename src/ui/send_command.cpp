#include "send_command.h"
#include "credentials.h"
#include "common_arguments.h"

#include <cmd/exceptions.h>
#include <lf/declarations.h>
#include <lf/engine.h>

namespace ui {

send_command::send_command(lf::engine& e)
    : cmd::command("send", "Sends the file(s) to specified user.")
    , m_engine(e)
    , m_to_argument("to", "<username>", "User name or email, to send file.")
    , m_message_argument("message", "<string>", "Message text of composed email.", "")
    , m_subject_argument("subject", "<string>", "Subject of composed email.", "")
    , m_files_argument("<file> ...", "File path(s) or attachments IDs to send to user.")
{
    get_arguments().push_back(credentials::get_arguments());
    get_arguments().push_back(s_report_level_arg);
    get_arguments().push_back(m_to_argument);
    get_arguments().push_back(m_subject_argument);
    get_arguments().push_back(m_message_argument);
    get_arguments().push_back(s_attachment_argument);
    get_arguments().push_back(m_files_argument);
}

void send_command::execute(const cmd::arguments& args)
{
    credentials c = credentials::manage(args);
    std::string user = m_to_argument.value(args);
    lf::report_level rl = s_report_level_arg.value(args);
    std::string subject = m_subject_argument.value(args);
    std::string message = m_message_argument.value(args);
    std::set<std::string> unnamed_args = m_files_argument.value(args);
    bool r = s_attachment_argument.value(args);
    if (r) {
        m_engine.send_attachments(c.server(), c.api_key(), user, subject, message, unnamed_args,
                rl, c.validate_flag());
    } else {
        m_engine.send(c.server(), c.api_key(), user, subject, message, unnamed_args,
                rl, c.validate_flag());
    }
}

}
