#ifndef Recipe_h
#define Recipe_h

#include "Arduino.h"

class Recipe
{
public:
  Recipe(int preMashTemp=0, int mashTemp=0, int boilTime=60, int mashTime=60);
  void hopAdditions(int a=0, int b=0, int c=0, int d=0, int e=0, int f=0, int g=0, int h=0, int i=0, int j=0);
  int numHopAdditions;
  ~Recipe(void);
  

private:
  // Mash variables
  const int PRE_MASH_TEMP_F;
  const int MASH_TEMP_F;
  const int MASH_TIME_MIN;

  // boiling and hop additions
  const int BOIL_TIME_MIN;
  
  int hopAdditions_minsLeftInBoil[10] = {0};
};

#endif  // Recipe_h
