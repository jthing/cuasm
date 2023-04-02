//
// Created by john on 02.04.23.
//

#include <string.h>
#include <ctype.h>
#include "utils.h"

/**
 * \brief whitespace back strip
 *
 * buf is scanned from the back and a '\0' inserted after the last non whitespace character.
 * @param buf - *buf modified
 */
void ws_bstrip (char *buf)
{
  size_t j = strlen (buf) - 1;
  while (!isspace(buf[j]))
	{
	  --j;
	}
  buf[j] = '\0';
}

/**
 * \brief whitespace front strip
 *
 * buf is scanned from the front past leading whitepspace
 * @param buf
 * @return - points to the first non-space character in buf
 */
char *ws_fstrip (char *buf)
{
  size_t i = 0;
  while (isspace(buf[i]))
	{
	  ++i;
	}
  return &buf[i];
}

/**
 * \brief strips leading and trailing whitespace
 *
 * \see \fn ws_fstrip,  \fn ws_bstrip
 * @param buf
 * @return - points to the frist nonspace character in buf
 */
char *ws_strip (char *buf)
{
  char *ln = ws_fstrip (buf);
  ws_bstrip (ln);
  return ln;
}
