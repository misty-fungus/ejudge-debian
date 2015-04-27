/* $Id: make-js-actions.c 8238 2014-05-17 10:52:34Z cher $ */

#include <stdio.h>
#include "ejudge/new-server.h"

#define A(n) [n] = #n
const unsigned char * const action_table[NEW_SRV_ACTION_LAST] =
{
  A(NEW_SRV_ACTION_VIEW_PROBLEM_SUMMARY),
  A(NEW_SRV_ACTION_VIEW_PROBLEM_SUBMIT),
  A(NEW_SRV_ACTION_JSON_USER_STATE),
  A(NEW_SRV_ACTION_UPDATE_ANSWER),
};

int main(void)
{
  int i;

  for (i = 0; i < NEW_SRV_ACTION_LAST; i++)
    if (action_table[i])
      printf("var %s=%d;\n", action_table[i], i);

  return 0;
}