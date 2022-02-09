/**
 * Menu.c
 *
 * This file manage the menu.
 *
 */

#include <sdk_tplus.h>
#include "Menu.h"

/**
 * Main menu
 *
 * - choice 0: to display a GOAL dialog box
 * - choice 1: to display a screen using GOAL resource file (.gml)
 * - choice 2: to exit
 *
 */
void menuGoalDisplay(void)
{
  char choice = 0;
  //Amount that accepts only 5 digit input
  char amount[100] = "00000";
  //currency
  char curr[4] = "KSH";

  const char *MenuUser[] =
  { "Sale", "Bill Payment", "Sale CashBack", 0 };

  initUIContext(_OFF_);

  do
  {
    //Display the menu using GOAL
    choice = GL_Dialog_Menu(mGoal, "POS PROJECT", MenuUser, choice,
            GL_BUTTON_NONE , GL_KEY_0, GL_TIME_INFINITE);

    switch (choice)
    {
    case 0:
    	choice = GL_Dialog_Amount(mGoal, NULL, "Enter amount :", "/d,/d/d/D./D/D", amount, sizeof(amount) -1 , curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);
    	break;
    case 1:
    	choice = GL_Dialog_Amount(mGoal, NULL, "Enter Bill :", "/d,/d/d/D./D/D", amount, sizeof(amount), NULL, GL_ALIGN_LEFT, GL_TIME_MINUTE);
    	break;
    default:
    	choice = GL_Dialog_Amount(mGoal, NULL, "Enter CashBack :", "/d,/d/d/D./D/D", amount, sizeof(amount), curr, GL_ALIGN_LEFT, GL_TIME_MINUTE);

    	break;


    }
  } while (choice != 2);

  releaseUIContext();

  return;
}



