#include "filelink_command.h"
#include "credentials.h"

#include <cmd/exceptions.h>
#include <lf/declarations.h>
#include <lf/engine.h>

namespace ui {

filelink_command::filelink_command(lf::engine& e)
    : cmd::command("filelink",
            credentials::usage() + 
            "[--report_level=<level>] [--expires=<YYYY-MM-DD>] <file>",
            "Uploads given file and creates filelink on it.",
            credentials::arg_descriptions() + 
            "\t--report_level\n"
            "\t    Level of reporting.\n"
            "\t    Valid values: silent, normal, verbose.\n"
            "\t    Default value: normal.\n\n"
            "\t--expires\n"
            "\t    Expire date for the filelink.\n\n"
            "\t<file>\n"
            "\t    File path to create filelink."
            )
    , m_engine(e)
{
}

void filelink_command::execute(const cmd::arguments& args)
{
    credentials c = credentials::manage(args);
    lf::report_level rl = lf::NORMAL;
    const std::string& rls = args["--report_level"];
    if (rls == "silent") {
        rl = lf::SILENT;
    } else if (rls == "verbose") {
        rl = lf::VERBOSE;
    } else if (rls != "" && rls != "normal") {
        throw cmd::invalid_argument_value("--report_level",
                "silent, normal, verbose");
    }
    const std::string& expire = args["--expires"];
    const std::set<std::string>& unnamed_args = args.get_unnamed_arguments();
    if (unnamed_args.size() != 1) {
        throw cmd::invalid_arguments("Need to specify only one file.");
    }
    m_engine.filelink(c.server(), c.api_key(), expire, *unnamed_args.begin(),
            rl, c.validate_flag());
}

}