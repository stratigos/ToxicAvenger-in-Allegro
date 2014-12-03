/**************************************************************** 
* Todd Morningstar                                              *
* 12/08/2005                                                    *
* Project 4                                                     *
*                                                               *
* THE TOXIC AVENGER!                                            *
* User controlls toxie, and must eliminate all thugs in town    *
* If player looses all his/her hitpts, he/she looses the game   * 
*************************************************************** */

#include "allegro.h"

//define some convenient constants
#define MODE GFX_AUTODETECT_WINDOWED
#define BURST makecol(255,189,73)
#define WIDTH 640
#define MOPSPEED 10
#define HEIGHT 480
#define STEP 8
#define TILEW 32
#define TILEH 32
#define TILES 39
#define COLS 20

//define the toxic avenger struct
struct toxicavenger
{
    int x,y;
    int hits;
    int dir;
}toxie;

//define mop structure
struct toxicmop
{
    int x,y;
    int alive;
    int xspd,yspd;

} mop;

//define bad guy struct (cigar face, knuckles, and nipples)
struct thug
{
    int x,y, movementint;
    int hits;
    int dir;  
} thug[10];

//tiled map (created in mappy)
int map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 2,
1, 1, 3, 4, 5, 6, 1, 1, 1, 1, 1, 7, 8, 9, 1, 1, 
1, 10, 11, 12, 13, 14, 15, 1, 1, 1, 1, 16, 17, 18, 19, 1, 
1, 1, 1, 20, 21, 22, 23, 1, 1, 1, 1, 16, 17, 18, 19, 1, 
1, 2,
24, 25, 26, 27, 28, 29, 30, 31, 1, 32, 33, 34, 35, 36, 37, 38, 
39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 
55, 56, 57, 58, 59, 60, 61, 62, 63, 48, 49, 50, 51, 52, 53, 54, 
55, 2,
1, 64, 65, 1, 1, 66, 67, 68, 1, 69, 70, 1, 1, 1, 71, 72, 
73, 74, 75, 1, 1, 1, 1, 76, 77, 1, 78, 79, 1, 80, 81, 82, 
83, 1, 84, 85, 1, 1, 1, 86, 87, 1, 78, 79, 1, 80, 81, 82, 
83, 2,
88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 
89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 2,
91, 92, 93, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 94, 91, 91, 
91, 91, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 95, 
96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 
96, 97,
98, 99, 100, 101, 508, 91, 102, 91, 91, 490, 91, 91, 91, 103, 91, 91, 
508, 91, 104, 91, 91, 490, 91, 91, 105, 91, 91, 91, 91, 91, 507, 91, 
91, 91, 91, 91, 91, 489, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
107, 108, 109, 110, 111, 91, 91, 112, 113, 113, 113, 114, 113, 115, 116, 91, 
491, 91, 117, 91, 91, 91, 91, 91, 118, 91, 91, 91, 119, 120, 121, 91, 
91, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 490, 91, 91, 
91, 106,
122, 123, 124, 124, 125, 91, 91, 126, 127, 128, 128, 129, 130, 131, 132, 508, 
509, 91, 91, 133, 134, 135, 136, 137, 138, 139, 508, 91, 91, 91, 91, 507, 
91, 140, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
141, 142, 143, 144, 145, 146, 489, 148, 149, 150, 151, 152, 153, 154, 155, 156, 
157, 157, 507, 158, 159, 160, 161, 162, 163, 164, 157, 157, 157, 157, 157, 165, 
91, 166, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
167, 168, 169, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 
170, 171, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 172, 
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
173, 174, 175, 176, 177, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 
178, 179, 180, 181, 178, 178, 178, 178, 178, 178, 178, 182, 183, 178, 178, 184, 
185, 186, 187, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
188, 188, 189, 190, 191, 192, 192, 193, 178, 194, 188, 188, 195, 178, 178, 196, 
188, 197, 198, 178, 178, 196, 188, 188, 199, 178, 178, 200, 201, 178, 178, 202, 
203, 204, 205, 91, 91, 91, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
206, 206, 207, 208, 209, 210, 211, 212, 178, 213, 206, 206, 214, 178, 178, 215, 
216, 217, 218, 178, 178, 215, 206, 206, 218, 178, 219, 220, 221, 178, 178, 222, 
223, 224, 225, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
178, 178, 178, 226, 227, 228, 229, 178, 178, 178, 178, 178, 178, 178, 178, 230, 
231, 232, 233, 178, 178, 178, 178, 178, 178, 178, 234, 235, 178, 178, 178, 236, 
237, 238, 239, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
178, 178, 178, 178, 178, 178, 178, 178, 178, 240, 178, 178, 178, 178, 178, 178, 
178, 178, 241, 178, 178, 178, 178, 178, 178, 178, 178, 242, 243, 178, 178, 202, 
244, 245, 246, 91, 507, 91, 91, 91, 489, 91, 91, 91, 91, 91, 489, 91, 
91, 106,
247, 247, 247, 247, 247, 247, 247, 247, 247, 248, 247, 247, 247, 247, 247, 247, 
247, 247, 247, 247, 247, 247, 247, 249, 178, 178, 178, 178, 178, 178, 178, 250, 
251, 252, 253, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 508, 91, 254, 178, 178, 178, 178, 178, 178, 178, 255, 
256, 257, 258, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 508, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 259, 178, 178, 178, 260, 
261, 262, 263, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 490, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 264, 178, 265, 266, 202, 
267, 268, 269, 91, 91, 91, 91, 91, 91, 91, 91, 91, 490, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 270, 91, 91, 508, 91, 271, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 272, 273, 274, 275, 276, 
277, 277, 278, 91, 91, 91, 91, 490, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 489, 91, 91, 491, 91, 91, 91, 490, 91, 91, 91, 91, 91, 91, 
507, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 279, 178, 280, 281, 282, 
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 509, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 283, 284, 178, 178, 178, 285, 286, 282, 
91, 91, 91, 91, 91, 91, 91, 489, 91, 91, 91, 91, 91, 507, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 287, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 288, 289, 290, 178, 178, 178, 178, 282, 
91, 489, 91, 91, 91, 91, 91, 91, 91, 91, 490, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 291, 292, 293, 294, 178, 178, 178, 282, 
91, 91, 91, 91, 507, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 507, 91, 91, 91, 91, 91, 491, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 295, 296, 178, 297, 178, 178, 178, 282, 
91, 490, 91, 91, 91, 91, 91, 91, 91, 298, 299, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 490, 509, 91, 91, 91, 
91, 91, 91, 91, 490, 91, 91, 254, 178, 178, 178, 300, 178, 178, 178, 301, 
302, 303, 304, 305, 305, 305, 305, 306, 91, 307, 308, 91, 91, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 508, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 309, 178, 178, 178, 310, 
311, 312, 313, 314, 315, 316, 317, 318, 91, 91, 491, 91, 507, 91, 91, 91, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 178, 178, 178, 178, 310, 
319, 320, 321, 322, 323, 324, 325, 318, 91, 91, 509, 91, 91, 91, 91, 490, 
91, 106,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 489, 91, 91, 91, 91, 254, 178, 178, 178, 178, 178, 178, 178, 326, 
327, 328, 329, 330, 331, 332, 333, 334, 489, 335, 335, 335, 335, 335, 336, 337, 
338, 339,
91, 91, 91, 91, 91, 91, 91, 91, 491, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 91, 91, 91, 91, 254, 178, 178, 178, 178, 178, 340, 341, 178, 
178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 
178, 178,
91, 91, 489, 91, 490, 91, 91, 91, 509, 91, 91, 91, 91, 508, 91, 91, 
91, 91, 91, 491, 91, 91, 91, 254, 178, 178, 178, 342, 343, 344, 345, 346, 
178, 178, 178, 178, 178, 347, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 
178, 178,
91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 
91, 91, 91, 509, 91, 508, 91, 254, 348, 349, 178, 350, 351, 352, 353, 178, 
178, 178, 178, 178, 178, 354, 178, 178, 178, 355, 356, 178, 178, 178, 178, 178, 
178, 178,
91, 507, 91, 91, 91, 91, 91, 91, 91, 91, 91, 490, 91, 91, 91, 507, 
91, 91, 91, 91, 91, 91, 91, 254, 357, 358, 178, 178, 359, 360, 178, 178, 
361, 362, 362, 178, 178, 363, 364, 364, 365, 366, 367, 368, 368, 369, 178, 370, 
362, 371,
595, 596, 616, 596, 595, 596, 594, 593, 593, 616, 582, 595, 596, 593, 582, 593, 
595, 593, 596, 593, 582, 593, 582, 254, 178, 178, 635, 178, 178, 178, 178, 178, 
178, 178, 178, 178, 178, 178, 178, 178, 372, 373, 178, 178, 178, 178, 178, 178, 
178, 178,
374, 374, 374, 374, 374, 374, 374, 374, 374, 375, 374, 374, 374, 374, 376, 374, 
374, 374, 374, 374, 374, 374, 374, 377, 378, 378, 378, 378, 379, 378, 378, 378, 
380, 381, 378, 378, 378, 378, 378, 378, 378, 378, 378, 378, 378, 378, 378, 378, 
378, 382,
383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 
399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 
415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 
431, 432,
433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 438, 444, 445, 446, 447, 
438, 448, 438, 449, 450, 451, 438, 438, 452, 453, 454, 455, 438, 438, 456, 457, 
438, 438, 438, 438, 458, 459, 460, 461, 462, 438, 438, 438, 438, 438, 438, 438, 
463, 464};

