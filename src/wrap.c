/* cuda assembler

Copyright (C) 2023 Pandora Norge

cuasm is free softwareyou can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

cuasm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with cuasm.  If not, see <https://www.gnu.org/licenses/>.  */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "wrap.h"

char *skip_ws(const char *str)
{
  while (isspace(*str)) str++;
  return (char *) str;
}

char *skip_word(const char *str)
{
  while (isalnum(*str)) str++;
  return (char *) str;
}

/**
 * \brief error-checked malloc
 *
 * Also zeroes out returned memory.
 * \see \fn malloc
 * @param nmemb
 * @return ptr to memory
 */
void *Malloc (size_t nmemb)
{
  assert(nmemb > 0);
  void *memref = malloc (nmemb);
  if (unlikely(memref == NULL))
    {
      perror ("calloc");
      exit (errno);
    }
  return memset (memref, 0, nmemb);
}

/**
 * \brief error-checked calloc
 *
 * Also zeroes out returned memory.
 * \see \fn calloc
 * @param nmemb
 * @param size
 * @return ptr to memory
 */
void *Calloc (size_t nmemb, size_t size)
{
  assert(nmemb > 0 && size > 0);
  void *memref = calloc (nmemb, size);
  if (unlikely(memref == NULL))
    {
      perror ("calloc");
      exit (errno);
    }
  return memset (memref, 0, sizeof *memref);
}

void *Realloc (void *ptr, size_t size)
{
  void *ret = realloc (ptr, size);
  if (unlikely(ret == NULL))
    {
      perror ("realloc");
      exit (errno);
    }
  return ret;
}

void *Memcpy (void *dest, const void *src, size_t n)
{
  void *ret = memcpy (dest, src, n);
  if (unlikely(ret == NULL))
    {
      perror ("memcpy");
      exit (errno);
    }
  return ret;
}

/**
 * \brief error-checked strdup
 * @param s
 * @return ptr to dup s
 */
char *Strdup (const char *s)
{
  char *ret = strdup (s);
  if (unlikely(ret == NULL))
    {
      perror ("strdup");
      exit (errno);
    }
  return ret;
}

int Streq (const char *str1, const char *str2)
{
  return strcmp (str1, str2) == 0;
}

/**
 * \brief error-checked fgets
 * \see \fn fgets
 * @param s
 * @param size
 * @param stream
 * @return ptr to string
 */
char *Fgets (char *s, int size, FILE *stream)
{
  char *ret = fgets (s, size, stream);
  if (unlikely(ret == NULL && ferror (stream)))
    {
      perror ("fgets");
      exit (errno);
    }
  return ret;
}

/**
 * \brief error-checked fputs
 *
 * \see \fn fputs
 * @param s
 * @param stream
 */
void Fputs (const char *s, FILE *stream)
{
  if (unlikely(fputs (s, stream) == EOF))
    {
      perror ("fputs");
      exit (errno);
    }
}

/**
 * \brief error-checked fprint
 *
 * \see \fn fprintf
 * @param stream
 * @param fmt
 * @param ...
 * @return characters read
 */
int Fprintf (FILE *stream, const char *fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);

  int ret = vfprintf (stream, fmt, ap);
  if (unlikely(ret < 0))
    {
      perror ("printf");
      exit (errno);
    }
  return ret;
}

/**
 * \brief error-checked \fn fread
 * \see fread
 * @param ptr
 * @param size
 * @param nmemb
 * @param stream
 * @return bytes read
 */
size_t Fread (void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t ret = fread (ptr, size, nmemb, stream);
  if (unlikely(feof (stream) || ret != nmemb))
    {
      if (ferror(stream) != 0)
        {
          perror ("fread");
          exit(errno);
        }
      else
        {
          fputs("fread: Unexpeceted EOF", stderr);
          exit(-1);
        }

    }
  return ret;
}

/**
 * \brief error-checked fwrite
 * \see fwrite
 * @param ptr
 * @param size
 * @param nmemb
 * @param stream
 * @return bytes written
 */
size_t Fwrite (const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
  size_t ret = fwrite (ptr, size, nmemb, stream);
  if (unlikely(feof(stream) || ret != nmemb))
    {
      if (ferror(stream) != 0)
        {
          perror ("fwrite");
          exit(errno);
        }
      else
        {
          fputs("fwrite: Unexpeceted EOF", stderr);
          exit(-1);
        }
    }
  return ret;
}

/**
 * \brief error-checked snprintf
 * \see \fn snprintf
 * @param str
 * @param size
 * @param fmt
 * @param ...
 * @return characters printed
 */
int Snprintf (char *str, size_t size, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int ret = vsnprintf (str, size, fmt, ap);
  if (unlikely(ret < 1))
    {
      perror ("snprintf");
      exit (errno);
    }
  return ret;
}

/**
 * \brief error-check fclose
 *
 * \see \fn fclose
 * @param file
 */
void Fclose (FILE *file)
{
  int ret = fclose (file);
  if (unlikely(ret == EOF))
    {
      perror ("fclose");
      exit (errno);
    }
}

/**
 * \brief error-checked popen
 *
 * \see \fn popen
 * @param command
 * @param type
 * @return pointer to stream
 */
FILE *Popen (const char *command, const char *type)
{
  FILE *stream = popen (command, type);
  if (unlikely(stream == NULL))
    {
      perror ("popen");
      exit (errno);
    }
  return stream;
}

/**
 * \brief error-checked pclose
 *
 * \see \fn pclose
 * @param stream
 */
void Pclose (FILE *stream)
{
  if (unlikely(pclose (stream) == -1))
    {
      perror ("pclose");
      exit (errno);
    }
}

void Warning (const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Fprintf (stderr, strcat ("Warning: ", fmt), ap);
}

void DEBUG (const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Fprintf (stderr, strcat ("DEBUG: ", fmt), ap);
}

void Error (const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  Fprintf (stderr, strcat ("Error: ", fmt), ap);
  exit (-1);
}