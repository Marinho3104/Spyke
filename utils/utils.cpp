
/** INCLUDES **/
#include "utils.h"
#include <stdio.h>
#include <iostream>

char* utils::get_file_content( const char* pathname ) {

  FILE* file = fopen( pathname, "r" );

  // Check for errors
  if ( ! file ) return 0;

  // Go to the end of file
  fseek( file, 0, SEEK_END );

  // Get the file size content
  long int file_content_size = ftell( file );

  // Allocate the memory needed for the file content +1 for the null terminated
  char* content = ( char* ) calloc( sizeof( char ), file_content_size + 1 );

  // Reset file cursor to the beginning
  fseek( file, 0, SEEK_SET );

  // Tries to read the file content
  if (
    fread(

      content,
      file_content_size,
      1,
      file

    ) != 1
  ) { free( content ); content = 0; }

  fclose( file );

  return content;

}