//background and tiles bitmaps
BITMAP *tiles;
BITMAP *bkg;

//virtual background buffer
BITMAP *scroll;

//character bitmaps
BITMAP *spriteimg1[4];  //toxie
BITMAP *spriteimg2[4];  //cigar
BITMAP *spriteimg3[4];  //knuckles
BITMAP *spriteimg4[4];  //nipples

//mop
BITMAP *spriteimg0;

//position variables
int mx=0, my=100;
int tilex, tiley;

//other game variables
int gameover = 0;
int thugdeaths = 0;

/*******************************************************
* grabframe() func as defined by Harbour               *
* function grabs a specific portion of a bitmap,      *
* denoted by the parameters, and returns that portion  *
********************************************************/
BITMAP *grabframe(BITMAP *source, 
                  int width, int height, 
                  int startx, int starty, 
                  int columns, int frame)
{
    BITMAP *temp = create_bitmap(width,height);

    int x = startx + (frame % columns) * width;
    int y = starty + (frame / columns) * height;

    blit(source,temp,x,y,0,0,width,height);

    return temp;
}

/***********************************************************************
* drawtoxie   (void);                                                  *
* this function draws the appropriate frame of toxic crusader on screen*
************************************************************************/
void drawtoxie()
{
    int a = toxie.x;
    int b = toxie.y;    
    int direc = toxie.dir;
    stayintown();
   
    //draw the sprite based on direction    
    switch (direc){
        case 0:
            masked_blit(spriteimg1[0], scroll, 0, 0, a, b, 64, 64);
            break;
        case 1:
            masked_blit(spriteimg1[1], scroll, 0, 0, a, b, 64, 64);
            break;
        case 2:
            masked_blit(spriteimg1[3], scroll, 0, 0, a, b, 64, 64);
            break;
        case 3:
            masked_blit(spriteimg1[2], scroll, 0, 0, a, b, 64, 64);
            break;
     }     
}

