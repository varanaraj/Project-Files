///////////////////////////////////////////////////
///		E/17/358 CO222 PROJECT-02				///
///////////////////////////////////////////////////

//HEADER FILES
#include <stdio.h> 
#include<string.h>
#include<stdlib.h>

//STRUCTURE FOR STORE EVERY CHARECTORS
typedef struct _c{
	char Char;
	int Amount;
	int order;
}chars;

//STRUCTURE FOR STORE EVERY CHARECTORS
typedef struct _w {
	char* WORD;
	int amount1;
	int order1;
	struct _w*next;
}word_d;

//DECLARATION OF FUNCTIONS
int forlett();
int forword();
int boxnum();
void addword();
float persentage();
int mergefile();
int rmrtn();

//FOR DELETE CREATED FILES AND RETURN
int rmrtn(){
	remove("@][IDENTICAL1][@.txt");
    remove("@][IDENTICAL2][@.txt");
    
}
//FUNCTION TO MERGE THE INPUT FILES
int mergefile(char*mfname,char*sfname){
	
	FILE* fpm=fopen(mfname,"r");			//open main file
	FILE* fps=fopen(sfname,"r");			//open subfile
	FILE* fpt=fopen("@][IDENTICAL2][@.txt","a");		//open temperory file to store 
	if(fps==NULL){
	return 0;
		
	}
	char Ch,Ch2;
	while ((Ch = fgetc(fpm)) != EOF){
		
		fputc(Ch, fpt); 					//adding charectors to the temporary files
	}
	while ((Ch2 = fgetc(fps)) != EOF){
		fputc(Ch2, fpt); 					//adding charectors to the temporary files
	}
	//close the files
	fclose(fpt);
	fclose(fpm);
	
}			//end mergefile function

//FUNCTION TO CALCULATE BOXES IN GRAPH
int boxnum(double select,double max,int space,int s,int Total){
	static int Boxnum;												//to return the number of boxes
	double tempb;			
	if(s==0){
		tempb=(select/max)*(double)space;							//calculate the decimal value of boxes in scaled position
	}else{
		tempb=(select/(double)Total)*(double)space;					//calculate the decimal value of boxes in not scaled position
	}
	Boxnum=(int)tempb;												//change the decimal value to int
	return Boxnum;
}

