////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/8/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef MESSAGEH
#define MESSAGEH

#include "GlobalDefines.h"

typedef enum
{
  MESSAGE_NONE,
  MESSAGE_FLY_UPWARDS,
} MESSAGE_ID;

typedef struct _AE_MESSAGE
{
	MESSAGE_ID ID_;                   // ID of this type of message
  struct _AE_MESSAGE *nextMessage_; // Pointer to the next message in the message queue
  struct _AE_MESSAGE *prevMessage_; // Pointer to the previous message in the message queue
} AE_MESSAGE;

#endif  MESSAGEH