/***********************************************************************
* drawthug  (int);                                                     *
* this function draws the appropriate frame of a thug on screen        *
************************************************************************/
void drawthug(int num)
{
    int a = thug[num].x;
    int b = thug[num].y;
    int direc = thug[num].dir;
   
  //draw the sprite based on direction
  if(num==0){
    if (thug[num].hits > 0){    
      switch (direc){
          case 0:
              masked_blit(spriteimg2[0], scroll, 0, 0, a, b, 64, 64);
              break;
          case 1:
              masked_blit(spriteimg2[1], scroll, 0, 0, a, b, 64, 64);
              break;
          case 2:
              masked_blit(spriteimg2[3], scroll, 0, 0, a, b, 64, 64);
              break;
          case 3:
              masked_blit(spriteimg2[2], scroll, 0, 0, a, b, 64, 64);
              break;
       }//end drawing
      }//end check for hits
  return;
  }//end check thug[0]
 
   if(num==1){
    if (thug[num].hits > 0){    
      switch (direc){
          case 0:
              masked_blit(spriteimg3[0], scroll, 0, 0, a, b, 64, 64);
              break;
          case 1:
              masked_blit(spriteimg3[1], scroll, 0, 0, a, b, 64, 64);
              break;
          case 2:
              masked_blit(spriteimg3[3], scroll, 0, 0, a, b, 64, 64);
              break;
          case 3:
              masked_blit(spriteimg3[2], scroll, 0, 0, a, b, 64, 64);
              break;
       }//end drawing
      }//end check for hits
  return;
  }//end check thug[1]
  
   if(num==2){
    if (thug[num].hits > 0){    
      switch (direc){
          case 0:
              masked_blit(spriteimg4[0], scroll, 0, 0, a, b, 64, 64);
              break;
          case 1:
              masked_blit(spriteimg4[1], scroll, 0, 0, a, b, 64, 64);
              break;
          case 2:
              masked_blit(spriteimg4[3], scroll, 0, 0, a, b, 64, 64);
              break;
          case 3:
              masked_blit(spriteimg4[2], scroll, 0, 0, a, b, 64, 64);
              break;
       }//end drawing
      }//end check for hits
  return;
  }//end check thug[2]        
}

