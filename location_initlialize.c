//when sw1 is pressed initialize the current coordinates with the starting position
void location_initlialize(){
    float dummyLat;
    int integer;
    int floatpart;
    dummyLat=atof(protocolValues[2]);
    integer=dummyLat/100;
    floatpart=dummyLat-(float)integer*100;
    floatpart=floatpart/60;
    currentLatitude=(float)integer+floatpart;

    float dummyLong;;
    dummyLong=atof(protocolValues[4]);
    integer=dummyLong/100;
    floatpart=dummyLong-(float)integer*100;
    floatpart=floatpart/60;
    currentLongitude=(float)integer+floatpart;

}