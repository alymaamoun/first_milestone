#include "ConfigMain.c"
double currentLongitude=31.2790314;
double currentAltitude=0;
double currentLatitude=30.0657458;
double distanceCovered;
double previousLong;
double previousAlti;
double previousLati;
double earthRadius=6371000.0;


void addDistance(double newLatitude,double newLongitude,double newAltitude){
  /*since we will calculate distance with harvesine method we will need all co-ordinates to be in radian
    so in code we will initialize current co-ordinates multiplied by pi/180
    and pass the parameteres to the function multiplied by pi/180*/

    //calculate the change between new co-ordinates and old current co-ordinates
    double deltaLongitude=newLongitude-currentLongitude;
    double deltaAltitude=newAltitude-currentAltitude;
    double deltaLatitude=newLatitude-currentLatitude;

    //using the haversine method to calculate distance b/w two points on earth

    double a= powf(sin((deltaLatitude/2)*(3.1415926536 / 180)),2)+cos(currentLatitude*3.1415926536 / 180)*cos(newLatitude*(3.1415926536 / 180))*pow(sin((deltaLongitude/2)*(3.1415926536 / 180)),2);

    double b=2*asin(sqrt(a));

     distanceCovered=distanceCovered+b*earthRadius;

    //set the current co-ordinates to the new co-ordinates
    currentLongitude = newLongitude;
    currentAltitude=newAltitude;
    currentLatitude=newLatitude;

}