/***********************************************************************
* update mop                                                           *
* this function draws the appropriate frame of toxic mop on screen     *
************************************************************************/
int updatemop()
{
    int x = mop.x;
    int y = mop.y;

    //retrieve location of self
    int selfx = toxie.x;
    int selfy = toxie.y;

    if (mop.alive)
    {
        //move mop
        mop.x += mop.xspd;
        mop.y += mop.yspd;
        x = mop.x;
        y = mop.y;
        
        //draw mop
        x = mop.x;
        y = mop.y;
        masked_blit(spriteimg0, scroll, 0, 0, x, y, 64, 64);
        
        //limit mop throwing distance to 300 - INCORPORATION OF PHYSICS
        if ( ((mop.x > (selfx + 300)) || (mop.x < (selfx - 300))) || ((mop.y > (selfy + 300)) || (mop.y < (selfy - 300))) )
        {
            mop.alive = 0;
        }

        //look for a hit inside ea thug
        int n;
        for(n=0; n<10;n++)
        {
         if( ( (mop.x < (thug[n].x + 64)) && (mop.x > (thug[n].x)) ) && ( (mop.y < (thug[n].y + 64)) && (mop.y > (thug[n].y)) ) )
         {
            if(thug[n].hits > 0){
               mop.alive = 0;
               losehits(n);
            }
         }
        }
    }
}

/***********************************************************************
* throw mop                                                            *
* this function determines direction and velocity of the mop           *
************************************************************************/
void throwmop()
{
    int x = toxie.x;
    int y = toxie.y;

    //ready to throw again?
    if (!mop.alive)
    {
        mop.alive = 1;

        //fire mop in direction toxie is facing
        switch (toxie.dir)
        {
            //north
            case 2:
                mop.x = x;
                mop.y = y-22;
                mop.xspd = 0;
                mop.yspd = -MOPSPEED;
                break;
            //east
            case 1:
                mop.x = x+22;
                mop.y = y;
                mop.xspd = MOPSPEED;
                mop.yspd = 0;
                break;
            //south
            case 0:
                mop.x = x;
                mop.y = y+22;
                mop.xspd = 0;
                mop.yspd = MOPSPEED;
                break;
            //west
            case 3:
                mop.x = x-22;
                mop.y = y;
                mop.xspd = -MOPSPEED;
                mop.yspd = 0;
                break;            
        }
    }
}

