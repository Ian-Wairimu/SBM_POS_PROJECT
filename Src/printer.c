#include <sdk_tplus.h>
#include "Menu.h"
#include <stdlib.h>

//int insert_card(NO_SEGMENT num, S_TRANSIN *param_in, S_ETATOUT *param_out);
//int card_inside(NO_SEGMENT no, S_TRANSIN *param_in, S_TRANSOUT *param_out);
//int chip_card(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out);
//int debit_emv(NO_SEGMENT no, S_TRANSIN * param_in, S_TRANSOUT * param_out);

static char appName[OBJECT_NAME_LEN + 1];

int insert_card(NO_SEGMENT no, S_TRANSIN *param_in, S_ETATOUT *param_out)
{
    int iRet;

    // Return application state
    param_out->returned_state[param_out->response_number].state.response = REP_KO;
    iRet = is_name(no, PT_NULL, param_out);

    return iRet;
}

int card_inside(NO_SEGMENT no, S_TRANSIN *param_in, S_TRANSOUT *param_out)
{
    bool card_accepted = TRUE;

    if (card_accepted)
    {
        // Return transaction status
        param_out->rc_payment = PAY_OK; // Transaction done, polling is stop
        return (STOP);
    }
    else
    {
        return (FCT_OK); // Card refused, poll the next application
    }
}
int chip_card(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
{

    // case of chip card
    if (param_in->support == CHIP_SUPPORT)
    {
        if(param_in->power_on_result == 0)
        {
            // accept this card
            param_out->returned_state[param_out->response_number].cardappnumber = 1;
            param_out->returned_state[param_out->response_number].cardapp[0].priority = CARD_PROCESSED;
        }
        else
        {
            // reject the card
            param_out->returned_state[param_out->response_number].cardappnumber = 0;
        }
    }

    // case of stripe 2 card
    if (param_in->support == TRACK2_SUPPORT)
    {
        // accept this card
        param_out->returned_state[param_out->response_number].cardappnumber = 1;
        param_out->returned_state[param_out->response_number].cardapp[0].priority = CARD_PRIORITY;
    }

    // case of Card Number Manual entry
    if (param_in->support == OPERATOR_SUPPORT)
    {
        // accept this card
        param_out->returned_state[param_out->response_number].cardappnumber = 1;
        param_out->returned_state[param_out->response_number].cardapp[0].priority = CARD_PRIORITY;
    }

    // give my application name
    strcpy(param_out->returned_state[param_out->response_number].appname, appName);
    // give my application number
    param_out->returned_state[param_out->response_number].no_appli = no;
    // give my card name
    strcpy(param_out->returned_state[param_out->response_number].cardapp[0].cardappname, "Template");
    // increment the response number
    param_out->response_number++;

    return (FCT_OK);
}
int debit_emv(NO_SEGMENT no, S_TRANSIN * param_in, S_TRANSOUT * param_out)
{
    Telium_File_t *prt;
    int i;

    prt = Telium_Fopen("PRINTER", "w-");

    // case of chip card
    if (param_in->support == CHIP_SUPPORT)
    {
        Telium_Pprintf("\x1b""E%s\n""\x1b""F", appName);
        if (param_in->historical_bytes.length != 0)
        {
            Telium_Pprintf("Atr:\n");
            for (i=0; i<param_in->historical_bytes.length; i++)
            {
                Telium_Pprintf("%02X ", param_in->historical_bytes.historic[i]);
            }
        }
        else
        {
            Telium_Pprintf("Synchronous card\n");
            Telium_Pprintf("or Chip mute\n");
        }
        Telium_Pprintf("\n\n\n\n\n\n");
    }

    // case of stripe 2 card
    if (param_in->support == TRACK2_SUPPORT)
    {
        Telium_Pprintf("\x1b""E%s\n""\x1b""F", appName);
        Telium_Pprintf("Track2:\n%s\n\n\n\n\n\n", param_in->track2);
    }

    // case of Card Number Manual entry
    if (param_in->support == OPERATOR_SUPPORT)
    {
        Telium_Pprintf("\x1b""E%s\n""\x1b""F", appName);
        Telium_Pprintf("Manual Entry:\n%s\n\n\n\n\n\n", param_in->track2);
    }

    Telium_Ttestall(PRINTER, 2*100);
    Telium_Fclose(prt);

    param_out->noappli = no; // Return application number
    param_out->rc_payment = PAY_OK; // Transaction done

    return (FCT_OK);
}
