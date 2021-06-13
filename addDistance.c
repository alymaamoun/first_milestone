void addDistance(){

    newLatitude=Coordinate_Adjustment(2);
    newLongitude=Coordinate_Adjustment(4);
    float deltaLongitude=newLongitude-currentLongitude;
    //float deltaAltitude=newAltitude-currentAltitude;
    float deltaLatitude=newLatitude-currentLatitude;

    //using the haversine method to calculate distance b/w two points on earth

    float a= powf(sin(deltaLatitude*degToRadian/2),2)+cos(currentLatitude*degToRadian)*cos(newLatitude*degToRadian)*pow(sin(deltaLongitude*degToRadian/2),2);

    float b=2*atan2(sqrt(a),sqrt(1-a));

    distancePath=distancePath+b*earthRadius;



    //set the current co-ordinates to the new co-ordinates
    currentLongitude = newLongitude;
    //currentAltitude=newAltitude;
    currentLatitude=newLatitude;

}
