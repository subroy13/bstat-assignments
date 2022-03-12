#include <stdio.h> 
int length(float n)
	{ int count=0;
	  while(n!=(int)n) n*=10;
	  while((int)n!=0){ count++; n/=10;
	  			 }
	return count+1;
	}

void extract(const char *str,float poly[10]) {
 	int i=0;float coeff=0;int expo=0;int temp=0;
 	int nDigits=-1;
 
  while (*str) {
  	nDigits=-1;
    float number;
    if (sscanf(str, "%f", &number) == 1) 
		{
			if(i%2==0) //then it is coeff
			   {coeff=number; temp+=1; }
			else //then it is an expo
			   { expo=number; temp+=1; }
			 i++;
			    
			   if(temp==2) // So i got both the expo and coeff
                 { poly[expo]=coeff;  temp=0; coeff=0; expo=0; }
                 
     if(*str=='+'||*str=='-')
     	nDigits = length(number)+1;
      else 
	  	 nDigits = length(number);
	  	 
    	if (number==(int)number) str--;
		}
    	
    if(nDigits!=-1){ str+=nDigits; }
	else{ str++;	}
    
  } 
  
if((expo==0)&&(temp==1)) poly[0]=coeff;
}
int main()
{
    int i=0; 
   char *str = "1.35x^6-5.4x^1-37.4";
   float a[10];
 extract(str,a);
 printf("\n\n"); 
 for(i=9;i>=0;i--)
 printf(" %.3f",a[i]);

   
}
