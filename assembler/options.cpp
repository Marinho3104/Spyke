#include "options.h"

/* Parse a single option. */
error_t spyke::micky::assembler::options::parse_opt (int key, char *arg, argp_state *state)
{
	/* Get the input argument from argp_parse, which we
		 know is a pointer to our arguments structure. */
	arguments* arguments = reinterpret_cast< struct arguments* >( state->input );

	switch (key)
	{

    case 'f':
			
      arguments->file_path = arg;

      break;

		case ARGP_KEY_ARG:

			if (state->arg_num >= 2)

				/* Too many arguments. */
				argp_usage( state );
		 	
      break;
		
    case ARGP_KEY_END:

      // Checks if mandatory arguments were given
      if( ! arguments->file_path ) argp_usage( state );

			break;
		
    default:
		
      return ARGP_ERR_UNKNOWN;

	}
	return 0;
}


