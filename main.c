#include<stdio.h>
#include<math.h>

#define RATED_PWR 2300000.0
#define HALF_OF_RATED_PWR RATED_PWR / 2.0

static void sinSig( void )
{
   //use V_AdvPowerSP instead of V_MTC_ActivePowerRef
   //todo simulate V_MTC_ActivePowerRef so it is changed every 20ms by
   //sin function;

   float powerRef;
   static float time;

   FILE *fileDesc;

   int P_Cnv_ActivePwrMin = 0;
   int short P_Cnv_ActivePwrRelativeMax = 10000;
   int short P_Cnv_ActivePwrRelativeMin = 0;
   int P_Cnv_ActivePwrMax = 2760000;

   int short powerRefPrcnt = 0;

   // Open a file in writing mode
   fileDesc = fopen("sinSig.csv", "w");

   // Write some text to the file


   // Close the file
   fprintf(fileDesc, "power,time,powerInt,powerPercentage\n");

   while(4.0 > time )
   {
      powerRef =
         (HALF_OF_RATED_PWR * sin(2.0 * M_PI * 0.5 * time)) + HALF_OF_RATED_PWR;
      time += 0.02;
      int powerRefInt = (int)powerRef;
//      printf("power %f, time %f\n\r", powerRef, time);

      powerRefPrcnt = (int short) ((long long)(powerRefInt - P_Cnv_ActivePwrMin)
      * ((long long)P_Cnv_ActivePwrRelativeMax - P_Cnv_ActivePwrRelativeMin)
      / (long long)(P_Cnv_ActivePwrMax - P_Cnv_ActivePwrMin) +
                                                   P_Cnv_ActivePwrRelativeMin);

      fprintf(fileDesc, "%f,%f,%i,%i\n", powerRef, time, powerRefInt, powerRefPrcnt);
   }

//   while(0.04 > time )
//   {
//      powerRef = 1 * sin(2.0 * M_PI * 50.0 * time);
//      time += 0.001;
//   //      printf("power %f, time %f\n\r", powerRef, time);
//      fprintf(fileDesc, "%f,%f\n", powerRef, time);
//   }

   fclose(fileDesc);

}
int main(void)
{
   sinSig();
}