/*****************************************************************************
* losehits(int)                                                              *
* this func takes hits away from a thug and determines winning conditions    *
******************************************************************************/
void losehits(int num){
   thug[num].hits--;
   if (thug[num].hits <= 0){
       thugdeaths++;
   }
   if (thugdeaths==3) {
            textprintf(screen, font, (SCREEN_W - 600), (SCREEN_H - 300),
               BURST, "YOU HAVE SAVED TROMAVILLE FROM NUCKLES, NIPPLES, AND CIGAR FACE!");
            rest(4000);
            gameover = 1;
   }
}

/**********************************************************
* gettoxie(int)                                           *
* this function is the "AI engine"                        *
* which drives the "agents" towards toxie if they see him *
***********************************************************/
void gettoxie(int num){
  int thx = thug[num].x;
  int thy = thug[num].y;
  int tox = toxie.x;
  int toy = toxie.y;
  //check to see if toxie is within 200 units of the agent
  if( ( (tox > (thx - 200)) && (tox < (thx + 200)) ) && ( (toy > (thy - 200)) && (toy < (thy+200)) ) )
  {
      if (toy < thy)
          thugforward(num);
      if (toy > thy)
          thugbackward(num);
      if (tox < thx)
          thugleft(num);
      if (tox > thx)
          thugright(num);
      //toxie takes damage when thugs stand on him    
      if ( (toy==thy) && (tox==thx) ) {
          toxie.hits-=1;
          if(toxie.hits == 0)
             owned();
      }
  } else {
     walkaround(num);
  }  
}

/*************************************************************
* walkaround(int)                                            *
* this function causes the "agents" to walk around when      *
* they dont have a toxic avenger in sight                    *
**************************************************************/
void walkaround(int num){
   
   if(thug[num].movementint > 50){
      thugright(num);
      thug[num].movementint++;
      if (thug[num].movementint == 100){
          thug[num].movementint=0;
          return;
       }
   }
   if(thug[num].movementint <= 50){
      thugleft(num);
      thug[num].movementint++;
   }   
}

/*************************************************************
* setupavatars()                                             *
* this gives values to all the variables associated with the *
* different avatar structs                                   *
**************************************************************/
void setupavatars()
{
    //toxie
    toxie.x = 300;
    toxie.y = 400;
    toxie.dir = 0;
    toxie.hits = 20;
    
    //cigarface, thug 0
    thug[0].x = 100;
    thug[0].y = 1000;
    thug[0].dir = 0;
    thug[0].hits = 5;
    thug[0].movementint = 0;
        
    //knuckles, thug 1
    thug[1].x = 600;
    thug[1].y = 700;
    thug[1].dir = 0;
    thug[1].hits = 3;
    thug[1].movementint = 0;
    
    //nipples, thug 2
    thug[2].x = 800;
    thug[2].y = 1000;
    thug[2].dir = 0;
    thug[2].hits = 3;
    thug[2].movementint = 0;
}

/**********************************************************
* stayintown(int)                                         *
* this function keeps the our avatar bound within a box   *
* to maintain the appearance of being inside the town     *
***********************************************************/
void stayintown(){
    int x = toxie.x;
    int y = toxie.y;
            if ( x < 10)
              toxie.x = x+3;
            if ( x > 800)
              toxie.x = x-3;
            if ( y < 300)
              toxie.y = y+3;
            if ( y > 1040)
              toxie.y = y-3;
}

/**********************************************************
* forward                                                 *
* function moves player 3 pixels down on the screen       *
***********************************************************/
void forward(){
    toxie.dir = 2;
    toxie.y = toxie.y - 3;
    
    my -= 3;
    if (my < 0)
        my = 0;
}