///FUNCTION TO ACCESS THE WORDS AND PLOT THE GRAPH
int forword(char* finfile,int NUMOFLINES,int scalevar){
	//TO STORE DATAS USING LINKED LIST
	word_d*head;
	head=(word_d*)malloc(sizeof(word_d));
	head->next=NULL;
    FILE* fp; 
  	fp = fopen(finfile, "r");   //open the file in read mode to read only
  	char count12; 
	int n=0;
	//COUNTING HOW MANY CHARECTORS THERE
    while ((count12= fgetc(fp)) != EOF){
    	if((count12>=48&&count12<=57)||(count12>=65&&count12<=90)
		||(count12<=122&&count12>=97)||count12==' '||count12=='\n'){
   		n++;
   		}
    }
    fclose(fp); //CLOSE THE FILE
    //TO CREATE A ARRAY TO STORE ALL ALLOWED CHARECTORS 
    
	char count11;
    char content[n-1];
    
    //OPEN AGAIN THE SAME FILE
    FILE* fp1; 
    fp1 = fopen(finfile, "r"); 
    int m=0;
    while ((count11 = fgetc(fp1)) != EOF){
   		if(count11<=90&&count11>=65){
  			count11=count11+32;
		}
		
		//CHANGE ALL NEXT LINE CHARCTORS TO SPACE CHARECTOR	AND STORE IN ARRAY  
		if((count11>=48&&count11<=57)||(count11<=122&&count11>=97)||count11==' '||count11=='\n'){
			if(count11=='\n'){
		    count11=' ';
	        } 
			content[m]=count11;
   			m++;	//m= TOTAL CHARECTRS
		}
	}	
    fclose(fp1); 	//CLOSE THE FILE
   
    int ercor;


	
	for(ercor=n;ercor<strlen(content);ercor++){
		
		content[ercor]=' ';
	}

	char* word;
	//INITIALIZING TOTAL WORDS AND WHAT ORDER THEY ARE IN THE FILE
	static int totalwords=0;		
	int ORDER=0;
	
	//SPLITING THE WORDS BY SPACE
	word=strtok(content," ");
	
    while( word != NULL){
		addword(head,word,ORDER);	//ADDING THE WORD TO THE LINKED LIST 
      	ORDER++;					//ORDERING THE WORD
        word=strtok(NULL," ");
        totalwords++;				//TO COUNT THE TOTAL WORDS
    }
    if(m==0){
    totalwords--;
}
    word_d*temp1;
    word_d*temp2;
    word_d*temp3;
    
    //RE ARRANGE THE WORDS ACCORDING TO THE AMOUNT OF OCCURENCE
    //USING SWAP METHOD
    for(temp1=head->next;temp1!=NULL;temp1=temp1->next){
    	for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next){
    		if(temp1->amount1<temp2->amount1){
    			char*tempword=temp1->WORD;
    			temp1->WORD=temp2->WORD;
    			temp2->WORD=tempword;
    			int tempamount=temp1->amount1;
    			temp1->amount1=temp2->amount1;
    			temp2->amount1=tempamount;
    			int temporder=temp1->order1;
    			temp1->order1=temp2->order1;
    			temp2->order1=temporder;
    			
			}
			
		}
	}
	
	/////RE ARRANGE THE WORDS ACCORDING TO THE ORDER WHEN THEY ARE IN SAME COUNTS
	//USING SWAP METHOD	
    for(temp1=head->next;temp1!=NULL;temp1=temp1->next){
    	for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next){
    		if(persentage(temp1->amount1,totalwords)==persentage(temp2->amount1,totalwords)){
				if(temp1->order1>temp2->order1){
    			char*tempword=temp1->WORD;
    			temp1->WORD=temp2->WORD;
    			temp2->WORD=tempword;
    			int tempamount=temp1->amount1;
    			temp1->amount1=temp2->amount1;
    			temp2->amount1=tempamount;
    			int temporder=temp1->order1;
    			temp1->order1=temp2->order1;
    			temp2->order1=temporder;
    			}
			}
   		}
	}
    
    word_d*start;		
    int linenumbers;	
    
    linenumbers=NUMOFLINES;		
    
    //IF THE INPUT NUMBER OF WORDS GREATER THAN THE TOTAL WORDS
    if(linenumbers>totalwords){
    	linenumbers=totalwords;
	}
	
    int count13=0,count14=0,count15;
    int wordlong=0;
    
    
    //To find the maximum length of a word
    for(start=head->next;count13<linenumbers;start=start->next){
    	count13++;
		if(strlen(start->WORD)>wordlong){         
			wordlong=strlen(start->WORD);
		}
    }
            
    //GRAPH PLOTTING PART  
    for(start=head->next;count14<linenumbers;start=start->next){
    	count14++;
    	for(count15=1;count15<5;count15++){
    		printf("\n");		//THAT CAP
    		int count16;	
    		if(count15!=2){			//EXCEPT THE MIDDLE ROW WE DON'T NEED TO PRINT ANY EXTRA CHARECTORS
    			for(count16=0;count16<=wordlong+1;count16++){
    				printf(" ");
				}
				printf("\u2502");
			
    		}else{
    			///FOR MIDDLE LINE OF EVERY ROWS
    			printf(" %s ",start->WORD);
    			for(count16=0;count16<(wordlong-strlen(start->WORD));count16++){
    				printf(" ");
				}
				printf("\u2502");
			}
    		if(count15!=4){		//IN 4TH ROW WE DON'T NEED TO PUT GRAPH
    			int count17;
    			//PRINTING THE GRAPH FOR THE SUITABLE LENGTH
    			for(count17=0;count17<boxnum((double)start->amount1,(double)head->next->amount1,75-(wordlong+3),scalevar,totalwords);count17++){
    				printf("\u2591");
				}
				
			}
			
			//IN THE SECOND ROWS WE NEED TO PUT THE PERSENTAGE VALUE
			if(count15==2){
				printf("%.2f",persentage(start->amount1,totalwords));
				printf("%%");
			}
		}
	}
	//EXCEPT THE 0 LINES NEED CASES
	//PRINT THE X AXIS
    if(linenumbers>0){
	   	printf("\n");
	    int count19;
	    for(count19=0;count19<wordlong+2;count19++){
	       printf(" ");
	    }
		printf("\u2514");
		int count18;
		
		for(count18=0;count18<(80-(wordlong+3));count18++){
			printf("\u2500");	
		}
		printf("\n");
	}else{		//WHEN THERE ARE NO ANY WORDS AVAILABLE
		printf("No data to process\n");
		rmrtn();
		return 0;
	}
	
	
}		//END OF FORWORD FUNCTION

