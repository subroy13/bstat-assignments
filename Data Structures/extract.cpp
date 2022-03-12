#include <stdio.h>
#include <math.h>
#include <string.h>
int poly1[10]; 
 
void GetNumber2(const char *str) {
 	int i=0,coeff=0,expo=0,temp=0;
 	int nDigits=-1;
 
  while (*str) {
  	nDigits=-1;
    int number;
    if (sscanf(str, "%d", &number) == 1) 
		{
			if(i%2==0) //then it is coeff
			   { coeff=number; temp+=1; printf("\neven i=%d coeff=%d  expo=%d  temp=%d",i,coeff,expo,temp); 
			   }
			else //then it is expo
			   { expo=number; temp+=1; printf("\neven i=%d coeff=%d  expo=%d  temp=%d",i,coeff,expo,temp);
			   }
			   
			 i++;
			    
			   if(temp==2) // tar mane coeff expo dutoi peyegechi.. yahoooo!!!!
                 { poly1[expo]=coeff;  temp=0; coeff=0; expo=0; }
                 else
                 { //Nothing
				 }				 
      
     
     
      if(*str=='+'||*str=='-')
     	nDigits = floor(log10(abs(number))) + 2;
     else
       nDigits = floor(log10(abs(number))) + 1;
    	}
    	
    if(nDigits!=-1){ str+=nDigits; }
	else{ str++;	}
    
  } 
  //printf("\nAt end even i=%d coeff=%d  expo=%d  temp=%d",i,coeff,expo,temp);
if((expo==0)&&(temp==1)) poly1[0]=coeff;
}

int main()
{
    int i=0; 
   char *str = "10x^5-15x^2-7x^1+9";
  
 GetNumber2(str);
 printf("\n\n"); 
 for(i=9;i>=0;i--)
 printf("  %d",poly1[i]);

   
}
