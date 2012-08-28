////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/22/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#include "Hitpoints.h"
#include "EntityManager.h"
#include "EntityFactory.h"

// Static class variables and data
static const char *CLASS_NAME = NULL;

//
// ClassCOM_PROC
// Purpose: Component procedure for this component type. Dispatches messages
//          recieved in the appropriate manner.
//
void HitPointsCOM_PROC( HP *self, EM msg, int var1, int var2 )
{
  // GENERAL
  switch(msg)
  {
  case EM_CLSINIT:
    HitPointsInit( (const char *)var1 );
    break;
  case EM_CREATE:
    HitPointsCreate( self, var1 );
    break;
  case EM_UPDATE:
    HitPointsUpdate( self, (float *)var1 );
    break;

  // DATA ACCESS
  case EM_GETHP:
    HitPointsGet( self, (int *)var1 );
    break;
  case EM_SETHP:
    HitPointsSet( self, var1 );
    break;
  case EM_DAMAGEHP:
    HitPointsDamage( self, var1 );
    break;
  case EM_HEALHP:
    HitPointsHeal( self, var1 );
    break;
  }
}

//
// ClassCreate
// Purpose: Acts as a constructor for this class. Initializes the
//          data and dynamically allocates any extra space needed, and
//          initializes the allocated space with data.
//
void HitPointsCreate( HP *self, int hp )
{
  self->hp = (hp >= 0) ? hp : 1;
  // FIXME : ability to set maxhp through param2
  self->maxHP = 20;
}

//
// ClassInit
// Purpose: One-time initialization of the class. Use this function to load resources from disk,
//          set up static class variables, or anything else.
//
void HitPointsInit( const char *className )
{
  CLASS_NAME = (const char *)malloc( strlen( className ) + 1 );
  strcpy_s( (char *)CLASS_NAME, strlen( className ) + 1 , className );
}

//
// ClassUpdate
// Purpose: Uses float *dt to update various aspects of the component.
//
void HitPointsUpdate( HP *self, float *dt )
{
  if(self->hp == 0)
    SendEntityMessage( self->base.owner, EM_INACTIVE, 0, 0 );
}

//
// HitPointsGet
// Purpose: Retrieves int HP and copies into int *var1
//
void HitPointsGet( HP *self, int *hp )
{
  *hp = self->hp;
}

//
// HitPointsSet
// Purpose: Retrieves int HP and copies into int *var1
//
void HitPointsSet( HP *self, int hp )
{
  self->hp = (hp < self->maxHP) ? hp : self->maxHP;
}

//
// HitPointsDamage
// Purpose: Subtracts an int var1 from the hp data member, but does not go lower than zero
//
void HitPointsDamage( HP *self, int damage )
{
  if(self->hp - damage > 0)
    self->hp -= damage;
  else
    self->hp = 0;

  CreateEntity( "DAMAGE_TEXT", (int)self->base.owner, damage );
}

//
// HitPointsHeal
// Purpose: Adds an int var1 from the hp data member, but does not go above than self->maxHP
//
void HitPointsHeal( HP *self, int heal )
{
  if((self->hp + heal) < self->maxHP)
    self->hp += heal;
  else
    self->hp = self->maxHP;
}
