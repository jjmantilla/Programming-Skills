
#include <sstream>
#include "windows.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
const int MAXI=10000, NN=30;
const double BIG=1e30;
static float x_min,x_max,y_min,y_max,X_C,Y_C,xxC,yyC,frefrac;

void viewportboundaries(float xMin, float xMax, float yMin, float yMax, float reductionFactor)
{
	float fx,fy;
	X_C=0.5*(xMin+xMax);
	Y_C=0.5*(yMin+yMax);
	fx=(xMax-xMin)/(x_max-x_min+1e-7);
	fy=(yMax-yMin)/(y_max-y_min+1e-7);
	frefrac=reductionFactor*(fx<fy?fx:fy);
	xxC=0.5*(x_min+x_max);
	yyC=0.5*(y_min+y_max);
}

void updatewindowboundaries(float x, float y)
{
if(x<x_min)	x_min=x;
if(x>x_max)	x_max=x;
if(y<y_min)	y_min=y;
if(y>y_max)	y_max=y;
}

void initwindows()
{
x_min=y_min=BIG;
x_max=y_max=-BIG;
}

float x_viewport(float x)
{
return X_C+frefrac*(x-xxC);
}

float y_viewport(float x)
{
return Y_C+frefrac*(x-yyC);
}

void bsplineA(int u,int prim, int inte, int &niv, char ruta[100],int cantidad_r,char carpeta[600],char archivo[600],int numero)
{
	float x[MAXI],y[MAXI], eps=0.04, XX,YY,t,xA,xB,xC,xD,yA,yB,yC,yD,a0,a1,a2,a3,b0,b1,b2,b3,*auxX1,*auxY1,*auxX2,*auxY2,x1,y1,x2,y2;
	int i,j,n,first,p=0;
	bspXA[u][inte] = new float[MAXI];
	bspYA[u][inte] = new float[MAXI];
	bspXB[u][inte] = new float[MAXI];
	bspYB[u][inte] = new float[MAXI];
	auxX1 = new float[20000];
	auxY1 = new float[20000];
	auxX2 = new float[20000];
	auxY2 = new float[20000];
	float d1=0,d2=0,d=0;
    numero=numero-5;
	int NoN=35;
	FILE *fp;

	char str[200];
	strcpy(str,ruta);
	strcat(str,carpeta);
	//strcpy(str,"TIME");
	char st3[10];
	itoa(niv+1,st3,10);	
	strcat(str,st3);
	strcat(str,archivo);
	char st2[10];
	itoa(u,st2,10);
	strcat(str,st2);
	if(prim==0)	
	{
		fp=fopen(str,"w+");
		fprintf(fp,"%d",cantidad_r);
		for(i=0;i<120;i++)
			fprintf(fp,"\n ");
	}
	else
		fp=fopen(str,"a+");
	ifstream inpfil("curvefit1.txt");
	if(!inpfil)
			printf("\nCannot open input file");
	inpfil >> n;
	if(n<3 || n+1>=MAXI )
			printf("\nFirst number incorrect");
	initwindows();
	for(i=0;i<=n;i++)
	{
		inpfil >> x[i] >> y[i];
		updatewindowboundaries(x[i],y[i]);
	}
	viewportboundaries(x_min,x_max,y_min,y_max, 0.9);
	totalesA[u][inte]=0;
	for(i=0;i<=n;i++)
	{
			XX=x_viewport(x[i]);
			YY=y_viewport(y[i]);
			bspXA[u][inte][totalesA[u][inte]]=XX;
			bspYA[u][inte][totalesA[u][inte]]=YY;
			totalesA[u][inte]++;
	}
	totales1A[u][inte]=totalesA[u][inte];
	first=1;
	
	
	int dd1=0;

	for(i=1;i<n-1;i++)
	{
		xA=x[i-1]; xB=x[i]; xC=x[i+1]; xD=x[i+2];
		yA=y[i-1]; yB=y[i]; yC=y[i+1]; yD=y[i+2];
		a3=(-xA+3*(xB-xC)+xD)/6.0; b3=(-yA+3*(yB-yC)+yD)/6.0;
		a2=(xA-2*xB+xC)/2.0;	b2=(yA-2*yB+yC)/2.0;
		a1=(xC-xA)/2.0;		b1=(yC-yA)/2.0;
		a0=(xA+4*xB+xC)/6.0;		b0=(yA+4*yB+yC)/6.0;
		for(j=0;j<NoN;j++)
		{
			t=(float)j/(float)NoN;
			XX=x_viewport(((a3*t+a2)*t+a1)*t+a0);
			YY=y_viewport(((b3*t+b2)*t+b1)*t+b0);
			auxX1[dd1]=XX;
			auxY1[dd1]=YY;
			if(p==1)
			{
				x2=auxX1[dd1];
				y2=auxY1[dd1];		
				d1+=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				p=1;
			}
			x1=auxX1[dd1];
			y1=auxY1[dd1];
			p=1;
			dd1++;
		}
	}

	float par,dist;
	par=d1/numero;

	p=0;
	d=0;
    int	k,kk,kkk;
	k=kk=kkk=totales1A[u][inte];
	int ccc=0;
	for(j=0;j<dd1;j++)
	{				
			if(p==1)
			{
				x2=auxX1[j];
				y2=auxY1[j];	
				dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				d+=dist;
				if(d>=par)				
				{
					bspXA[u][inte][k]=auxX1[j];
					bspYA[u][inte][k]=auxY1[j];
					ccc++;
					totalesA[u][inte]++;
					d=0;//dist;
					p=0;
					k++;
				}					
				
			}
			x1=auxX1[j];
			y1=auxY1[j];
			p=1;
	}
    ifstream inpfil2("curvefit2.txt");
	if(!inpfil2)
			printf("\nCannot open input file");
	inpfil2 >> n;
	if(n<3 || n+1>=MAXI )
			printf("\nFirst number incorrect");
	initwindows();
	for(i=0;i<=n;i++)
	{
		inpfil2 >> x[i] >> y[i];
		updatewindowboundaries(x[i],y[i]);
	}
	viewportboundaries(x_min,x_max,y_min,y_max, 0.9);
	totalesB[u][inte]=0;
	for(i=0;i<=n;i++)
	{
			XX=x_viewport(x[i]);
			YY=y_viewport(y[i]);
			bspXB[u][inte][totalesB[u][inte]]=XX;
			bspYB[u][inte][totalesB[u][inte]]=YY;
			totalesB[u][inte]++;
	}
	totales1B[u][inte]=totalesB[u][inte];
	first=1;	
	int dd2=0;
	d2=0;
	p=0;
	for(i=1;i<n-1;i++)
	{
		xA=x[i-1]; xB=x[i]; xC=x[i+1]; xD=x[i+2];
		yA=y[i-1]; yB=y[i]; yC=y[i+1]; yD=y[i+2];
		a3=(-xA+3*(xB-xC)+xD)/6.0; b3=(-yA+3*(yB-yC)+yD)/6.0;
		a2=(xA-2*xB+xC)/2.0;	b2=(yA-2*yB+yC)/2.0;
		a1=(xC-xA)/2.0;		b1=(yC-yA)/2.0;
		a0=(xA+4*xB+xC)/6.0;		b0=(yA+4*yB+yC)/6.0;
		for(j=0;j<NoN;j++)
		{
			t=(float)j/(float)NoN;
			XX=x_viewport(((a3*t+a2)*t+a1)*t+a0);
			YY=y_viewport(((b3*t+b2)*t+b1)*t+b0);
			auxX2[dd2]=XX;
			auxY2[dd2]=YY;
			if(p==1)
			{
				x2=auxX2[dd2];
				y2=auxY2[dd2];		
				d2+=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				p=1;
			}
			x1=auxX2[dd2];
			y1=auxY2[dd2];
			p=1;
			dd2++;
		}
	}

	par=(float)d2/numero;
	
	p=0;
	d=0;
	int ccc1=0;
    int	k1,kk1,kkk1;
	k1=kk1=kkk1=totales1B[u][inte];
	ccc1=0;
	for(j=0;j<dd2;j++)
	{				
			if(p==1)
			{
				x2=auxX2[j];
				y2=auxY2[j];	
				dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				d+=dist;
				if(d>=par)				
				{
					bspXB[u][inte][k1]=auxX2[j];
					bspYB[u][inte][k1]=auxY2[j];
					ccc1++;
					totalesB[u][inte]++;
					d=0;//d=dist;
					p=0;
					k1++;
				}							
			}
			x1=auxX2[j];
			y1=auxY2[j];
			p=1;
	}



int prom=(ccc1+ccc)/2;
if(ccc<ccc1)
prom=ccc1;
else
prom=ccc;

if(ccc1!=ccc)
{
if(ccc<ccc1)
{	
	float canti1=numero;
	do
	{
	par=(float)d2/(canti1);	
	if(ccc1<prom)
		canti1+=0.1;
	else
		canti1-=0.1;
	p=0;
	d=0;
	totalesB[u][inte]=totales1B[u][inte];
	kk1=totales1B[u][inte];
	ccc1=0;
	for(j=0;j<dd2;j++)
	{				
			if(p==1)
			{
				x2=auxX2[j];
				y2=auxY2[j];	
				dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				d+=dist;
				if(d>=par)
				{
					bspXB[u][inte][kk1]=auxX2[j];
					bspYB[u][inte][kk1]=auxY2[j];
					ccc1++;
					totalesB[u][inte]++;
					d=0;//dist;
					p=0;
					kk1++;
				}					
				
			}
			x1=auxX2[j];
			y1=auxY2[j];
			p=1;
	}

	}while(ccc1!=prom+1&&ccc1!=prom-1&&ccc1!=prom);

}
else
{
if(ccc>ccc1)
{
	float canti=numero;
	do
	{
	par=(float)d1/(canti);
	if(ccc<prom)
		canti+=0.1;
	else
		canti-=0.1;
	p=0;
	d=0;
	ccc=0;
    totalesA[u][inte]=totales1A[u][inte];
	kk=totales1A[u][inte];
	for(j=0;j<dd1;j++)
	{				
			if(p==1)
			{
				x2=auxX1[j];
				y2=auxY1[j];	
				dist=sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				d+=dist;
				if(d>=par)
				{
					bspXA[u][inte][kk]=auxX1[j];
					bspYA[u][inte][kk]=auxY1[j];
					ccc++;
					totalesA[u][inte]++;
					d=0;//dist;
					p=0;
					kk++;
				}					
				
			}
			x1=auxX1[j];
			y1=auxY1[j];
			p=1;
	}
	}while(ccc!=prom+1&&ccc!=prom-1&&ccc!=prom);


}
}
}
int ll=0,l,c=0;

	for(j=totales1A[u][inte],l=totales1B[u][inte];j<totales1A[u][inte]+ccc;j++,l++)
	{
			if(bspXA[u][inte][j]<0||bspXB[u][inte][l]<0||bspYA[u][inte][j]<0||bspYB[u][inte][l]<0)
				c++;
			else
			{ 
			   fprintf(fp,"\n%f  %f  0",(float)(bspXA[u][inte][j]+bspXB[u][inte][l])/2,(float)(bspYA[u][inte][j]+bspYB[u][inte][l])/2);
			   ll++; 
			}

	}
	fclose(fp);
	fp=fopen(str,"r+");
	fseek(fp,sizeof(int)*(prim+1),SEEK_SET);
	fprintf(fp,"%d\n",ll);
	fclose(fp);
	delete[] auxX1;	
	delete[] auxY1;	
	delete[] auxX2;	
	delete[] auxY2;	
	delete[] bspXA[u][inte];
	delete[] bspYA[u][inte];
	delete[] bspXB[u][inte];
	delete[] bspYB[u][inte];
}

void CartoPolar(float x,float y,float &rho,float &theta)
{
		rho = (float) (sqrt(pow((double)x,2.0)+pow((double)y,2.0)));
		theta = (float) (atan2(y,x));
}

void ordenar(int *b[16][90],int u, int m, int inte)
{
	float temp1;

	for(int i=0;i<m;i++)
	{  for(int j=0;j<m-1;j++) 
       {
           if (b[u][inte][j] > b[u][inte][j+1]) 
           {
               int temp = b[u][inte][j]; 
               b[u][inte][j]= b[u][inte][j+1];
               b[u][inte][j+1]= temp;
           }
       }
   } 

}


void ordenar1(int *b[16][90], int *c[16][90],int u, int m, int inte)
{
    float temp1;
	for(int i=0;i<m;i++)
	{  for(int j=0;j<m-1;j++) 
       {
           if (b[u][inte][j] > b[u][inte][j+1]) 
           {
               int temp = b[u][inte][j]; 
               b[u][inte][j]= b[u][inte][j+1];
               b[u][inte][j+1]= temp;
			   temp = c[u][inte][j]; 
               c[u][inte][j]= c[u][inte][j+1];
               c[u][inte][j+1]= temp;




           }
       }
   } 

}

