

void parse(){
    int i,;
    for(i=0;array_Data[i]!='\0';i++){

        int counter=i;
        if(array_Date[i][counter]=='$'){
            counter++;
            if(array_Date[i][counter]=='G'){
                counter++;

                if(array_Date[i][counter]=='P'){
                    counter++;

                    if(array_Date[i][counter]=='R'){
                        counter++;

                        if(array_Date[i][counter]=='M'){
                            counter++;
                            if(array_Date[i][counter]=='C'){
                                counter+=2;
                                int index = 0;
                                char *token=strtok(array_Data[i],comma);
                                while( token != NULL ) {
                                    strcpy(protocolValues[index], token);
                                    token = strtok(NULL,comma);
                                    index++;
                               }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