///FUNCTION TO ACCESS THE CHARECTORS AND PLOT THE GRAPH
int forlett(char* finfile,int NUMOFLINES,int scalevar){
	chars charlist[40];		//TO STORE MAXIMUM OF 26 LET + 10 NUM SO IT TOOK 40
    FILE* fp; 				
    char c; 
  	char*filename;
	filename=finfile; 
    fp = fopen(filename, "r"); 		//OPEN THE MERGED FILE IN READ MODE
    int count = 0; 
    int let=0;
    int o;
    //TO GET EVERY CHARECTORS IN A LOOP
    while ((c = fgetc(fp)) != EOF){
  		if(c<=90&&c>=65){		//FOR MAKE CAPITAL LETTERS AS SMALL
  			c=c+32;
		}
			  
		int check=0;
		//ADD TO STRUCTURE LIST
		if((c>=48&&c<=57)||(c<=122&&c>=97)){
		    for(let=0;let<=count;let++){
		       	if(charlist[let].Char==c){		//CHECKING IS ALREADY EXIST OR NOT
					check=1;
					charlist[let].Amount++;		//ADD ONE IN AMOUNT IF ALREADY THERE
				 }
			}
			//IF IT IS A NEW CHARECTOR
			if(check==0){
				charlist[count].Char=c;		//ASSIGN NEW CHARECTOR
				charlist[count].Amount=1;	//ASSIGN AMOUNT AS 1
				charlist[count].order=o;	//ASSIGN ORDER TO SAME TIME OCCURENCE CASE
				o=o+1;
				count = count + 1;		
			}				
		}
	}
			
    fclose(fp); 	//CLOSE THE FILE
    
    //RE ARRANGE PART
    int count2;
    int a=0;
    int count3=0,count4;
    
    //RE ARRANGE THE AMOUNT OF OCCURANCE 
    //USING SWAP METHOD
    while(count3<count-1){
    	count4=count3+1;
    	while(count4<count){
    		if((charlist[count3].Amount)<(charlist[count4].Amount)){
    			chars tem=charlist[count3];
    			charlist[count3]=charlist[count4];
    			charlist[count4]=tem;	
			}
			count4++;
		}
		count3++;
	}
	
	//RE ARRANGE ACCORDING TO THE ORDER
    //USING SWAP METHOD
    count3=0;
    while(count3<count-1){
    	count4=count3+1;
    	while(count4<count){
    		if((charlist[count3].Amount)==(charlist[count4].Amount)){
	    		if((charlist[count3].order)>(charlist[count4].order)){
	    			chars tem=charlist[count3];
	    			charlist[count3]=charlist[count4];
	    			charlist[count4]=tem;	
				}
			}
			count4++;
		}
		count3++;
	}
	
	//TO FIND THE TOTAL NUMBER OF CHARECTORS
    
    for(count2=0;count2<count;count2++){
    	a=a+charlist[count2].Amount;
	}
	
	int number;
	
	number=NUMOFLINES;
	
	//WHEN NEEDED LETTERS IS GREATER THAN HERE
	if(number>count){
		number=count;
	}
	
	printf("\n");		//TO THE STARTING BLANK
	
    int SC=scalevar;	//INDICATE SCALED OR NOT
    
    int count6,count7,count8;
    
    ///PLOTTING PART
    for(count6=0;count6<number;count6++){
    	
    	char c1=charlist[count6].Char;
    	char c2=c1;
    	double f1=((charlist[count6].Amount)*100*(1/(float)a));
    	
    	for(count7=1;count7<5;count7++){
    		c2=c1;
    		if(count7==1||count7==3||count7==4){		//TO THE LINES EXCEPT 2
    		c2=' ';										//TO PRINT SPACE AT SECOND IN LINES EXCEPT LINE TWO
    		}
    		
			printf(" %c \u2502",c2);					//PRINT BEFORE PART AND HORIZONTAL CHARECTOR
         
		 	if(count7!=4){								//PRINT THE GRAPH CHARECTOR IN FIRST LINE IN EVERY ROW
    			for(count8=0;count8<boxnum((charlist[count6].Amount),(charlist[0].Amount),70,SC,a);count8++){
					printf("\u2591");
				}
				if(count7==2){
					//PRINTING THE PERSENTAGE VALUE
					printf("%.2f",f1);
					printf("%%");
				}
			}
       		printf("\n");
     		int count10;
      		if(count6==number-1&&count7==4){		//IN LAST LINE
      		//PRINTING X AXIX
        		for(count10=0;count10<3;count10++){
            		printf(" ");
            	}
        		printf("\u2514");
        		int count9;
         		for(count9=0;count9<76;count9++){
        		printf("\u2500");
           		}
            	printf("\n");
			}
			
		}
   
	}
	//IF THERE ARE NO CHARECTORS TO PRINT
    if(count==0){
		printf("No data to process");
		rmrtn();
		return 0;
	}
}