/************************************************************
* backward                                                  *
* function moves player 3 pixels upward on the screen       *
*************************************************************/
void backward(){
    toxie.dir = 0;
    toxie.y = toxie.y + 3;
    
    my += 3;
    if (my > scroll->h - HEIGHT)
        my = scroll->h - HEIGHT;
}

/**********************************************************
* turnleft                                                *
* function moves player 3 pixels left on the screen       *
***********************************************************/
void turnleft(){
    toxie.dir = 3;
    toxie.x = toxie.x - 3;
    
    mx -= 3;
    if (mx < 0)
        mx = 0;
}

/************************************************************
* turnright                                                 *
* function moves player 3 pixels right on the screen        *
*************************************************************/
void turnright(){
    toxie.dir = 1;
    toxie.x = toxie.x + 3;
    
    mx += 3;
    if (mx > 500)
        mx = 500;
}

/**********************************************************
* thugforward(int)                                        *
* function moves thug(num) 3 pixels down on the screen    *
***********************************************************/
void thugforward(int num){
    thug[num].dir = 2;
    thug[num].y = thug[num].y - 2;
}

/**********************************************************
* thugbackward(int)                                       *
* function moves thug(num) 3 pixels up on the screen      *
***********************************************************/
void thugbackward(int num){
    thug[num].dir = 0;
    thug[num].y = thug[num].y + 2;
}

/**********************************************************
* thugleft(int)                                           *
* function moves thug(num) 3 pixels left on the screen    *
***********************************************************/
void thugleft(int num){
    thug[num].dir = 3;
    thug[num].x = thug[num].x - 2;
}

/**********************************************************
* thugright(int)                                          *
* function moves thug(num) 3 pixels right on the screen   *
***********************************************************/
void thugright(int num){
    thug[num].dir = 1;
    thug[num].x = thug[num].x + 2;
}

/*******************************************************************
* getinput()                                                       *
* this function checks the key buffer and performs game operations *
* based on the last keystroke                                      *
********************************************************************/
void getinput()
{
    //WASD / SPACE keys control Toxie
    if (key[KEY_W])
        forward();
    if (key[KEY_D])
        turnright();
    if (key[KEY_A])
        turnleft();
    if (key[KEY_S])
        backward();
    if (key[KEY_SPACE])
	    throwmop();
    //C key CENTERS MAP ON TOXIE
    if (key[KEY_C]){
        mx = (toxie.x - 300);
        my = (toxie.y - 300);
        if (mx < 0)
            mx = 0;
    }
        //below allows player to look around map for other thugs
        if (key[KEY_RIGHT])
        {
            mx += STEP;
            if (mx > scroll->w - WIDTH)
                mx = scroll->w - WIDTH;
        }
        if (key[KEY_LEFT])
        {
            mx -= STEP;
            if (mx < 0)
                mx = 0;
        }
        if (key[KEY_DOWN])
        {
            my += STEP;
            if (my > scroll->h - HEIGHT)
                my = scroll->h - HEIGHT;
        }
        if (key[KEY_UP])
        {
            my -= STEP;
            if (my < 0)
                my = 0;
        }
        
        //quit the game
        if (key[KEY_ESC])
            gameover=1;
            
    //short delay after keypress        
    rest(10);
}

/***************************************************
*  owned()                                         *
*    this func is called when toxie dies,          *
*    and promptly ends game with a goodbye message *
****************************************************/
void owned(){
  textprintf(screen, font, (SCREEN_W - 490), (SCREEN_H - 300),
               BURST, "TOXIE JUST GOT OWNED BY THE THUGS! Tromaville is doomed.");
              rest(5000);
  gameover = 1;   
}

