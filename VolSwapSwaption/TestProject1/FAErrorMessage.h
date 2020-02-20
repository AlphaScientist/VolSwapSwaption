/**
 *  Filename : FAErrorMessage.h
 *  All rights reserved.
 */

#ifndef FAERRORMESSAGE_H
#define FAERRORMESSAGE_H

#include <string.h>

#define MaxErrorLength 256
#define MaxMessages 10

struct error_struct
{
   char messageList[MaxMessages][MaxErrorLength];
   int lastSlot;   /* The last slot written to */
   int FreeSlots;   /* Decrementing counter */
   int lastErrorStatus;
};

static void FAInitializeErrorBuffer(struct error_struct *theErrorStruct);

static int FAWriteErrorMessage(struct error_struct *theErrorStruct,
       char *m,
       int errorType);

static int FAGetLastErrorMessage(struct error_struct *theErrorStruct, 
       char *theMessage);

static int FAGetErrorMessage(struct error_struct *theErrorStruct, 
	int slot, 
	char *theMessage);
 
static void FAInitializeErrorBuffer(struct error_struct *theErrorStruct)
{
  theErrorStruct->lastSlot = -1;
  theErrorStruct->FreeSlots = MaxMessages + 1;
  theErrorStruct->lastErrorStatus = 0;
}
 
static int FAWriteErrorMessage(struct error_struct *theErrorStruct, char *m,
   int errorType)
{
   /* Search for the next free slot. If there are none then start */
   /* Cycle to the start if there are no free slots */
 
   int nextSlot;
   nextSlot = (theErrorStruct->lastSlot + 1) % (MaxMessages);  
   /* Write the message set error type. Return the last index written to
    */
   strcpy(theErrorStruct->messageList[nextSlot], m);
   theErrorStruct->lastSlot = nextSlot;
   if (theErrorStruct->FreeSlots > 0)
     {theErrorStruct->FreeSlots--;}
   theErrorStruct->lastErrorStatus = errorType;
   return nextSlot;
}

static int FAGetLastErrorMessage(struct error_struct *theErrorStruct, char *
   theMessage)
  /* Check if there are any messages, return 0 if none else return the 
   error
     number associated with the last error message. */
{
  if (theErrorStruct->lastSlot == -1)
    {return 0;}
  {
    strcpy(theMessage,theErrorStruct->messageList[theErrorStruct->
   lastSlot]);
    return theErrorStruct->lastErrorStatus;
      }
}

static int FAGetErrorMessage(struct error_struct *theErrorStruct, int slot, 
   char *theMessage)
{
  if (theErrorStruct->lastSlot == -1)
    {return 0;}
  else
  {
    strcpy(theMessage,theErrorStruct->messageList[slot]);
    return slot;
      }
}


#endif  /* FAERRORMESSAGE_H */
