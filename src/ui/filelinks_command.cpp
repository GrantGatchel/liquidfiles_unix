#include "filelinks_command.h"
#include "credentials.h"

#include <cmd/exceptions.h>
#include <lf/declarations.h>
#include <lf/engine.h>

namespace ui {

filelinks_command::filelinks_command(lf::engine& e)
    : cmd::command("filelinks",
            credentials::usage() + 
            "[--report_level=<level>] [--expires=<YYYY-MM-DD>] <file>",
            "Lists the available filelinks.",
            credentials::arg_descriptions() + 
            "\t--report_level\n"
            "\t    Level of reporting.\n"
            "\t    Valid values: silent, normal, verbose.\n"
            "\t    Default value: normal.\n\n"
            "\t--output_format\n"
            "\t    Specifies output string format.\n"
            "\t    Valid values: table, csv.\n"
            "\t    Default value: table.\n\n"
            "\t--limit\n"
            "\t    Limit of filelinks list."
            )
    , m_engine(e)
{
}

void filelinks_command::execute(const cmd::arguments& args)
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
    lf::output_format of = lf::TABLE_FORMAT;
    const std::string& ofs = args["--output_format"];
    if (ofs == "csv") {
        of = lf::CSV_FORMAT;
    } else if (ofs != "" && ofs != "table") {
        throw cmd::invalid_argument_value("--output_format",
                "table, csv");
    }
    const std::string& limit = args["--limit"];
    m_engine.filelinks(c.server(), c.api_key(), limit, of, rl, c.validate_flag());
}

}