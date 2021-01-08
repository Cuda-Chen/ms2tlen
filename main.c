#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time_length.h"

static void
usage ()
{
  printf ("Usage: ./ms2tlen [mseedfile]\n\n");
  printf ("## Options ##\n"
          " mseedfile         input miniSEED file\n");
  printf ("\nOutput format: \n");
  printf ("<time length> <npts> <sps>");
}

int
main (int argc, char **argv)
{
  char *mseedfile = NULL;

  /* Simplistic argument parsing */
  if (argc != 2)
  {
    usage ();
    return -1;
  }

  /* Get file name without path */
  mseedfile  = argv[1];
  int len    = strlen (mseedfile);
  char *temp = (char *)malloc (sizeof (char) * (len + 1));
  strncpy (temp, mseedfile, len);
  temp[len] = '\0';
  int l     = 0;
  char *ssc = strstr (temp, "/");
  while (ssc)
  {
    l    = strlen (ssc) + 1;
    temp = &temp[strlen (temp) - l + 2];
    ssc  = strstr (temp, "/");
  }
#ifdef DEBUG
  size_t tempLen = strlen (temp);
  printf ("temp str size: %ld content: %s\n", tempLen, temp);
#endif

  /* Get time length, number of points, sample rate of this trace */
  int64_t npts = 0;
  double sps;
  int rv = getTimeLength (mseedfile, &npts, &sps);
  if (rv != 0)
  {
    puts ("Something went wrong.");
    return -1;
  }

  printf ("%g %" PRId64 " %g\n", (double)npts / sps, npts, sps);

  return 0;
}
