#include <argp.h>

namespace spyke::micky::assembler::options {

  // Documentation
  static char doc[] = "Assembler from Assembly to Micky Bd";

  /* A description of the arguments we accept. */
  static char args_doc[] = "TABLE FILE";

  /* The options we understand. */
  static argp_option options[] = {
    {"filepath", 'f', "FILEPATH", 0,  "File path to the assembly file that will be used" },
    { 0 }
  };

  /* Used by main to communicate with parse_opt. */
  struct arguments {

    char* file_path = 0;

  };

  error_t parse_opt (int key, char *arg, struct argp_state *state);

}
