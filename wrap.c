//
// Created by john on 31.03.23.
//

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include "wrap.h"

char *Fgets (char *s, int size, FILE *stream)
{
  char *ret = fgets (s, size, stream);
  if (ret == NULL && ferror (stream))
	{
	  perror ("fgets: ");
	  exit (errno);
	}
  return ret;
}
void Fputs (const char *s, FILE *stream)
{
  if (fputs (s, stream) == EOF)
	{
	  perror ("fputs: ");
	  exit (errno);
	}
}

int Printf (char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);

  int ret = vprintf (fmt, ap);
  if (ret < 0)
	{
	  perror ("printf: ");
	  exit (errno);
	}
  return ret;
}

int Fprintf (FILE *stream, char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);

  int ret = vfprintf (stream, fmt, ap);
  if (ret < 0)
	{
	  perror ("printf: ");
	  exit (errno);
	}
  return ret;
}

void Fclose (FILE *file)
{
  int ret = fclose (file);
  if (ret == EOF)
	{
	  perror ("fclose: ");
	  exit (errno);
	}
}

FILE *Popen (const char *command, const char *type)
{
  FILE *stream = popen(command, type);
  if (stream == NULL)
	{
	  perror ("popen: ");
	  exit(errno);
	}
  return stream;
}

void Pclose (FILE *stream)
{
  if (pclose (stream) == -1)
	{
	  perror ("pclose: ");
	  exit(errno);
	}
}
