#include "common_arguments.h"

namespace ui {

cmd::argument_definition<lf::report_level, cmd::NAMED_ARGUMENT, false> s_report_level_arg
    ("report_level", "<level>", "Level of reporting.", lf::NORMAL);

cmd::argument_definition<lf::output_format, cmd::NAMED_ARGUMENT, false> s_output_format_arg
    ("output_format", "<format>", "Specifies output string format.", lf::TABLE_FORMAT);

cmd::argument_definition<bool, cmd::BOOLEAN_ARGUMENT, false>  s_attachment_argument
    ("r", "If specified, it means that unnamed arguments are attachment IDs,"
     " otherwise they are file paths.");
}
