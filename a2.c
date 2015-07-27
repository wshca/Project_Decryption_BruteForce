#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// assignment 2 - question 5
// user has to call the function with first argument is the
// input file name with the cipher text to decrypt
// output file name with the first good guess of the decoded message

char compare(int frequency, int charnumber)
{
    double calcfrequency;
    //printf("freq: %d char: %d ",frequency,charnumber);
    char tempchar;
    calcfrequency = 100 * (double)frequency/ (double)charnumber;//note that the comparing values are in %
    //printf("calcfrequency %f \n",calcfrequency);
    if (calcfrequency < 0.085){
        tempchar = 'Z';
    }else if (calcfrequency >= 0.085 && calcfrequency < 0.105){
        tempchar = 'J';
    }else if (calcfrequency >= 0.105 && calcfrequency < 0.14){
        tempchar = 'Q';
    }else if (calcfrequency >= 0.14 && calcfrequency < 0.43){
        tempchar = 'X';
    }else if (calcfrequency >= 0.43 && calcfrequency < 0.9){
        tempchar = 'K';
    }else if (calcfrequency >= 0.9 && calcfrequency < 1.3){
        tempchar = 'V';
    }else if (calcfrequency >= 1.3 && calcfrequency < 1.655){
        tempchar = 'B';
    }else if (calcfrequency >= 1.655 && calcfrequency < 1.925){
        tempchar = 'P';
    }else if (calcfrequency >= 1.925 && calcfrequency < 2.06){
        tempchar = 'G';
    }else if (calcfrequency >= 2.06 && calcfrequency < 2.1){
        tempchar = 'W';
    }else if (calcfrequency >= 2.1 && calcfrequency < 2.205){
        tempchar = 'Y';
    }else if (calcfrequency >= 2.205 && calcfrequency < 2.455){
        tempchar = 'F';
    }else if (calcfrequency >= 2.455 && calcfrequency < 2.66){
        tempchar = 'M';
    }else if (calcfrequency >= 2.66 && calcfrequency < 2.795){
        tempchar = 'C';
    }else if (calcfrequency >= 2.795 && calcfrequency < 3.43){
        tempchar = 'U';
    }else if (calcfrequency >= 3.43 && calcfrequency < 4.15){
        tempchar = 'L';
    }else if (calcfrequency >= 4.15 && calcfrequency < 5.12){
        tempchar = 'D';
    }else if (calcfrequency >= 5.12 && calcfrequency < 5.97){
        tempchar = 'H';
    }else if (calcfrequency >= 5.97 && calcfrequency < 6.15){
        tempchar = 'R';
    }else if (calcfrequency >= 6.15 && calcfrequency < 6.615){
        tempchar = 'S';
    }else if (calcfrequency >= 6.615 && calcfrequency < 7.13){
        tempchar = 'N';
    }else if (calcfrequency >= 7.13 && calcfrequency < 7.495){
        tempchar = 'I';
    }else if (calcfrequency >= 7.495 && calcfrequency < 7.9){
        tempchar = 'O';
    }else if (calcfrequency >= 7.9 && calcfrequency < 8.61){
        tempchar = 'A';
    }else if (calcfrequency >= 8.61 && calcfrequency < 10.56){
        tempchar = 'T';
    }else{
        tempchar = 'E';
    };//end all if calls

    return tempchar;//return the new char
}//end of the compare subroutine


int main ( int argc, char *argv[] )
{
    // variables to build the actual string
    char output[1];        //temporary store the char while readin
    int castoutput;
    char output2[1];
    int intstorage[400]; //store the charactor of the cipher text
    int charfrequncy[400]; //store the frequncy of the char
    char charoutput[400];  //store the highest possible output char for the input char
    int numberofchar=0;
    int i,j,k;
    int found;
    int index=1;

    // cipher text file
    FILE *cipherchar = fopen( argv[1], "r" );
    // output to write keyword - here only creating new file
    FILE *fileOutCreate = fopen( argv[2], "w" );//just for clean purpose
    fclose( fileOutCreate ); //close it immeditately
    //reset the values of char storage to nothing to avoid problems with memory
    i = 0;
    while (i<400)
    {
        intstorage[i]=0;
        charfrequncy[i]=0;
        charoutput[i]='\0';
        i++;
    }//end while to reset the char storage

  index=0;//index variable to count how many chars we have in this message

  while((output[0] = fgetc(cipherchar)) != EOF)//start while to go throught the input file and store the char and frequeny in the variables
   {
      index++;//incremement to get the number of chars in the message
      // strip trailing '\n' if it exists
      int len = strlen(output)-1;
      if(output[len] == '\n')
         output[len] = 0;

      castoutput = (int) output[0];//cast the char to integer to avoid problems
      // section of storing char and occurence in variables

   //now have a char to test - converted it into int
   found=0;
   for(i=0;i<400;i++)
   {
       //compare char with all available variables in the array
       if(castoutput==intstorage[i]){
         charfrequncy[i]++;//if we have one we already have in the table we just increment the freqeuncy count
         found=1;//found the char in the table
       }
   }
   //after we checked all available chars in the table
   if (found == 0)//so we could not find it in the list, so we have to add it to the list
   {
       i=0;//reset index
       while(i<400)//while loop to make sure we don't have segmentation fault (if we would use loop with stop after finding 0
       {
           if(intstorage[i]==0)//search for the next available spot in the list which is empty (0)
           {
               intstorage[i]=castoutput;//store the new char in the list
               charfrequncy[i]=1;
               i=400;//after we have found one empty spot, we stored it, now jump out of loop
           }//end if
           i++;//go forward in the list until we found an empty spot
       }//end while
   }//end if found ==0

   }//end while cipher char file go through

   //call routine to compare character
   printf("char replacement is (guessed):\n");
   i=0;//reset i
   while (i<400)//go through the storage of char
   {
       if (intstorage[i] != 0)//only do check if variable is acutally set
       {
       if (charfrequncy[i] != 0){
           charoutput[i] = compare(charfrequncy[i],index);
           printf("<%d - freq %d =>%c> \n",i,charfrequncy[i],charoutput[i]);
       }//end if
       }//end if checking that charstorage has real value and not random number
       i++;//increment i
   }//end of while going through the char storage

   // convert cipher text into readable message
   //read in file char by char
   fclose( cipherchar );   //clean up - so we can open it again
   FILE *cipherchar2 = fopen( argv[1], "r" );//open file to read the char and compare it and replace it with the decoded one
   FILE *fileOut = fopen( argv[2], "a" );  //open file to append
  while((output2[0] = fgetc(cipherchar2)) != EOF)
  {
      // strip trailing '\n' if it exists
      int len = strlen(output2)-1;
      if(output2[len] == '\n')
         output2[len] = 0;

      i=0;//reset to 0
      while (i<400)//go through the char storage
      {
        if ((int)output2[0] == intstorage[i] && intstorage[i] != 0){//test for the char in the vector
        //fprintf(fileOut, "%c", charoutput[i]);        //write out the new char
        fputc(charoutput[i],fileOut);
        printf("%c",charoutput[i]);
        i=400;//jump out of loop after we found the matching char
        }//end of if
        i++;
      }//end if of char comparison and replacmen

      }//end while to check if char is already in table

      fclose( fileOut );
      fclose( cipherchar2 );
printf("\n");
}//end of the main routine