///FUNCTION TO CALCULATE PERSENTAGE WITH TWO DECIMAL
float persentage(int melan,int keelan){
	float p=(float)melan/(float)keelan;	
	float p1=p*10000;
	return p1/100;
}

//FUNCTION TO ADD A WORD TO THE LINKED LIST
void addword(word_d *head,char *curword, int ORDER){
	int checker1=0;
	word_d*startd;
	//IF THE WORD IS ALREADY THERE 
	for(startd=head->next;startd!=NULL;startd=startd->next){
		if(strcmp(startd->WORD,curword)==0){
			startd->amount1++;		//ADD THE AMOUNT AS ONE
			checker1=1;
			break;
			
		}
	}
	//FOR NEW CHARECTOR ENTRANCE
	if(checker1!=1){
			word_d *current;		//CREATE A CURRENT NODE
			current=(word_d*)malloc(sizeof(word_d));	//ALLOCATE NEEDED SPACE
			current->WORD=curword;		//ASSIGN THE WORD INTO THAT NODE
			//EXCHANGE THE NEXT VALUES AND ADD THE CURRENT ADDRESS AS THE HEAD'S NEXT
			current->next=head->next;	
			current->amount1=1;			//ASSIGN THE AMOUNT AS 1 AND PUT ORDER
			current->order1=ORDER;    
   			head->next=current;  	
	}
	
}



