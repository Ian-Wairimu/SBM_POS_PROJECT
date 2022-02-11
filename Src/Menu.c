/**
 * Menu.c
 *
 * This file manage the menu.
 *
 */

#include <sdk_tplus.h>
#include "Menu.h"
#include <stdlib.h>


/**
 * Main menu
 *
 * - choice 0: to display a GOAL dialog box
 * - choice 1: to display a screen using GOAL resource file (.gml)
 * - choice 2: to exit
 *
 */
int menuGoalDisplay(void)
{
  char choice = 0;

  const char *MenuUser[] =
  { "Sale", "Bill Payment", "Sale CashBack", 0 };

  initUIContext(_OFF_);

  do
  {
    //Display the menu using GOAL
    choice = GL_Dialog_Menu(mGoal, "POS PROJECT", MenuUser, choice,
            GL_BUTTON_NONE , GL_KEY_1, GL_TIME_INFINITE);

    switch (choice)
    {
    case 0:
    	saleMenuDisplay();
    	break;
    case 1:
    	billMenuDisplay();
    	break;
    default:
    	cashBackMenuDisplay();
    	break;


    }
  } while (choice != 3);

  releaseUIContext();

  return EXIT_SUCCESS;
}



