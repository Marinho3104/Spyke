
#include "./../../assembler/options.h"
#include <iostream>

// Handles given options
void handle_options( spyke::micky::assembler::options::arguments&, int, char* [] );

int main (int argc, char *argv[]) {

  // Handles options given by user
  spyke::micky::assembler::options::arguments arguments; handle_options( arguments, argc, argv );

  

  std::cout << arguments.file_path << std::endl;

  return 0;

}

void handle_options( spyke::micky::assembler::options::arguments& arguments, int argc, char* argv[] ) {

  // Makes it refer to spyke::micky::assembler::options namespace
  using namespace spyke::micky::assembler::options;

  argp argp = { options, parse_opt, args_doc, doc }; argp_parse( &argp, argc, argv, 0, 0, &arguments );  

}
