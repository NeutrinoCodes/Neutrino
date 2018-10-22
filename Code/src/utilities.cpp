/// @file

#include "utilities.hpp"

void load_file(char* neutrino_path, const char* file_name, char** file_buffer, size_t* file_size)
{
	FILE* handle;
  char full_name[32768];

  snprintf(full_name, sizeof full_name, "%s%s", neutrino_path, file_name);

  handle = fopen(full_name, "rb");

  if(handle == NULL)
  {
    printf("\nError:  could not find the file!\n");
    exit(1);
  }

  fseek(handle, 0, SEEK_END);
  *file_size = (size_t)ftell(handle);
  rewind(handle);
  *file_buffer = (char*)malloc(*file_size + 1);

  if (!*file_buffer)
  {
    printf("\nError:  unable to allocate buffer memory!\n");
    exit(EXIT_FAILURE);
  }

  fread(*file_buffer, sizeof(char), *file_size, handle);
  fclose(handle);
  file_buffer[0][*file_size] = '\0';
}

void write_file(const char* file_name, char* file_buffer)
{
	FILE* handle;

	printf("Action: writing file \"%s\"...", file_name);

  handle = fopen(file_name, "a");

  if(handle == NULL)
  {
    printf("\nError:  could not write the file!\n");
    exit(1);
  }

  fputs(file_buffer, handle);
  fclose(handle);

	printf(" DONE!\n");
}

void free_file(char* buffer)
{
  free(buffer);                                                                                                               ///< Freeing buffer...
}

int query_numeric(char* caption, int min, int max)
{
  char  buffer[128];                                                            // Input buffer.
  int   numeric;                                                                // Numeric value.
  bool  valid_choice = false;                                                   // User's choice.

  printf("%s", caption);                                                        // Printing caption...

  while (!valid_choice)                                                         // Checking choice validity...
  {
    fgets(user_input, 128, stdin);                                              // Reading string from stdin...
    numeric = strtol(user_input, NULL, 10);                                     // Parsing stdin...

    if ((min <= numeric) && (numeric <= max) && (errno != ERANGE))
    {
      valid_choice = true;                                                    // Setting flag...
    }

    else
    {
      printf("\nError:  invalid input! Please, try again!\n");                  // Printing message...
      printf("\n");                                                             // Printing message...
      printf("%s", caption);                                                    // Printing question...

      errno = 0;
    }
  }

  return(numeric);                                                              // Returning numeric choice...
}
