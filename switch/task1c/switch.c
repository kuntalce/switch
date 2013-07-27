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


void buffer_lock()
{
  int status;

   status = pthread_mutex_lock(&bufferSpace.mutex);   
   if (status != 0) {
      printf("Error locking mutex in buffer data structure\n");
      exit(0);
   }
}


void buffer_unlock()
{
   int status;

   status = pthread_mutex_unlock(&bufferSpace.mutex);   
   if (status != 0) {
      printf("Error unlocking mutex in buffer data structure\n");
      exit(0);
   }
}

static void forward_message(int input_port)
{
	port_t inputPort=in_port[input_port];
	port_lock(&inputPort);

   	/* If the input port flag is high, that means a packet is there. */
	if(in_port[input_port].flag)
	{
		packet_t packet; 
		 /* Copy the packet from the port */
		packet_copy(&inputPort.packet,&packet);

		in_port[input_port].flag = (BOOL)0;


		bufferSpace.packets[ bufferSpace.writeIndex++%BUFFERLENGTH] =packet;
	}
	port_unlock(&inputPort);
}
static void short_sleep()
{
   struct timespec delay_time, what_time_is_it;

   delay_time.tv_sec = 0;
   delay_time.tv_nsec = HARNESS_SPEED;

   nanosleep(&delay_time, &what_time_is_it);
}
void *processOutputs(void *arg)
{
	while(!die) 
	{
		if(bufferSpace.writeIndex>bufferSpace.readIndex)
		{

				packet_t packet=bufferSpace.packets		[bufferSpace.readIndex++%BUFFERLENGTH]; 
				int outPort=cam_lookup_address(&packet.address);

				//port_t outputPort=out_port[outPort];
				port_lock(&(out_port[outPort]));
				 /* Copy the packet to the port */
				packet_copy(&packet,
			       &(out_port[outPort].packet));

				out_port[outPort].flag= TRUE;

				port_unlock(&(out_port[outPort]));
		}

		short_sleep();
	}

}

void *switch_thread_routine(void *arg)
{

bufferSpace.readIndex=0;
bufferSpace.writeIndex=0;	
int i=0;
pthread_t switch_child_id;
int status = pthread_create(&switch_child_id,
                           NULL,
                           processOutputs,
                           NULL);

   if (status != 0) {
      printf("Error creating switch child thread\n");
      exit(0);
   }
	status = pthread_detach(switch_child_id);
   if (status != 0) {
      printf("Error detaching switch child thread\n");
      exit(0);
   }


while(!die) 
{

	for(i=0;i<4;i++) 
	{
 		forward_message(i);	
 	}
      short_sleep();
}

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
