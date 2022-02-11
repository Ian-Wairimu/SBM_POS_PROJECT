

int GoalGetKey(T_GL_HWIDGET hWindow, T_GL_HGRAPHIC_LIB hGraphicLib, bool bShortcut, ulong ulTimeOut, bool bClear)
{
	// Local variables
    // ***************
	Telium_File_t *hKeybd=NULL;  // Handle peripheral Keyboard
	Telium_File_t *hTsc=NULL;  // Handle peripheral Touch Screen
#ifndef __TELIUM3__
	bool bTouch;
#endif
	T_GL_WCHAR ulKey;
	int iRet;

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
#ifndef __TELIUM3__
	bTouch = GL_GraphicLib_IsTouchPresent(hGraphicLib);       // Touch screen?
	if (bTouch)
	{                                                         // Yes,
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_F);       // Unbind "F" key to Telium Key
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_DOT);     // Unbind "Dot" key to Telium Key
	}
	else
	{                                                         // No,
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_UP);      // Unbind "Up" key to Telium Key
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_DOWN);    // Unbind "Down" key to Telium Key
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_F1);      // Unbind "F1" key to Telium Key
		GL_GraphicLib_UnbindKey(hGraphicLib, GL_KEY_F4);      // Unbind "F4" key to Telium Key
	}
#endif

	// Restart timer
	// *************
	if (ulTimeOut == GL_TIME_INFINITE)                        // Set timeout value
		GL_Timer_SetInterval(GL_Widget_SearchId(hWindow, TIMER_ID), 0x7FFFFFFF);          // Bug 0xFFFFFFFF not supported
	else
		GL_Timer_SetInterval(GL_Widget_SearchId(hWindow, TIMER_ID), ulTimeOut);

	// Detect key pressed
	// ******************
	if (!bShortcut)                                           // Remove shortcut and enable callback on key pressed?
	{                                                                                     // Yes
		GL_Widget_RegisterCallback(hWindow, GL_EVENT_KEY_DOWN, CallBackPressKey);         // Call back when key pressed
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_CAN_ID), GL_KEY_NONE);   // Remove shortcut from cancel button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_VAL_ID), GL_KEY_NONE);   // Remove shortcut from valid button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_DOWN_ID), GL_KEY_NONE);  // Remove shortcut from down button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_UP_ID), GL_KEY_NONE);    // Remove shortcut from up button
	}

	// Reset FIFO keyboard and touch
	// *****************************
	if (bClear)
	{
		hKeybd = Telium_Stdperif("KEYBOARD", NULL);             // Check "keyboard" peripheral opened?
		if(hKeybd)
			Telium_Reset_buf(hKeybd, _receive_id);              // Yes, reset "keyboard" FIFO

		hTsc = Telium_Stdperif("TSCREEN", NULL);              // Check "touch" peripheral opened?
		if(hTsc)
			Telium_Reset_buf(hTsc, _receive_id);              // Yes, reset "touch" FIFO
	}
	GL_Window_MainLoop(hWindow);                              // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(hWindow))                      // Get the result
	{
	case RES_PRESS_STATUS:                                    // Key press result
		GL_Timer_Stop(GL_Widget_SearchId(hWindow, TIMER_ID));
		GL_Widget_GetUserData(hWindow, &ulKey, sizeof(ulKey));
		iRet=ulKey;
		break;
	case RES_VALID_STATUS:                                    // Key valid result
		GL_Timer_Stop(GL_Widget_SearchId(hWindow, TIMER_ID));
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                                   // Key cancel result
		GL_Timer_Stop(GL_Widget_SearchId(hWindow, TIMER_ID));
		iRet=GL_KEY_CANCEL;
		break;
	case RES_DOWN_STATUS:                                     // Key down result
		GL_Timer_Stop(GL_Widget_SearchId(hWindow, TIMER_ID));
		iRet=GL_KEY_DOWN;
		break;
	case RES_UP_STATUS:                                       // Key up result
		GL_Timer_Stop(GL_Widget_SearchId(hWindow, TIMER_ID));
		iRet=GL_KEY_UP;
		break;
	case RES_TIMER_STATUS:                                    // Timer result
		iRet=0;
		break;
	default:                                                  // Unknown result
		iRet=0;
		break;
	}

	if (!bShortcut)                                           // Restore shortcut and disable callback on key pressed?
	{                                                                                     // Yes
		GL_Widget_UnregisterCallback(hWindow, GL_EVENT_KEY_DOWN, CallBackPressKey);       // Unregister call back on key pressed
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_CAN_ID), GL_KEY_CANCEL); // Set shortcut on cancel button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_VAL_ID), GL_KEY_VALID);  // Set shortcut on valid button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_DOWN_ID), GL_KEY_DOWN);  // Set shortcut on down button
		GL_Widget_SetShortcut(GL_Widget_SearchId(hWindow, BUTTON_UP_ID), GL_KEY_UP);      // Set shortcut on up button
	}

