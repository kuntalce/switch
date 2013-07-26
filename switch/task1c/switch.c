/*******************************************************
 *
 *  Switch Routines
 *
 *  Created by G10, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the switch routines.  You should use the headers as
 *  supplied.  All your code for Assignment 2 will go in this
 *  file (and possibly in switch.h)
 *
 ******************************************************/

#include "defs.h"

void *switch_thread_routine(void *arg)
{
   /* Add your code here */
}


void switch_init()
{
   /* Add your code here.  At the very least, you probably
      want to include a call to cam_init() */
}

void switch_add_entry(ip_address_t *address,
                      int port)
{
   cam_add_entry(address,port);
}

void switch_free()
{
   /* add your code (if any) here */
}
