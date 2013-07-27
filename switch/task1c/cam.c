
/*******************************************************
 *
 *  Routing Table Routines
 *
 *  Created by G10, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the routing table.  You should use the headers as
 *  supplied.  All your code will go in this
 *  file (and in cam.h)
 *
 ******************************************************/

#include "defs.h"

/* Note that you probably want to have a data structure
   that is accessable to all routines in this file.  To do
   this, you probably would define some structure (perhaps
   called cam_t in the file cam.h.  Then you could 
   create a variable of this type here by using:

   cam_t cam;

   This will create  a variable called cam (of type cam_h)
   that can be accessed by any routine in this file.  */
#include<iostream>
#include<unordered_map>
using namespace std;

typedef unordered_map<unsigned long long, int>  Routes;
Routes routes;
void cam_init()
{

}
//Get the hash for the ip
unsigned long long getHash(ip_address_t *address)
{
	long long a=1000000000;
	long long b=1000000;
	long long c=1000;
	return a*address->n1+b*address->n2+c*address->n3+address->n4;
}
void cam_add_entry(ip_address_t *address, int port)
{
	unsigned long long hash=getHash(address);
	routes.insert(make_pair(hash,port));
}

int cam_lookup_address(ip_address_t *address)
{

	unsigned long long hash=getHash(address);
	Routes::const_iterator iter=routes.find(hash);
	//if not found
	if(iter == routes.end())
	{
		return -1;
	}
	return routes.find(hash)->second;
}

void cam_free()
{
   /* Write your code here */
}
