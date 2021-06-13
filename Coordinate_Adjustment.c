     //function to take values from parsed string and do math ops on them and them place them in the next coordinates
float Coordinate_Adjustment(int index){
    float dummyCo;
    int integer;
    int floatpart;
    dummyCo=atof(protocolValues[index]);
    integer=dummyCo/100;
    floatpart=dummyCo-(float)integer*100;
    floatpart=floatpart/60;
    return (float)integer+floatpart;
}