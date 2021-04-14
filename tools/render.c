// copy index.html into formatted file index.h
// not very cohesive but it gets the job done
#include <stdio.h>
#include <string.h>

int main() {

  const char *preamble =
      "#pragma once\n#include \"pgmspace.h\"\nconst char ndx[] = R\"=====(\n";
  const char *postamble = "\n)=====\";";

  FILE *infile = fopen("..\\src\\index.html", "r");
  FILE *outfile = fopen("..\\src\\index.hpp", "w");

  fprintf(outfile, preamble);
  long lines = 1;
  char c;
  while ((c = (char)fgetc(infile)) != EOF) {
    fprintf(outfile, "%c", c);
    lines += (c == '\n');
  }

  fprintf(outfile, postamble);
  fclose(outfile);
  fclose(infile);
  printf("\nDone copying %ld lines.", lines);

  return 0;
}
