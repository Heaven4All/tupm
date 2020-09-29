/* TUP Monitoring Exec : Can execute a command returning a service status (http://www.uptimeprj.com)
 * OpenSOURCE / GPL / Sebastien TUGS (uptimeprj@nextworlds.com)
 *
 * TUP Linux Client and all program are released on GPL :
 * --------------------------------------------
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


/*****************************************
* Print Usage			   	 *
* Info : Give information about switch	 *
*****************************************/
void PrintUsage(int argc, char *argv[]) {
    if (argc >=1) {
        printf("\nUsage: %s -h|help -g\n", argv[0]);
        printf("  Options:\n");
        printf("      -g : Execute monitoring command.\n");
        printf("      -h or -help : Show this help screen.\n");
        printf("\n");
    }

}


void DoLowercase(char string[])
{
   int  i = 0;

   while ( string[i] )
   {
      string[i] = tolower(string[i]);
      i++;
   }

   return;
}

int DoGrep(char *strorig, char *strsearch) {

char *ptr;
ptr = strstr(strorig, strsearch);

if( ptr == NULL ) { 
	return 0;
} else {
	return 1;
}

// end DoGrep

}

 


/*****************************************
* Do Monitor			   	 *
* Info : Execute service testing command *
*****************************************/
void DoMonitor(char *tupmcommand, char *tupccommand, char *tupsservice) {

   FILE *fpipe;
   char line[256];
   char tocompare[256];
   int iKoService = 1;

   strcpy(tocompare,tupccommand);

 if ( !(fpipe = (FILE*)popen(tupmcommand,"r")) )
		   {  // If fpipe is NULL
		      perror("Problems with pipe");
		      exit(1);
		   }

		   while ( fgets( line, sizeof line, fpipe))
		   {
		     //printf("%s", line);

		     DoLowercase(line);
		     DoLowercase(tocompare);

		     if( DoGrep(line,tocompare) ) {
				printf("OK");
				iKoService = 0;
			} 				
		   }

		   if ( iKoService ) { 
		   	printf("KO");
	           }
		   pclose(fpipe);
}


/****************************************************************
* Main				   	 			*
*****************************************************************/
int main(int argc, char *argv[])
{
   
   int c;
   int domonitor = 0;
   static char *optforZ,*optforG,*optforS;
   extern char *optarg;

	while( (c = getopt(argc, argv, "g:s:z:h|help")) != -1) {

	switch(c){
	    case 'g':
		domonitor = 1;
		optforG = optarg;
		break;
	    case 'z':
		optforZ = optarg;
		break;
	    case 's':
		optforS = optarg;
		break;
	    case 'h':
		PrintUsage(argc, argv);
		exit(0);
		break;
	    default:
		PrintUsage(argc, argv);
		exit(0);
		break;
		} // end switch

	}  // end while


	if(domonitor) {
		
		DoMonitor(optforG,optforZ,optforS);
	}

	return 0;

}


