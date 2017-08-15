#include "Arduino.h"
#include "Recipe.h"

// TODO: Optimize ints to bytes to save memory.


// Create Recipe object with necessary brewing parameters.
Recipe::Recipe(int preMashTemp, int mashTemp, int mashTime, int boilTime) :
  PRE_MASH_TEMP_F(preMashTemp),
  MASH_TEMP_F(mashTemp),
  MASH_TIME_MIN(mashTime),
  BOIL_TIME_MIN(boilTime)
{}

// Fill a recipe's hop additions array with provided hop additions, with each hop addition
// being the time remaining in the boil
void Recipe::hopAdditions(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
  // TODO: Sort hop additions from largest to smallest to prevent out of sync additions.
  
  hopAdditions_minsLeftInBoil[0] = a;
  hopAdditions_minsLeftInBoil[1] = b;
  hopAdditions_minsLeftInBoil[2] = c;
  hopAdditions_minsLeftInBoil[3] = d;
  hopAdditions_minsLeftInBoil[4] = e;
  hopAdditions_minsLeftInBoil[5] = f;
  hopAdditions_minsLeftInBoil[6] = g;
  hopAdditions_minsLeftInBoil[7] = h;
  hopAdditions_minsLeftInBoil[8] = i;
  hopAdditions_minsLeftInBoil[9] = j;

  int count = 0;
  for (int i; i < (sizeof(hopAdditions_minsLeftInBoil)/2); i++)
  {
    if (hopAdditions_minsLeftInBoil[i] != 0)
    {
      count++;  
    }
  }

  numHopAdditions = count;
}  

Recipe::~Recipe(void){}
