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

polyadd (float a[10],float b[10],float c[20])
		{ int i=0; 
		for(i=0;i<10;i++)
				c[i]=a[i]+b[i];
		}
polymult (float a[10],float b[10],float c[20])
			{ int i,k; 
			for(i=0;i<20;i++)
				{ float sum=0;
				  for(k=0;k<10;k++)
				  		if((i-k)<10 && i>=k) sum+= a[k]*b[i-k];
				  c[i]=sum;
				}	
			}
			
			
int main()
{ 	
	FILE *f; f=fopen("poly.txt","r");
	float a[10],b[10],c[20]; char s[100]; int i=0; 
	for(i=0;i<10;i++) a[i]=0;
	for(i=0;i<10;i++) b[i]=0;
	for(i=0;i<20;i++) c[i]=0;
	fgets(s,100,f);
	extract(s,a);
	for(i=0;i<100;i++) s[i]=0;
	fgets(s,100,f);
	extract(s,b);
	polyadd(a,b,c);
			printf("\n\nThe result of addition is:  ");
			for(i=19;i>0;i--)
					{ if (c[i]>0) printf("+%.3fx^%d",c[i],i); 
					  if (c[i]<0) printf("%.3fx^%d",c[i],i);
					}      // printing the result of addition
			if (c[0]>0) printf("+%.3f\n",c[i]); 
			if (c[0]<0) printf("%.3f\n",c[i]);
	for(i=0;i<20;i++) c[i]=0;
	polymult(a,b,c);
			printf("The result of multiplication is:  ");
			for(i=19;i>0;i--)
					{ if (c[i]>0) printf("+%.3fx^%d",c[i],i); 
					  if (c[i]<0) printf("%.3fx^%d",c[i],i);
					}      // printing the result of addition
			if (c[0]>0) printf("+%.3f\n",c[i]); 
			if (c[0]<0) printf("%.3f\n",c[i]);
return 0;}
