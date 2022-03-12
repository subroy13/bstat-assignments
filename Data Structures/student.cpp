#include <stdio.h>
struct student { char name[20];
				 int roll;
				 int marks;
				};
struct student s[50];
struct batch{ struct student s[50];
			};
struct batch c[10];
sort (int a[],int n)
			{ int temp;
				for (int i=0;i<n-1;i++)
					for (int j=0;j<n;j++)
						if (a[i]>a[j]) { temp=a[i];a[i]=a[j];a[j]=temp; }
			}
int main(){
	int m,n,i,j,k; 
	FILE *f; f=fopen("student.txt","r");
	fscanf(f,"%d %d",&m,&n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			{ char temp;
			  fscanf(f,"%s %d %d\n",c[i].s[j].name,&(c[i].s[j].roll),&(c[i].s[j].marks));
			}
	for(i=0;i<m;i++)
		{ float avr=0; int med[50];
			for(j=0;j<n;j++)
				{ printf("%s",c[i].s[j].name);
		 		 printf(" %d %d\n",(c[i].s[j].roll),(c[i].s[j].marks));
		  		avr+=(float)c[i].s[j].marks/n;
		  		med[j]=c[i].s[j].marks;
				}
			printf("Mean of class %d is %.3f\n",i, avr);
			sort(med,n);
			printf("median of class %d is %d\n\n",i,med[(n+1)/2]);
		}
   fclose(f);
return 0;}
