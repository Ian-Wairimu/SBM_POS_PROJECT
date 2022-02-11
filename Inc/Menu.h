/**
 * Menu.h
 *
 * Header for the Menu source file.
 *
 */
#ifndef __MENU_H
#define __MENU_H
#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}

#include <GL_GraphicLib.h>

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/

/*+************* STRUCTURES ************************************************+*/

/*+************* VARIABLES *************************************************+*/
//extern T_GL_HGRAPHIC_LIB gGoalGraphicLibInstance;
extern T_GL_HGRAPHIC_LIB mGoal;


/*+************* FUNCTION PROTOTYPES ***************************************+*/
extern int menuGoalDisplay(void);
extern void initUIContext(int);
extern void releaseUIContext(void);
extern void amountValidation(void);
extern int saleMenuDisplay(void);
extern int billMenuDisplay(void);
extern int cashBackMenuDisplay(void);
extern int saleMenuPassword(void);


#endif //__MENU_H