//main function
void main(void)
{
    int n;
    //used in frame grabber many lines below
    BITMAP *temp1;
    BITMAP *temp2;
    BITMAP *temp3;
    BITMAP *temp4;
    
    /************************/
    //initialize allegro
    allegro_init();
    install_keyboard();
    install_timer();
    srand(time(NULL));
    set_color_depth(16);
    /***********************/

    //set video mode
    if (set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0) != 0)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message(allegro_error);
        return;
    }
    
    setupavatars();
    
    /******************************************************************/
    //load the bitmaps for the avatars into arrays to grab ea frame
    temp1 = load_bitmap("toxie.bmp", NULL);
    for (n=0; n<4; n++){
        spriteimg1[n] = grabframe(temp1,64,64,0,0,8,n);
    }
    destroy_bitmap(temp1);

    temp2 = load_bitmap("cigarface.bmp", NULL);
    for (n=0; n<4; n++){
        spriteimg2[n] = grabframe(temp2,64,64,0,0,8,n);
    }
    destroy_bitmap(temp2);
    
    temp3 = load_bitmap("knuckles.bmp", NULL);
    for (n=0; n<4; n++){
        spriteimg3[n] = grabframe(temp3,64,64,0,0,8,n);
    }
    destroy_bitmap(temp3);
    
    temp4 = load_bitmap("nipples.bmp", NULL);
    for (n=0; n<4; n++){
        spriteimg4[n] = grabframe(temp4,64,64,0,0,8,n);
    }
    destroy_bitmap(temp4);
    
    //load mop
    spriteimg0 = load_bitmap("mop.bmp",NULL);    
    /******************************************************************/

    /*******************************************************************/
    //create the virtual background
    scroll = create_bitmap(1600, 1200);
    if (scroll == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating virtual background");
        return;
    }

    //load the buffer bitmap 
    bkg = create_bitmap(1600, 1200);
    if (bkg == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating virtual background");
        return;
    }
    
    //load the tile bitmap 
    tiles = load_bitmap("tromaville.bmp", NULL);
    if (bkg == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading tromaville.bmp file");
        return;
    }

    //now draw tiles on virtual background
    for (tiley=0; tiley < scroll->h; tiley+=TILEH)
    {
        for (tilex=0; tilex < scroll->w; tilex+=TILEW)
        {
            //use the result of grabframe directly in blitter
            blit(grabframe(tiles, TILEW, TILEH, 0, 0, COLS, map[n++]), 
                bkg, 0, 0, tilex, tiley, TILEW, TILEH);
        }
    }
    /*******************************************************************/

    textprintf(screen, font, (SCREEN_W - 600), (SCREEN_H - 300),
               BURST, "Save Tromaville by 'cleaning up' Knuckles, Nipples, and Cigar Face");
    rest(4000);
    
    //main loop
    while (!gameover)
    {    
     blit(bkg, scroll, 0, 0, 0, 0, 1599, 1199);
        
     if (keypressed())
            getinput();
            
     drawtoxie();
     //walkaround(0); 
     //walkaround(1);   //used in debugging
     //walkaround(2);
     gettoxie(0);
     gettoxie(1);
     gettoxie(2);
     drawthug(0);
     drawthug(1);
     drawthug(2);
     updatemop();
     
        //display hitpoints and how many thugs are alive
        textprintf(scroll, font, (toxie.x-32), (toxie.y - 300), BURST,
        "Toxie's Life: %d", toxie.hits);
        textprintf(scroll, font, (toxie.x-32), (toxie.y - 290), BURST,
        "thugs killed out of %d: %d", 3, thugdeaths);
    
        //draw the scroll window portion of the virtual buffer
        blit(scroll, screen, mx, my, 0, 0, WIDTH-1, HEIGHT-1);

        //"slow" it down
        rest(20);
    }//end main loop
    
    for (n=0; n<20; n++){
          textprintf(screen, font, (SCREEN_W - 280), ((n * 10)+ (SCREEN_H - 350)) ,
          BURST, "THANKS FOR PLAYING!!!");
          rest(100);
     }
     
    destroy_bitmap(scroll);
    destroy_bitmap(bkg);
    return;
}

END_OF_MAIN();

