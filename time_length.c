#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>

#include "libmseed.h"

#include "time_length.h"

int
getTimeLength (const char *mseedfile, int64_t *npts, double *sps)
{
  MS3TraceList *mstl = NULL;
  MS3TraceID *tid    = NULL;
  MS3TraceSeg *seg   = NULL;

  int rv;
  uint32_t flags = 0;
  int8_t verbose = 0;

  /* Set bit flag to validate CRC */
  flags |= MSF_VALIDATECRC;

  /* Set bit flag to build a record list */
  flags |= MSF_RECORDLIST;

  /* Read all miniSEED into a trace list, limiting to selections */
  rv = ms3_readtracelist (&mstl, mseedfile, NULL, 0, flags, verbose);
  if (rv != MS_NOERROR)
  {
    ms_log (2, "Cannot read miniSEED from file: %s\n", ms_errorstr (rv));
    return -1;
  }

  /* Traverse trace list structures and print summary information */
  tid = mstl->traces;
  while (tid)
  {
    ms_log (0, "TraceID for %s (%d), segments: %u\n",
            tid->sid, tid->pubversion, tid->numsegments);

    seg = tid->first;
    while (seg)
    {
      *npts += seg->samplecnt;
      *sps = seg->samprate;

      seg = seg->next;
    }
    tid = tid->next;
  }

  if (mstl)
  {
    mstl3_free (&mstl, 0);
  }

  return 0;
}
