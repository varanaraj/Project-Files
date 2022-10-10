#include<stdio.h>    
#include<string.h> 
#include<stdlib.h>

//declare the variables/////////////////////////////////////////////////////////////////
int qr[38][38];	//to take maximum array value
char qrc[10000];
int number,r1,r2,r3,c3,c2,c1,n3,n2,n4,n5,n6,n7,n8,n9,simr,simc,n,i,j,k;
int addtoarray(int number,int r1,int c1);

//creating function to put a number to array with binary order//////////////////////////////////
//r1 and c1 are the left top element's location of 3x3 boxes
int addtoarray(int number,int r1,int c1){
for(n3=2;n3>=0;n3--){
	for(n2=2;n2>=0;n2--){
		qr[r1+n3][c1+n2]=number%2;
		number=number/2;
	    }
	}
}

//starting main function////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
	
//making all the charector of the argument colors are small/////////////////////////////////////////
if(argc==3){ 
    int l1;
   	for(l1=0;l1<strlen(argv[2]);l1++){
   		if(argv[2][l1]<92){
   		   argv[2][l1]=argv[2][l1]+32;
			}
	   }
    } 
    

//filtering only suitable inputs for showing qr code/////////////////////////////////////////

if((argc==1)||((argc==3)&&(strcmp(argv[1],"-c")==0)&&((strcmp(argv[2],"black")==0)||(strcmp(argv[2],"red")==0)||(strcmp(argv[2],"green")==0)||(strcmp(argv[2],"magenta")==0)||(strcmp(argv[2],"cyan")==0)||(strcmp(argv[2],"blue")==0)||(strcmp(argv[2],"yellow")==0)))){

/////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("Enter the URL: ");
	
//declare variables//////////////////////////////////////////////////////////////////////////
	
	char in[135];
	int col,row,counter2=0,counter1=-1,counter3=0,ch,sidelen;
	
	
	scanf("%s",in);          //get the url from the user
	
	n=strlen(in);			//find the length
	
//to determine the correct scale of the qr code//////////////////////////////////////////////

	if(n>3&&n<120){
		system("clear");
		if(n<=20){
		ch=24;		//charector for <20 letters URL
		sidelen=20;
			
			}else{
				ch=132;		//charector for >20 letters URL
				sidelen=38;
				}
	
//assign the first charector /////////////////////////////////////////////////////////////////
		char ou[ch],ou2[ch],ou1[ch];
		
		ou[0]=50+n;	
		
//string hashing and order the charectors(24or132)/////////////////////////////////////////////
		
		for(i=1;i<ch;i++){
		
			if((i-1)%n==0){
				counter1++;
			}else{
				counter1=counter1;
			}
			ou[i]=in[i-1-(counter1*n)]+counter1;
			}	
			
//reversing entire part after the current order/////////////////////////////////////////////////
		for(j=0;j<=(ch-1);j++){
			if(j<=n){
			ou1[j]=ou[j];
			}else{
			ou1[j]=ou[ch-j+n];
			}
			}
	
//making all of the array charectors to be zero///////////////////////////////////////////////////
	
		for(n4=0;n4<=sidelen-1;n4++){
			for(n5=0;n5<=sidelen-1;n5++){
				qr[n4][n5]=0;
				}
			}
	
//building posistion squares///////////////////////////////////////////////////////////////////
		int p1,p2;
		for(p1=0;p1<2;p1++){
			for(p2=0;p2<2;p2++){
				if(p1==0||p2==0){
					addtoarray(485,1+p1*(sidelen-8),1+p2*(sidelen-8));
					addtoarray(461,1+p1*(sidelen-8),4+p2*(sidelen-8));
					addtoarray(359,4+p1*(sidelen-8),1+p2*(sidelen-8));
					addtoarray(335,4+p1*(sidelen-8),4+p2*(sidelen-8));
					}
				}
			}
		
//assigning major square part(part which is covered by position squares' corners//////////////
		for(r2=0;r2<(sidelen-8)/3;r2++){
			for(c2=0;c2<(sidelen-8)/3;c2++){
				
				addtoarray(ou1[counter2],(7+(3*r2)),(7+(3*c2)));
				counter2++;
				}
			}
		
//assigning the part which is in between the posion squares////////////////////////////////////////////
		int counter4=((sidelen-8)/3)*((sidelen-8)/3);
		
		for(n9=0;n9<2;n9++){
			for(r3=0;r3<2+(n9*(((sidelen-14)/3)-2));r3++){
				for(c3=0;c3<((sidelen-14)/3)-(n9*(((sidelen-14)/3)-2));c3++){
					addtoarray(ou1[counter4],(1+(3*r3)+(6*n9)),(7+(3*c3)-(6*n9)));
					counter4++;
					}
				}
			}
					
//printing with color part/////////////////////////////////////////////////////////////////////////////
		counter3=0;
		//black and white part
		if(argc==1){
			for(simr=0;simr<sidelen;simr++){
				for(simc=0;simc<sidelen;simc++){
					if(qr[simr][simc]==0){
						printf("\x1b[47m  "); 			
					}else{
						printf("\x1b[40m  ");
						}
					counter3++;
					}
		   		printf("\x1b[0m");
				printf("\n");
				}
				
		//color part	
		}else{
			for(simr=0;simr<sidelen;simr++){
				for(simc=0;simc<sidelen;simc++){
					if(qr[simr][simc]==0){
						printf("\x1b[47m  ");
					}else{
						if(strcmp(argv[2],"black")==0){
							printf("\x1b[40m  ");
					}else{
						if(strcmp(argv[2],"red")==0){
							printf("\x1b[41m  ");
					}else{
						if(strcmp(argv[2],"green")==0){
							printf("\x1b[42m  ");
					}else{
						if(strcmp(argv[2],"blue")==0){
							printf("\x1b[44m  ");
					}else{
						if(strcmp(argv[2],"cyan")==0){
							printf("\x1b[46m  ");
					}else{
						if(strcmp(argv[2],"yellow")==0){
							printf("\x1b[43m  ");
					}else{
						if(strcmp(argv[2],"magenta")==0){
							printf("\x1b[45m  ");
						}
					}
					}
					}
					}
					}
					}
					}
				counter3++;
				}
		    printf("\x1b[0m");	
			printf("\n");
			}
		}
	}else{
		if(n<=3){
			printf("String is too short. Not supported by available QR versions \n");
		}else{
			printf("String is too long. Not supported by available QR versions \n");
		}
	}
}else{
	
//declare error messages/////////////////////////////////////////////////////////////////////
	char em1[50]="Incorrect usage of arguments.\n";
	char em2[50]="Invalid argument for color.\n";
	char cm1[50]="usage :\n";
	char cm2[50]="-c [black|red|green|yellow|blue|magenta|cyan]\n";
	char cm3[50]="-h for the help about the program\n";
	
	if((argc==3)&&(strcmp(argv[1],"-c")==0)){
		printf("%s",em2);						//print the specific error message
	}else{
	     if((argc!=2)||(strcmp(argv[1],"-h")!=0)){
			printf("%s",em1);					//print the specific error message
			}
	}
	printf("%s%s %s%s %s",cm1,argv[0],cm2,argv[0],cm3);	//print the common message
}
return 0;
}


