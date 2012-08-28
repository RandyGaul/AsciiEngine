////////////////////////////////////////////////////
// Copyright (c) 2012 ICRL
// See the file LICENSE.txt for copying permission.
// 
// Original Author: Randy Gaul
// Date:   7/3/2012
// Contact: r.gaul@digipen.edu
////////////////////////////////////////////////////

#ifndef GLOBALDEFINESH
#define GLOBALDEFINESH

#include <windows.h>
#include <assert.h>
#include <crtdbg.h>
#include "Properties.h"

#define CLIENT_WIDTH        75
#define CLIENT_WIDTH_HALF   37.5f
#define CLIENT_HEIGHT       50
#define CLIENT_HEIGHT_HALF  25.0f

#define FPS_LIMIT ((float)( 30 ))
// Compile switch for displaying (or not) the FPS onto the screen
#define DISPLAY_FPS

#define TRUE 1
#define FALSE 0

#define TRANSPERANT 255

#define GRAVITY 80.f
#define PLAYER_JUMP_HEIGHT -33.0f
#define LEFT_RIGHT_SPEED 15.f

// CAMERA STUFF
#define ENABLE_CAM 1
#define DISABLE_CAM 0
#define CAMOFFX ((self->base.enableCam) ? 0 : GLOBAL_CAM.center.x_)
#define CAMOFFY ((self->base.enableCam) ? 0 : GLOBAL_CAM.center.y_ + 1)

// VISUALS
#define DAMAGE_TEXT_FLOAT_VEL -5.f
#define DAMAGE_TEXT_FLOAT_TIME 2.f
#define ITEM_PARTICLE_SPAWN_COUNT 6
#define ITEM_PARTICLE_VELOCITY_RANGE 10
#define ITEM_PARTICLE_DELAY (float)RandomInt( 1, 4 ) / 8.f

// UI stuff
#define INVENTORY_BUTTON_DEBOUNCE_TIME .1f

// Takes a pointer and returns a pointer offset in bytes
#define PtrAdd( ptr, offset ) \
  (((char *)ptr) + offset)

#define DT_MAX 60.0f

typedef enum
{
  RETURN_SUCCESS,
  RETURN_FAILURE
} RETURN_TYPE;

/* ASCII key definitions */
#define ASCII_a (unsigned char)97
#define ASCII_b (unsigned char)98
#define ASCII_c (unsigned char)99
#define ASCII_d (unsigned char)100
#define ASCII_e (unsigned char)101
#define ASCII_f (unsigned char)102
#define ASCII_g (unsigned char)103
#define ASCII_h (unsigned char)104
#define ASCII_i (unsigned char)105
#define ASCII_j (unsigned char)106
#define ASCII_k (unsigned char)107
#define ASCII_l (unsigned char)108
#define ASCII_m (unsigned char)109
#define ASCII_n (unsigned char)110
#define ASCII_o (unsigned char)111
#define ASCII_p (unsigned char)112
#define ASCII_q (unsigned char)113
#define ASCII_r (unsigned char)114
#define ASCII_s (unsigned char)115
#define ASCII_t (unsigned char)116
#define ASCII_u (unsigned char)117
#define ASCII_v (unsigned char)118
#define ASCII_w (unsigned char)119
#define ASCII_x (unsigned char)120
#define ASCII_y (unsigned char)121
#define ASCII_z (unsigned char)122
#define ASCII_RETURN (unsigned char)13
#define ASCII_BACKSPACE (unsigned char)8
#define ASCII_SPACE (unsigned char)32

#define ASCII_A (unsigned char)65
#define ASCII_B (unsigned char)66
#define ASCII_C (unsigned char)67
#define ASCII_D (unsigned char)68
#define ASCII_E (unsigned char)69
#define ASCII_F (unsigned char)70
#define ASCII_G (unsigned char)71
#define ASCII_H (unsigned char)72
#define ASCII_I (unsigned char)73
#define ASCII_J (unsigned char)74
#define ASCII_K (unsigned char)75
#define ASCII_L (unsigned char)76
#define ASCII_M (unsigned char)77
#define ASCII_N (unsigned char)78
#define ASCII_O (unsigned char)79
#define ASCII_P (unsigned char)80
#define ASCII_Q (unsigned char)81
#define ASCII_R (unsigned char)82
#define ASCII_S (unsigned char)83
#define ASCII_T (unsigned char)84
#define ASCII_U (unsigned char)85
#define ASCII_V (unsigned char)86
#define ASCII_W (unsigned char)87
#define ASCII_X (unsigned char)88
#define ASCII_Y (unsigned char)89
#define ASCII_Z (unsigned char)90

/* Virtual key definitions (type int) */
// http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
typedef enum _VIRTUAL_KEY
{
  VK_0 = 0x30,
  VK_1,
  VK_2,
  VK_3,
  VK_4,
  VK_5,
  VK_6,
  VK_7,
  VK_8,
  VK_9,
  VK_A = 0x41,
  VK_B,
  VK_C,
  VK_D,
  VK_E,
  VK_F,
  VK_G,
  VK_H,
  VK_I,
  VK_J,
  VK_K,
  VK_L,
  VK_M,
  VK_N,
  VK_O,
  VK_P,
  VK_Q,
  VK_R,
  VK_S,
  VK_T,
  VK_U,
  VK_V,
  VK_W,
  VK_X,
  VK_Y,
  VK_Z,
  VK_ENTER = 0x0D,
} VIRTUAL_KEY;

#endif  GLOBALDEFINESH