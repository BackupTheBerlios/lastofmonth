/*
 ********************************************************************************
 *
 * $Id: lastofmonth.c,v 1.1 2003/11/04 16:58:53 sauerlaender Exp $
 *
 ********************************************************************************
 *
 * Copyright (C) 2003 drueeke.net
 * Written by Christian Drueeke (linux@drueeke.net)
 *
 ********************************************************************************
 *
 * This is my first program written in C... (-:
 * Please send any hints to my e-mail address!
 *
 * Dies ist mein erstes C-Programm... (-:
 * Anregungen, Verbesserungsvorschlaege, Kritik bitte per Mail!
 *
 ********************************************************************************
 *
 * ToDo:
 *
 * man-page
 *
 ********************************************************************************
 *
 * $Log: lastofmonth.c,v $
 * Revision 1.1  2003/11/04 16:58:53  sauerlaender
 * Initial revision
 *
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <time.h>
#include <getopt.h>

#define RC_OK 0
#define RC_USAGE 100
#define RC_ILLEGAL_OPTION 101
#define RC_ILLEGAL_MONTH 102
#define RC_ILLEGAL_YEAR 103

int main(int argc, char *argv[])
{
 int option;
 int lastday = 31;            /* standard days per month */
 time_t now;                  /* time_t = long */
 struct tm *nowpointer;
 char month[4], year[8];
 int imonth = -1, iyear = -1, longoutput = 0, quit = 0;
 char *bname;
 bname = basename(argv[0]);

 while ((option = getopt (argc, argv, "qhlm:y:")) != EOF)
 {
  switch (option)
  {
   case 'h':
   {
    fprintf(stderr,"%s is a tool to resolve the last day of a month.",bname);
    fprintf(stderr,"\n\nUsage: %s [OPTION]...",bname);
    fprintf(stderr,"\n\nExamples:");
    fprintf(stderr,"\n  %s                # the last day of the current month/year",bname);
    fprintf(stderr,"\n  %s -q             # Quit, no output. Just the return code",bname);
    fprintf(stderr,"\n  %s -h             # show the usage",bname);
    fprintf(stderr,"\n  %s -m 2 -y 1880   # the last day of february in the year 1880",bname);
    fprintf(stderr,"\n  %s -l -m 10       # the last day of october in the current year (long format)",bname);
    fprintf(stderr,"\n\nOptions:");
    fprintf(stderr,"\n  -h (help)    show the usage and exit");
    fprintf(stderr,"\n  -l (long)    print the result in the long format (year-month-day)");
    fprintf(stderr,"\n  -m (month)   the requested month");
    fprintf(stderr,"\n  -y (year)    and the requested year");
    fprintf(stderr,"\n\nReturn codes:");
    fprintf(stderr,"\n  28-31   the last day of the requested month");
    fprintf(stderr,"\n  %d     usage shown",RC_USAGE);
    fprintf(stderr,"\n  %d     illegal option",RC_ILLEGAL_OPTION);
    fprintf(stderr,"\n  %d     illegal month",RC_ILLEGAL_MONTH);
    fprintf(stderr,"\n  %d     illegal year",RC_ILLEGAL_YEAR);
    fprintf(stderr,"\n\nCopyright:");
    fprintf(stderr,"\n  %s",bname);
    fprintf(stderr,"\n  Copyright (C) 2003 by drueeke.net");
    fprintf(stderr,"\n  This program comes with NO WARRANTY, to the extent permitted by law.");
    fprintf(stderr,"\n  You may redistribute it under the terms of the GNU General Public License;");
    fprintf(stderr,"\n  see the file named COPYING for details.");
    fprintf(stderr,"\n  Written by Christian Drueeke (linux@drueeke.net).\n\n");
    return RC_USAGE;
    break;
   }
   case 'm':
   {
    imonth = atoi(optarg);
    break;
   }
   case 'y':
   {
    iyear = atoi(optarg);
    break;
   }
   case 'l':
   {
    longoutput = 1;
    break;
   }
   case 'q':
   {
    quit = 1;
    break;
   }
   default:
   {
    fprintf(stderr,"\nTry %s -h\n",bname);
    return RC_ILLEGAL_OPTION;
   }
  }
 }
 time(&now);
 nowpointer = localtime(&now);
 strftime(month, 4, "%m", nowpointer);
 strftime(year, 8, "%Y", nowpointer);

 imonth = (imonth == -1) ? atoi(month) : imonth;
 iyear = (iyear == -1) ? atoi(year) : iyear;

 if ((imonth < 1) || (imonth > 12))
 {
  fprintf(stderr,"ERROR! Illegal month!\n");
  return RC_ILLEGAL_MONTH;
 }
 
 if ((iyear < 1) || (iyear > 9999))
 {
  fprintf(stderr,"ERROR! Illegal year!\n");
  return RC_ILLEGAL_YEAR;
 }
 
 switch (imonth)
 {
  case 2:
  { /* Februar - 28 Tage (normalerweise!) */
   lastday = 28;
   switch (iyear % 4)
   {
    case 0:
    { /* Schaltjahr (Jahreszahl durch 4 teilbar)... */
     lastday = 29;
     break;
    }
   }
   switch (iyear % 100)
   {
    case 0:
    { /* KEIN Schaltjahr (Jahreszahl durch 100 teilbar)... */
     lastday = 28;
     break;
    }
   }
   switch (iyear % 400)
   {
    case 0:
    { /* DOCH ein Schaltjahr (Jahreszahl durch 400 teilbar)... */
     lastday = 29;
     break;
    }
   }
   break;
  }
  case 4:
  { /* April - 30 Tage */
   lastday = 30;
   break;
  }
  case 6:
  { /* Juni - 30 Tage */
   lastday = 30;
   break;
  }
  case 9:
  { /* September - 30 Tage */
   lastday = 30;
   break;
  }
  case 11:
  { /* November - 30 Tage */
   lastday = 30;
   break;
  }
 }

 if (quit == 0)
 {
  if (longoutput == 1)
  {
   printf("%d-%d-%d\n", iyear, imonth, lastday);
  }
  else
  {
   printf("%d\n", lastday);
  }
 }
 return lastday;
}
