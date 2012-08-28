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

typedef enum ENTITY_MESSAGE
{
  // CLASS OPERATIONS
  EM_CLSINIT, // Initialize static class variables and resources
              // PARAM is class name -- char *
  EM_CLSFREE, // Free up class and resources used
  EM_CLSNAME, // Return class name char * within PARAM

  // CREATION AND DELETION OPERATIONS
  EM_CREATE,  // Constructor for entity
  EM_DESTROY, // Immediately destroy entity
  EM_INACTIVE,// Mark entity as inactive to be cleaned up by entity manager.

  // STANDARD ACTIONS
  EM_UPDATE,  // var1 is float * in seconds; For Physics components var2 is Entity *(owner)
  EM_DRAW,    // PARAM is AE_COORD * -- standard rendering

  // POSITION
  EM_SETPOS,  // var1 is float *, var2 is float * -- sets entity's position
  EM_GETPOS,  // Copies float x and y into float *var1 and var2

  // PHYSICS
  EM_SETVEL,  // Sets float x and float y vel to values from float pointers var1 and var2
  EM_GETVEL,  // Copies a float into float *var1 and float *var2 representing x and y vel
  EM_STEPXPOS,// Copies the stepped value of position x into float *var1,
              // var2 is (float *)dt provided for step
  EM_STEPYPOS,// Copies the stepped value of position y into float *var1,
              // var2 is (float *)dt provided for step
              // Does not actually modify anything, only retrieves values stepped by dt
  EM_SETACCEL,// PARAM is VECTOR2D * -- sets entity's velocity
  EM_GETACCEL,// Copies VECTOR2D into PARAM representing velocity
  EM_GRAVITY, // Applies gravity to the object, requires PhysicsComponent, var1 is float *dt
 
  // INPUT
  EM_GETINVEC,// Copies the input velocity vector into VECTOR2D *var1
  EM_SETINVEC,// Copies VECTOR2D *var1 into the input velocity vector
  EM_SETJUMP, // Sets the canJump data member of the PlayerComponent to BOOL *var1
  EM_GETJUMP, // Copies canJump data member of PlayerComponent into BOOL *var1
  EM_SETJUMPN,// Places the value of var1 into jumping
  EM_GETJUMPN,// Copies the jumping contents into BOOL *var1

  // ANIMATION
  EM_GETPLAYC,// Gets the playcount of the animation and copies into int *var1
  EM_SETPLAYC,// Sets the playcount from the data within int *var1
  EM_GETFRAME,// Gets the currentFrame of the animation and copies into int *var1
  EM_SETFRAME,// Sets the currentFrame from the data within int *var1
  EM_GETFRAMD,// Gets the frameDelay from the animation and copies into float *var1
  EM_SETFRAMD,// Copies the frameDelay in the animation to value of float *var1
  EM_GETISPAS,// Gets the isPaused from the animation and copies into BOOL *var1
  EM_SETISPAS,// Copies the isPaused in the animation to value of BOOL *var1

  // CLOUD
  EM_GETLOCUS,// Retrieves a pointer to a specific locus by const char *var1
              // stores pointer in LOCUS *var2
  EM_CLDSETIM,// Swaps the image * of locus const char *var1 with IMAGE *var2
  EM_CLDSETAN,// Swaps the image * of locus const char *var1 with ANIMATION *var2
  EM_INSLOCUS,// Inserts a locus from LOCUS *var1 into the cloud.
  EM_CLDFREAN,// Deallocates the animation of a specific locus at const char *var1
  EM_CLDTGLLC,// Toggles activity of a locus const char *var1
  EM_CLDSETLC,// Sets the activity of a locus const char *var1 to BOOL *var2
  EM_CLDOFFLC,// Sets the acvivity of a locus const char *var1 to FALSE
  EM_CLDONLC,// Sets the acvivity of a locus const char *var1 to FALSE

  // COLLISION
  EM_HITTEST, // Tests for collision with other game objects
              // var1 is the axis as a BOOL
              // var2 is pointer to COL_DATA
              // When recieved an object performs appropriate hittest and then
              // if there is a collision between the objects, a EM_IHITYOU message
              // is sent to the sender of the EM_HITTEST message
  EM_CIRCLE,  // Represents a circle; var1 of EM_HITTEST
  EM_RECT,    // Represents a rect; var1 of EM_HITTEST
  EM_IHITYOU, // A response message sent to the sender of a EM_HITTEST message
              // var1 is pointer to the sender (ENTITY *)
              // var2 is a bitfield flag of properties from Properties.h
  EM_COLTILE, // Represents a tile; var2 of EM_IHITYOU
  EM_SETWH,   // Sets the width and height of an entity of the values in var1 and var2
              // var1 -- float *width; var2 float *height
  EM_GETWH,   // Copies the width and height of an entity into var1 and var2
              // var1 -- float *width; var2 float *height
  EM_GETSHAPE,// Requests the type of shape from the reciever
              // Shape *is copied into var1
  EM_HITBOTOM,// Sends message to player component letting it know bottom was hit by a tile
  EM_GETHTBTM,// Copies contents of hitBottom from player component into BOOL *var1
  EM_SETHTBTM,// Sets the value of hitBottom to BOOL var1

  // ACTIONLIST
  EM_ALADDACT,// Adds an action to an object's actionList component. Var1 is ALT ID, var2 is flag
  EM_ALREMACT,// Removes an action within an action list. var1 is AL_NODE *node to remove

  // HITPOINTS
  EM_GETHP,   // Retrieves int HP and copies into int *var1
  EM_SETHP,   // Sets value of HP to int var1
  EM_DAMAGEHP,// Subtracts an int var1 from the hp data member, but does not go lower than zero
  EM_HEALHP,  // Adds an int var1 from the hp data member, but does not go above than self->maxHP

  // INVENTORY
  EM_GETINV,  // Copies value of inventory at index var2 into int *var1
  EM_SETINV,  // Copies value of ITEM_ID var1 into slot var2
  EM_GETINVSZ,// Copies the size in number of elements of the inventory array into int *var1
  EM_INSINV,  // Inserts a single ITEM_ID var1 into first available slot within inventory
  EM_INVEJECT,// Creates an item entity for each item in the inventory, and empties the inventory.
  EM_INVGDRAW,// Copies drawMe into BOOL *var1
  EM_INVSDRAW,// Copies content of BOOL *var1 into drawMe
  EM_INVTDRAW,// Toggles the drawMe value from FALSE and TRUE
} EM;

#endif  MESSAGEH