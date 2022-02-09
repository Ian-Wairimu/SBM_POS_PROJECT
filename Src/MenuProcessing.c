/*
 *this is an evaluation project Menu
 *where our main purpose are:
 *to create three Menu:
 *1)Sale Menu
 *2)Bill Management Menu
 *3)Sale CashBack
 **/
#include <sdk_tplus.h>

#include "DateScreen.h"
#include "Menu.h"

 //variables
//define a file descriptor handle
static Telium_File_t *sMoonKeyboard = NULL;
static Telium_File_t *sMoonDisplay = NULL;

//disable header, footer and led to maximize the canvas size
int savedStatusHeader, savedStatusLeds, savedStatusFooter;

/*
 * function that creates a menu*/
void menuGoalDisplayMoon(void){
	char choice = 0;
	const char *MenuUser[] ={
	"Sale", "Bill Payment", "Sale CashBack"
	}; initUIContext(_OFF_);

	  do
	  {
	    //Display the menu using GOAL
	    choice = GL_Dialog_Menu(mGoal, "POS PROJECT", MenuUser, choice,
	            GL_BUTTON_NONE , GL_KEY_0, GL_TIME_INFINITE);

	    switch (choice)
	    {
	//    case 0:
	//      // Displays a GOAL sample dialog
	//    	GL_Dialog_Amount(mGoal, "Bill Payment",
	//          "Enter Name: ", 'd',  'c', 20,
	//       GL_TIME_MINUTE);
	//      break;   2 *
	    case 1:
	    	GL_Dialog_Message(mGoal, "Sale CashBack",
	    	          "This is the\ndialog message", GL_ICON_INFORMATION, GL_BUTTON_VALID,
	    	          3 * GL_TIME_SECOND);
	    	break;
	    case 2:
	      // Loads a GOAL resource file
	      dateScreenUseGoalResource();
	    	GL_Dialog_Message(mGoal, "Sale CashBack",
	    	    	          "This is the\ndialog message", GL_ICON_INFORMATION, GL_BUTTON_VALID,
	    	    	          3 * GL_TIME_SECOND);
	      break;
	    default:
	      //exit
	      break;
	    }
	  } while (choice != 2);

	  releaseUIContext();

	  return;
	}





void initUIContext(int displayHeaderFooterLeds)
{
	if(displayHeaderFooterLeds != _OFF_ && displayHeaderFooterLeds != _ON_) {
		displayHeaderFooterLeds = _OFF_;
	}
	savedStatusHeader=DisplayHeader(displayHeaderFooterLeds);
	savedStatusLeds=DisplayLeds(displayHeaderFooterLeds);
	savedStatusFooter=DisplayFooter(displayHeaderFooterLeds);

    // Open display
    sMoonDisplay = Telium_Fopen("DISPLAY", "w*");
    // Open keyboard
    sMoonKeyboard = Telium_Fopen("KEYBOARD", "r*");

    return;
}

/**
 * Restore display context
 */
void releaseUIContext(void)
{
    // close keyboard
    if (sMoonKeyboard)
    {
        Telium_Fclose(sMoonKeyboard);
        sMoonKeyboard = NULL;
    }
    // close display
    if (sMoonDisplay)
    {
        Telium_Fclose(sMoonDisplay);
        sMoonDisplay = NULL;
    }

	// Restore display context
	DisplayHeader(savedStatusHeader);
	DisplayLeds(savedStatusLeds);
	DisplayFooter(savedStatusFooter);

	return;
}