int main(int argc1,char**argv1) 
{
	//to remove IF exiting files
  remove("@][IDENTICAL1][@.txt");
  remove("@][IDENTICAL2][@.txt");
  	//defaults values
     int NUMOFLINES=10;
	 int WCcheck=0;
     int scalevar=1;
     
	////////////scale checking////////////
	int arcount;
	for(arcount=0;arcount<argc1;arcount++){
		if(strcmp(argv1[arcount],"--scaled")==0){
			scalevar=0;
		}
	}
	////////file merging////////////////
	FILE *fpi1 = fopen("@][IDENTICAL1][@.txt", "w"); 
	fclose(fpi1);
	int mercount,mercount2;
	for(mercount=1;mercount<argc1;mercount++){
		if((argv1[mercount][0]!='-')&&(strcmp(argv1[mercount-1],"-l")!=0)){
				mergefile("@][IDENTICAL1][@.txt",argv1[mercount]);
		}
	}

	//ERROR PRINTINGS
	char error1[]="Invalid options for [-l]";
	char error2[]="Invalid option(negative) for [-l]";
	char error3[]="usage:";
	char error4[]="Not enough options for [-l]";
	char error5[]="[-c] and [-w] cannot use together";
	char error6[]="Cannot open one or more given files";
	char error7[]="No data to process";
	char error8[]="No input files were given";
  char error9[]="[-l length] [-w | -c] [--scaled] filename1 filename2 ..";
	


	//CHECKING THE LINE NUMBER IS NEGATIVE OR NOT
	int NC=0;
	int negcheck;
	for(arcount=0;arcount<argc1-1;arcount++){
		if((strcmp(argv1[arcount],"-l")==0)&&(argv1[arcount+1][0]=='-')){
			NC=1;
			for(negcheck=1;negcheck<strlen(argv1[arcount+1]);negcheck++){
				if(argv1[arcount+1][negcheck]<'0'||argv1[arcount+1][negcheck]>'9'){
					NC=2;
				}
			}
		}
	}
	
	//	NC=1-> negative length
	//	NC=2-> no length given
	
	if(NC==1){
	printf("%s\n%s %s %s\n",error2,error3,argv1[0],error9);
	rmrtn();
	return 0;
	}else if(NC==2){
	printf("%s\n%s %s %s\n",error1,error3,argv1[0],error9);
	rmrtn();
	return 0;	
	}
	
	//for last argument is -l
	if(strcmp(argv1[argc1-1],"-l")==0){
		printf("%s\n%s %s %s\n",error4,error3,argv1[0],error9);
		rmrtn();
		return 0;
		}
	
	
	
	
	////if there any stranger arguments THAN WE HAVE
	for(arcount=0;arcount<argc1;arcount++){
		
		if((argv1[arcount][0]=='-')&&(strcmp(argv1[arcount],"-l")!=0)&&(strcmp(argv1[arcount],"--scaled")!=0)&&(strcmp(argv1[arcount],"-c")!=0)&&(strcmp(argv1[arcount],"-w")!=0)){
		printf("Invalid option [%s]\n%s %s %s\n",argv1[arcount],error3,argv1[0],error9);
		rmrtn();
		return 0;
		}
	}

	//EXTRACT NUMBEROF LINES FROM ARGUMENTS
	
	int CC;
	int CCcheck=0;
	for(arcount=0;arcount<argc1;arcount++){
		if(CCcheck==0){
			if(strcmp(argv1[arcount],"-l")==0){
				CCcheck=1;
				for(CC=0;CC<strlen(argv1[arcount+1]);CC++){
				if((argv1[arcount+1][0]!='+')&&((argv1[arcount+1][CC]<'0')||(argv1[arcount+1][CC]>'9'))){
					printf("%s\n",error1);	
					printf("%s %s %s\n",error3,argv1[0],error9);
					rmrtn();	
					return 0;		
				}else{
					NUMOFLINES=atoi(argv1[arcount+1]);
				}
			}
			}
		}
	}

	
	for(arcount=0;arcount<argc1;arcount++){
		
		
		//to check word or charector
		if(strcmp(argv1[arcount],"-w")==0){
			WCcheck++;
		}else if(strcmp(argv1[arcount],"-c")==0){
			WCcheck=WCcheck+2;
		}
		
		//if -c and -w are inserted
		if(WCcheck==3){
			printf("%s\n",error5);
			printf("%s %s %s\n",error3,argv1[0],error9);
			rmrtn();
			return 0;
		}
		
	}
	int fchecker=0;
	int fchecker2=0;
	
	//TO FIND THE GIVEN FILES ARE THERE OR NOT
	for(arcount=1;arcount<argc1;arcount++){
			if((argv1[arcount][0]!='-')&&(strcmp(argv1[arcount-1],"-l")!=0)){
	       fchecker2++;
				FILE* checkfp=fopen(argv1[arcount],"r"); 
				
				if(checkfp==NULL){
					fchecker++;
					
				}
				}
	}
	//FILE ERROR CASE
	if(fchecker>0){
		printf("%s\n",error6);
		rmrtn();
		return 0;
	}
	//NO FILES INPUT CASE
	if(fchecker2==0){
		printf("%s\n%s %s %s\n",error8,error3,argv1[0],error9);
		rmrtn();
		return 0;
}	


	
///scalevar=scale or not //WCcheck=word0/1 or char2 //NUMOFLINES 
	if(WCcheck==0||WCcheck==1){
    forword("@][IDENTICAL2][@.txt",NUMOFLINES,scalevar);		
	}else if(WCcheck==2){
    forlett("@][IDENTICAL2][@.txt",NUMOFLINES,scalevar);
}
  rmrtn();
  return 0;
}
////////////////////THE END/////////////////////////////