#ifndef __TELIUM3__
	if (bTouch)                                               // Touch screen?
	{                                                                                     // Yes
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_F, GL_VIRTUAL_KEY_PREVIOUS);      // Bind "F" key to virtual Key
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_DOT, GL_VIRTUAL_KEY_NEXT);        // Bind "Dot" key to virtual Key
	}
	else
	{                                                                                     // No
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_UP, GL_VIRTUAL_KEY_PREVIOUS);     // Bind "Up" key to virtual Key
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_DOWN, GL_VIRTUAL_KEY_NEXT);       // Bind "Down" key to virtual Key
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_F1, GL_VIRTUAL_KEY_LEFT);         // Bind "F1" key to virtual Key
		GL_GraphicLib_BindSingleKey(hGraphicLib, GL_KEY_F4, GL_VIRTUAL_KEY_RIGHT);        // Bind "F4" key to virtual Key
	}
#endif

	return iRet;
}
void GoalDestroyScreen(T_GL_HWIDGET *phWindow)
{
	// Local variables
    // ***************
		// Empty

	// Destroy screen
	// **************
	GL_Widget_Destroy(*phWindow); // Destroy window with all widgets attached
	*phWindow=NULL;
}

T_GL_HWIDGET GoalCreateScreen (T_GL_HGRAPHIC_LIB hGraphicLib, const ST_DSP_LINE txLine[], ushort usMaxLine, T_GL_ENCODING_CHARSET eCharSet)
{
	// Local variables
    // ***************
	T_GL_HWIDGET hWindow, hTimer, hLayout, hLabel, hLayout2, hButtonVal, hButtonCan, hButtonDown, hButtonUp;
	bool bTouch;
	ushort usLine;

	// Build screen context with MAX labels and 4 buttons (Cancel, Valid, Down and Up)
	// *******************************************************************************
	GL_GraphicLib_SetCharset(hGraphicLib, eCharSet);                                  // Change the encoding charset of the graphic library

	bTouch = GL_GraphicLib_IsTouchPresent(hGraphicLib);                               // Is it a touch screen?

	hWindow = GL_Window_Create(hGraphicLib);                                          // Create a window in the user area
	CHECK(hWindow!=NULL, lblKO);

	hTimer = GL_Timer_Create(hWindow);                                                // Create a timer on this window
	CHECK(hTimer!=NULL, lblKO);
	GL_Widget_SetId(hTimer, TIMER_ID);                                                // Timer Identifier TIMER_ID
	GL_Widget_RegisterCallback(hTimer, GL_EVENT_TIMER_OUT, CallBackTimeout);          // Call back when the timer expired

	hLayout = GL_Layout_Create(hWindow);                                              // Create a layout on this window
	CHECK(hLayout!=NULL, lblKO);

	for (usLine=0; usLine<usMaxLine; usLine++)                                        // Build labels on this layout
	{
		hLabel = GL_Label_Create(hLayout);                                            // Create a label on this layout
		CHECK(hLabel!=NULL, lblKO);
		GL_Widget_SetItem(hLabel, 0, usLine);                                         // Label location on this layout
		GL_Widget_SetText(hLabel, NULL);                                              // Clear text on this label
		GL_Widget_SetShrink(hLabel, GL_DIRECTION_WIDTH);                              // Shrink beyond its size (No width scrolling cell if label goes over screen)
		if (IsColorDisplay())                                                         // Color display?
			GL_Widget_SetFontScale(hLabel, txLine[usLine].xColor.xFont.eScale);       // Yes, font scale color
		else
			GL_Widget_SetFontScale(hLabel, txLine[usLine].xBW.xFont.eScale);          // No, font scale B&W
		GL_Widget_SetId(hLabel, LABEL_0_ID+usLine);                                   // Label identifier LABEL0_ID + (0..8)
	}

	hLayout2 = GL_Layout_Create(hLayout);                                             // Create a second layout on this layout
	CHECK(hLayout2!=NULL, lblKO);
	GL_Widget_SetId(hLayout2, LAYOUT2_ID);                                            // Second layout identifier
	GL_Widget_SetItem(hLayout2, 0, usLine);                                           // Second layout location on this layout
	GL_Widget_SetGrow(hLayout2, GL_DIRECTION_WIDTH);                                  // Grow beyond its size (Background width around layout will fill the complete cell)

	hButtonCan = GL_Button_Create(hLayout2);                                          // Create a cancel button on this second layout
	CHECK(hButtonCan!=NULL, lblKO);
	GL_Widget_SetSource(hButtonCan, "skin://images/cancel.wgu");                      // Set the cancel skinned image
	GL_Widget_SetItem(hButtonCan, 0, 0);                                              // Button location on this layout
	GL_Widget_SetExpand(hButtonCan, GL_DIRECTION_WIDTH);                              // Expand button width
	GL_Widget_SetShortcut(hButtonCan, GL_KEY_CANCEL);                                 // Shortcut on this button
	GL_Widget_SetId(hButtonCan, BUTTON_CAN_ID);                                       // Cancel button Identifier
	GL_Widget_SetGrow(hButtonCan, GL_DIRECTION_WIDTH);                                // Grow beyond its size (Background width around cancel button will fill the complete cell)
	GL_Widget_SetFocusable(hButtonCan, false);                                        // No focus on this button
	GL_Widget_RegisterCallback(hButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Call back when key pressed

	hButtonDown = GL_Button_Create(hLayout2);                                         // Create a down button on this layout
	CHECK(hButtonDown!=NULL, lblKO);
	GL_Widget_SetSource(hButtonDown, "skin://images/downArrow.wgu");                  // Set the down arrow skinned image
	GL_Widget_SetItem(hButtonDown, 1, 0);                                             // Button location on this layout
	GL_Widget_SetExpand(hButtonDown, GL_DIRECTION_WIDTH);                             // Expand button width
	GL_Widget_SetForeColor(hButtonDown, GL_COLOR_WHITE);                              // Foreground color
	if (bTouch)
		GL_Widget_SetShortcut(hButtonDown, GL_KEY_DOT);                               // Shortcut on this button
	else
		GL_Widget_SetShortcut(hButtonDown, GL_KEY_DOWN);                              // Shortcut on this button
	GL_Widget_SetId(hButtonDown, BUTTON_DOWN_ID);                                     // Down button Identifier
	GL_Widget_SetGrow(hButtonDown, GL_DIRECTION_WIDTH);                               // Grow beyond its size (Background width around down button will fill the complete cell)
	GL_Widget_SetFocusable(hButtonDown, false);                                       // No focus on this button
	GL_Widget_RegisterCallback(hButtonDown, GL_EVENT_STYLUS_CLICK, CallBackDownKey);  // Call back when key pressed

	hButtonUp = GL_Button_Create(hLayout2);                                           // Create a up button on this layout
	CHECK(hButtonUp!=NULL, lblKO);
	GL_Widget_SetSource(hButtonUp, "skin://images/upArrow.wgu");                      // Set the up arrow skinned image
	GL_Widget_SetItem(hButtonUp, 2, 0);                                               // Button location on this layout
	GL_Widget_SetExpand(hButtonUp, GL_DIRECTION_WIDTH);                               // Expand button width
	GL_Widget_SetForeColor(hButtonUp, GL_COLOR_WHITE);                                // Foreground color
	if (bTouch)                                                                       // Touch screen?
		GL_Widget_SetShortcut(hButtonUp, GL_KEY_F);                                   // Yes, Shortcut (Key F) on this button
	else
		GL_Widget_SetShortcut(hButtonUp, GL_KEY_UP);                                  // No, Shortcut (Key Up) on this button
	GL_Widget_SetId(hButtonUp, BUTTON_UP_ID);                                         // Up button Identifier
	GL_Widget_SetGrow(hButtonUp, GL_DIRECTION_WIDTH);                                 // Grow beyond its size (Background width around up button will fill the complete cell)
	GL_Widget_SetFocusable(hButtonUp, false);                                         // No focus on this button
	GL_Widget_RegisterCallback(hButtonUp, GL_EVENT_STYLUS_CLICK, CallBackUpKey);      // Call back when key pressed

	hButtonVal = GL_Button_Create(hLayout2);                                          // Create a valid button on this second layout
	CHECK(hButtonVal!=NULL, lblKO);
	GL_Widget_SetSource(hButtonVal, "skin://images/validation.wgu");                  // Set the valid skinned image
	GL_Widget_SetItem(hButtonVal, 3, 0);                                              // Button location on this layout
	GL_Widget_SetExpand(hButtonVal, GL_DIRECTION_WIDTH);                              // Expand button width
	GL_Widget_SetShortcut(hButtonVal, GL_KEY_VALID);                                  // Shortcut on this button
	GL_Widget_SetId(hButtonVal, BUTTON_VAL_ID);                                       // Valid button Identifier
	GL_Widget_SetGrow(hButtonVal, GL_DIRECTION_WIDTH);                                // Grow beyond its size (Background width around valid button will fill the complete cell)
	GL_Widget_SetFocusable(hButtonVal, false);                                        // No focus on this button
	GL_Widget_RegisterCallback(hButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey);  // Call back when key pressed

	if(!bTouch)                                                                       // Touch screen?
		GL_Widget_SetVisible(hLayout2, false);                                        // No, do not show second layout (keep shortcut access on key pressed)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                                // Window creation failed
	if (hWindow)
	{
		GL_Widget_Destroy(hWindow);                                                   // Destroy window and all widgets
		hWindow=NULL;
	}
	goto lblEnd;
lblEnd:
	return hWindow;
}
