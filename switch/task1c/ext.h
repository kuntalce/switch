
/*******************************************************
 *
 *  Global External File
 *
 *  Sathish Gopalakrishnan
 *  University of British Columbia
 *
 *  This routine contains external references to the global
 *  variables in the system.  Global variables are used because
 *  we want to use shared memory to communicate between tasks
 *  (other methods will be discussed in class).  These variables
 *  are all defined in main.c, but by including this file, 
 *  other threads can access the variables directly.
 *
 ******************************************************/


/* Shared variables among all threads */

extern port_t in_port[4];
extern port_t out_port[4];
extern BOOL die;
extern Buffer bufferSpace;
