#include <sstream>
#include "windows.h"
#include <FL/filename.H>
#include "Correspondence.h"
#include "Objects.h"
#include "vtkbspline.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkFlRenderWindowInteractor.h>
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkPoints.h"
#include "vtkMath.h"
#include "vtkPolyData.h"
#include "vtkVoxelContoursToSurfaceFilter.h"
#include "vtkShrinkFilter.h"
#include "vtkDataSetMapper.h"
#include "vtkOutlineFilter.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkDelaunay3D.h"
#include "vtkTriangleFilter.h"
#include "vtkMassProperties.h"
#include "vtkCamera.h"
#include "vtkTimerLog.h"
#include "vtkCellArray.h"
#include "vtkActorCollection.h"
#include "vtkShrinkFilter.h"
#include "vtkSurfaceReconstructionFilter.h"
#include "vtkContourFilter.h"
#include "vtkReverseSense.h"
#include "vtkCleanPolyData.h"
#include "vtkConeSource.h"
#define TIMES 16
#define CONTORNS 90
int DESP_X;
int DESP_Y;
int bases,ecuador,apex,niv_arch,cual=-1,fgg,number_cones,conces;
int first1=0;
Fl_Box *box_criticos,*box_tiempo,*box_contorno,*flbox1;
Fl_Window *ventana1;
Fl_Window *ventana2;
Fl_Window *ventana3;
Fl_Window *ventana5;
Fl_Window *ventana6;
Fl_Progress *progress;
Fl_Progress *progress1;
Fl_Progress *progress2;
Fl_Progress *progress3;
Fl_Progress *progressA;
Fl_Progress *progressB;
Fl_Button *butt1,*butt5,*butt6,*butt7,*butt10,*butt3;
Fl_Input* inpu;
Fl_Choice *combo;
Fl_Slider* s2;
Fl_Slider* s3;
//Fl_Input *input;
vtkActor *contornoActorA; 
vtkActor *contornoActorB; 
vtkActor *contornoActorC; 
vtkActor *contornoActorD; 
vtkActor *contornoActorE; 
vtkActor *contornoActorF;
vtkActor *contornoActorG; 
vtkActor *contornoActorH; 
vtkActor *contornoActorI; 
vtkActor *contornoActorJ; 
vtkActor *contornoActorAA; 
vtkActor *contornoActorBB; 
vtkActor *contornoActorCC; 
vtkActor *contornoActorDD; 
vtkActor *contornoActorC10; 
vtkActor *contornoActorC20; 
vtkActor *contornoActorC3; 
vtkActor *coneActor[30000]; 
vtkFlRenderWindowInteractor *fl_vtk_windowAS,*fl_vtk_windowV; 
vtkPoints *pointsA[16];	
vtkCellArray *polysA[16];
vtkPoints *pointsB[16];	
vtkCellArray *polysB[16];
vtkConeSource *cone[30000];

vtkRenderer *renglob,*renglobVec,*renglob1,*renglob3,*renglob4,*renglob10,*renglob12,*renglob13,*renglob14;

float r, g, b;
int cantidad,criticos,pointsC,pointsM,pointsL ,critic,interes,todos=1,nnn,criticos1,criticos2,cant1,cant2;
int du=-1;
int *v[TIMES];
float *puntop[TIMES][CONTORNS][3];
int correspond=0,conto=0,contoB=1,contoA=1,nivelado=0;
char carpeta[600],archivo[600],ruta3[600];
struct point
{
float x,y;
};


struct point1
{
	float r,t,d,x,y,z;
	int tipo;
	float critical;
	int indice;
	struct point1 *sig;
}*polar,*polar1,*polar1M,*aux;

typedef point1 * ppoint;

struct corrs1
{
	float x,y,z;
	int tipo;
	int indice;
	struct corrs1 *sig;
}*polar2;
typedef corrs1 * ccorrs;
ccorrs *corresp1[TIMES],*corresp2[TIMES],*primcorr1[TIMES],*primcorr2[TIMES];
ppoint *recorre[TIMES],*recorreM[TIMES],*primero[TIMES],*primeroM[TIMES],*primeroL[TIMES],*recorreL[TIMES],*primeroC[TIMES],*recorreC[TIMES],*primeroCrit[TIMES],*recorreCrit[TIMES];
int *contourn[TIMES],*contourn1[TIMES];
struct correspon
{
	int indice1,indice2;
	struct correspon *sig;
}*ppol;

typedef correspon * pccorrs;
pccorrs *pcor[TIMES],*pcor1[TIMES],*pprim[TIMES],*pprim1[TIMES];


void dibujar_arbol(vtkRenderer *ren,float r, float g, float b, float desp,int u, int despY,int carp,int sec,int gr,int vent,int);
void pintar_final_correspondence(vtkFlRenderWindowInteractor *,vtkRenderer *,int,int);
void arbol(int);
void final_correspondence();
void dibujar_criticos();
int find_correspondence(int,int);
int *final_crit,final_cant,*indice[CONTORNS],crit_dibuj;
float *indiceX[CONTORNS],*indiceY[CONTORNS],*indiceXB[TIMES][CONTORNS],*indiceYB[TIMES][CONTORNS],*indiceZB[TIMES][CONTORNS];
int interes1,prime=0;
int quant=16,quant1=16,dibujo=1,niv=0,menorCont[CONTORNS]={9999};
void bspline(int,int,int);
void bsplineA(int,int,int,int&, char[],int,char[],char[]);
char *ruta1,ruta[100],*combnumber;


void convertir(int j, int u)
{       float r,t;
        r=sqrt(pow((double)recorre[u][j]->r,2)+pow((double)recorre[u][j]->t,2));
        t=(float)atan2(recorre[u][j]->t,recorre[u][j]->r);
        recorre[u][j]->r=r;
        recorre[u][j]->t=t;
}

void conversion_rec_polar(int turno, int u, int carp)
{
        FILE *coords;
		char s1[200],s[100],s2[100];	
        struct point punto;
        float acumx[100],acumy[100],centroidex,centroidey,distance=0.0,d=0.0;
        int i=0,interes1;
		char st3[15];		
		criticos=0;
		pointsC=0;
		pointsM=0;
		pointsL=0;
		critic=0;	
		interes1=u;
		itoa(interes1,s,10);		
		itoa(carp,s2,10);
		strcpy(s1,ruta);
		strcat(s1,carpeta);
    	if(carp==1)
		{
	    itoa(niv,st3,10);	
	    strcat(s1,st3);	
		}
		
		strcat(s1,archivo);
		strcat(s1,s);				
		

		coords=fopen(s1,"r");				
		fscanf(coords,"%d",&cantidad);

		if(first1==0)
		{
		for(i=0;i<cantidad;i++)
		{	menorCont[i]=9999;
		}
		first1=1;
		
		}
		
        recorre[u]=new ppoint[cantidad];
		recorreM[u]=new ppoint[cantidad];
        recorreL[u]=new ppoint[cantidad];
		recorreC[u]=new ppoint[cantidad];
		recorreCrit[u]=new ppoint[cantidad];

		primero[u]=new ppoint[cantidad];
        primeroC[u]=new ppoint[cantidad];
		primeroM[u]=new ppoint[cantidad];
		primeroL[u]=new ppoint[cantidad];        
		primeroCrit[u]=new ppoint[cantidad];

		corresp1[u]=new ccorrs[cantidad];
		primcorr1[u]=new ccorrs[cantidad];
		
		float z=0.0;

		v[u]=new int[cantidad];
		contourn[u]=new int[cantidad];
		
		
        
		for(int j=0;j<cantidad;j++)
		{	
			fscanf(coords,"%d\n",&v[u][j]);
			if(carp!=1)
			if(v[u][j]<menorCont[j])
				menorCont[j]=v[u][j];
			
			
		}
		j=0;
		int ii=0,j32;

		do
		{   acumx[j]=0.0;
			acumy[j]=0.0;		
		    recorre[u][j]=new point1;
	        primero[u][j]=new point1;
			corresp1[u][j]=new corrs1;
			primcorr1[u][j]=new corrs1;
			corresp1[u][j]=NULL;
			primcorr1[u][j]=NULL;
			corresp1[u][j]=primcorr1[u][j];
	        aux=new point1;
		    recorre[u][j]=NULL;
			primero[u][j]=NULL;			
			recorre[u][j]=primero[u][j];		
			i=0;
			j32=0;
			do
			{
	            fscanf(coords,"%f %f %f\n",&punto.x,&punto.y,&z);			
				polar1=new point1;
				polar1->r=punto.x;
				polar1->t=punto.y;
				polar1->x=punto.x;
				polar1->y=punto.y;
				polar1->tipo=0;
				polar1->z=z;    
				polar1->indice=i;
				polar1->sig=NULL;

				polar2=new corrs1;
				polar2->x=punto.x;
				polar2->y=punto.y;
				polar2->tipo=0;
				polar2->z=z;    
				polar2->indice=i;
				polar2->sig=NULL;
	
		        acumx[j]+=punto.x;
				acumy[j]+=punto.y;
				i++;
				if (primero[u][j]==NULL)
				{   primero[u][j]=polar1;
					recorre[u][j]=polar1;
					aux=polar1;
					corresp1[u][j]=polar2;
					primcorr1[u][j]=polar2;			   			   								
				}
				else
				{	recorre[u][j]->sig=polar1;
					recorre[u][j]=polar1;
					corresp1[u][j]->sig=polar2;
	                corresp1[u][j]=polar2;			   			   
				}

			}while(i<v[u][j]);
			corresp1[u][j]->sig=primcorr1[u][j];
			j++;		

		}while(j<cantidad);
		
		fclose(coords);	

		for(j=0;j<cantidad;j++)   //    CENTRO DE GRAVEDAD
		{
			centroidex=acumx[j]/v[u][j];
			centroidey=acumy[j]/v[u][j];
		    recorre[u][j]->sig=primero[u][j];
	        i=0;
			d=0.0;
			do
			{
				i++;
				recorre[u][j]->r=recorre[u][j]->r-centroidex;
				recorre[u][j]->t=recorre[u][j]->t-centroidey;
				recorre[u][j]=recorre[u][j]->sig;

			}while(recorre[u][j]->sig!=primero[u][j]);

		    recorre[u][j]->sig=primero[u][j];  //NORMALIZANDO
			i=0;
			do
			{
				i++;
				d += (float) sqrt(((recorre[u][j]->r)*(recorre[u][j]->r)) + ((recorre[u][j]->t)*(recorre[u][j]->t)) );
				recorre[u][j]=recorre[u][j]->sig;

			}while(recorre[u][j]->sig!=primero[u][j]);
			distance=d/i;

			
			recorre[u][j]->sig=primero[u][j];
			i=0;
			do
			{
				i++;
				recorre[u][j]->r=recorre[u][j]->r/distance;
				recorre[u][j]->t=recorre[u][j]->t/distance;
				convertir(j,u);				
				recorre[u][j]=recorre[u][j]->sig;

			}while(recorre[u][j]->sig!=primero[u][j]);			
		}
		
}


void play(vtkRenderer *ren,vtkFlRenderWindowInteractor *flrwi)
{
	float rr,gg,bb;
	
	for(int uu=0;uu<quant1;uu++)
	{
	vtkPolyData *contorno = vtkPolyData::New();
	contorno->SetPoints(pointsA[uu]);
	contorno->SetPolys(polysA[uu]);
	pointsA[uu]->Delete();
	polysA[uu]->Delete();	
	vtkSmoothPolyDataFilter *poligono = vtkSmoothPolyDataFilter::New();
	poligono->SetInput(contorno);	
	vtkPolyDataMapper *poligonoMapper = vtkPolyDataMapper::New();
	poligonoMapper->SetInput(poligono->GetOutput());
	ren->RemoveActor(contornoActorC3);
	contornoActorC3= vtkActor::New();
	contornoActorC3->SetMapper(poligonoMapper);
	rr = rand()%255; 
	gg = rand()%255; 
	bb = rand()%255;
	


   contornoActorC3->GetProperty()->SetAmbient(0.1);
  contornoActorC3->GetProperty()->SetDiffuse(0.3);
  contornoActorC3->GetProperty()->SetSpecular(1.0);
  contornoActorC3->GetProperty()->SetSpecularPower(30.0);

	contornoActorC3->GetProperty()->SetColor(rr,gg,bb);

	contornoActorC3->GetProperty()->SetRepresentationToWireframe();
	poligonoMapper->Delete();
    ren->AddActor(contornoActorC3);	
	contornoActorC3->Delete();
	progressA->value(uu);       			
	Fl::check(); 
	usleep(1000);	
    flrwi->Render();	
	

	}
}

void play2(vtkRenderer *ren,vtkFlRenderWindowInteractor *flrwi)
{
	float rr,gg,bb;
	int r =combo->value();
try
{
	do
	{
		if(fgg==88888)
			break;
		cual++;
	vtkPolyData *contorno = vtkPolyData::New();
	contorno->SetPoints(pointsB[cual]);
	contorno->SetPolys(polysB[cual]);
		if(fgg==88888)
			break;
	pointsB[cual]->Delete();
	polysB[cual]->Delete();	
	vtkSmoothPolyDataFilter *poligono = vtkSmoothPolyDataFilter::New();
	poligono->SetInput(contorno);	

	vtkPolyDataMapper *poligonoMapper = vtkPolyDataMapper::New();
	poligonoMapper->SetInput(poligono->GetOutput());


	ren->RemoveActor(contornoActorC3);
	contornoActorC3= vtkActor::New();
	contornoActorC3->SetMapper(poligonoMapper);
	if(fgg==88888)
			break;
	
	int i;
	for(i=conces*cual;i<conces*cual+conces;i++)
	{	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
		if(fgg==88888)
			break;
		coneMapper->SetInputConnection(cone[i]->GetOutputPort() );		
		coneActor[i]= vtkActor::New();
		coneActor[i]->SetMapper( coneMapper );
			if(fgg==88888)
			break;
	    coneMapper->Delete();
		ren->AddActor(coneActor[i]);	
		coneActor[i]->Delete();
		if(fgg==88888)
			break;

	//	
	}
//coneMapper->Delete();


	rr = 5.5;//rand()%255; 
	gg = 5.5;//rand()%255; 
	bb = 5.5;//rand()%255;
	
if(fgg==88888)
			break;

   contornoActorC3->GetProperty()->SetAmbient(0.1);
  contornoActorC3->GetProperty()->SetDiffuse(0.3);
  contornoActorC3->GetProperty()->SetSpecular(1.0);
  contornoActorC3->GetProperty()->SetSpecularPower(30.0);

	contornoActorC3->GetProperty()->SetColor(rr,gg,bb);

	contornoActorC3->GetProperty()->SetRepresentationToWireframe();
	poligonoMapper->Delete();
    ren->AddActor(contornoActorC3);	
	
	contornoActorC3->Delete();
	

	//progressB->value(cual);       			
	Fl::check(); 
if(fgg==88888)
			break;
	flrwi->Render();
//	usleep(100);	
	for(i=conces*cual;i<conces*cual+conces;i++)
	{
		ren->RemoveActor(coneActor[i]);
	}
		
	if(cual==r)
		cual=-1;
	if(fgg==88888)
			break;

	}while(1);
}
catch(...)
{
}
	
}
void dibujar_contorno_total(vtkRenderer *ren,float r, float g, float b, int turno,vtkFlRenderWindowInteractor *flrwi,int sec,float desp,int u, int despY,int ventana,int carp)
{
	char s1[200],s2[100],s[100];
	int i,ii,c;
	FILE *coords;
	
	float x,y,z;
	int j,*temp;	
	for(int uu=0;uu<quant1;uu++)
	{

	pointsA[uu] = vtkPoints::New();
	polysA[uu] = vtkCellArray::New();
	
	
	interes1=uu;
	itoa(interes1,s,10);		
	itoa(carp,s2,10);
	strcpy(s1,ruta);
	strcat(s1,carpeta);
	if(carp!=0)
		strcat(s1,s2);
	strcat(s1,archivo);
	strcat(s1,s);				
	coords=fopen(s1,"r");
	
	fscanf(coords,"%d",&c);	
	
	temp=new int[cantidad];
	for(j=0;j<cantidad;j++)
		fscanf(coords,"%d\n",&temp[j]);
	j=0;
	i=0;
	ii=0;
	do
	{
		polysA[uu]->InsertNextCell(temp[j]);		
		i=0;
		do
		{
			fscanf(coords,"%f %f %f\n",&x,&y,&z);			
			pointsA[uu]->InsertNextPoint(y,z,x);
			polysA[uu]->InsertCellPoint(ii);			
			i++;
			ii++;
		}while(i<temp[j]);
		j++;
	}while(j<cantidad);
	
	}

play(ren,flrwi);
    delete[] temp;
}


void dibujar_contorno_total_vector(vtkRenderer *ren,float r, float g, float b, int turno,vtkFlRenderWindowInteractor *flrwi,int sec,float desp,int u, int despY,int ventana,int carp)
{


	int i,c,ss;
	char s1[200],s[200];
	FILE *coords;
	float rr,gg,bb,x,y,z,yy[200],xx[200],hh[200],xxx[200][90],yyy[200][90],hhh[200][90],mayor=0;
	int k,coto;
	int j,ii=0,*temp;	
	rr=0;gg=255;bb=0;
	
	k=0;
	int t;
	ii=0;	
	
	for(ss=0;ss<combo->value()+1;ss++)
	{			
		itoa(ss,s,10);	
		strcpy(s1,ruta);
		strcat(s1,carpeta);		
		strcat(s1,archivo);
		strcat(s1,s);	
		coords=fopen(s1,"r");				
		fscanf(coords,"%d",&c);	
		temp=new int[cantidad];	
   		for(j=0;j<cantidad;j++)
			fscanf(coords,"%d\n",&temp[j]);	
		for(t=0;t<cantidad;t++)
		{
			indiceXB[ss][t]=new float[final_crit[t]];		
			indiceYB[ss][t]=new float[final_crit[t]];		
			indiceZB[ss][t]=new float[final_crit[t]];		
			j=0;
			int re=0;
			i=0;
			do
			{
				fscanf(coords,"%f %f %f\n",&x,&y,&z);								
				if(indice[t][re]<temp[t])
				{
					if(i==indice[t][re])
					{
						indiceXB[ss][t][re]=x;
						indiceYB[ss][t][re]=y;
						indiceZB[ss][t][re]=z;
						re++;
						if(re==final_crit[t])
							re=0;
						if(z>mayor)
						{	mayor=z;
							coto=ss;
						}
					}
				}
				else
				{
					indiceXB[ss][t][re]=x;
					indiceYB[ss][t][re]=y;
					indiceZB[ss][t][re]=z;
					re++;
					if(re==final_crit[t])
						re=0;
					if(z>mayor)
					{	mayor=z;
						coto=ss;
					}			
				}
				i++;
			}while(i<=temp[t]);	
		}	
		
		fclose(coords);		
		
	}
		
	int cc=0,vec_p=0;		
	
	for(j=0;j<cantidad;j++)
		for(k=0;k<final_crit[j];k++)
		{
			hhh[j][k]=indiceZB[coto][j][k];
			yyy[j][k]=indiceYB[coto][j][k];
			xxx[j][k]=indiceXB[coto][j][k];
		}
	

	t=coto;
	printf("\nMayor %d\n",coto);
	int w=0,ww=0;
	
number_cones=0;
	do
	{   
		pointsB[w] = vtkPoints::New();
		polysB[w] = vtkCellArray::New();
		conces=0;

		ii=0;
		for(k=0;k<cantidad;k++)
		{				
			if(k%8==0)
			{		
				cc=0;
				for(int uu=0;uu<final_crit[k];uu++)
				{
					polysB[w]->InsertNextCell(2);
					pointsB[w]->InsertNextPoint(xxx[k][uu],hhh[k][uu],yyy[k][uu]);														
					polysB[w]->InsertCellPoint(ii);	
					ii++;			
					int tt;
					tt=t+1;
					if(tt==combo->value()+1)
						tt=0;
					if(yyy[k][uu]==indiceYB[tt][k][uu]&&  hhh[k][uu]==indiceZB[tt][k][uu]&&xxx[k][uu]==indiceXB[tt][k][uu])
						desp=1;
					else
						desp=0;
					pointsB[w]->InsertNextPoint(indiceXB[tt][k][uu]+desp,indiceZB[tt][k][uu]+desp,indiceYB[tt][k][uu]+desp);														
					polysB[w]->InsertCellPoint(ii);	
					hh[cc]=indiceZB[tt][k][uu]+desp;
					yy[cc]=indiceYB[tt][k][uu]+desp;
					xx[cc]=indiceXB[tt][k][uu]+desp;
					cc++;
					ii++;			

					cone[number_cones] = vtkConeSource::New();
					cone[number_cones]->SetHeight( 4 );
					cone[number_cones]->SetRadius( 1 );
					cone[number_cones]->SetResolution( 15 );
					float diry=yyy[k][uu]-indiceYB[tt][k][uu];
					float dirz=hhh[k][uu]-indiceZB[tt][k][uu];
					float dirx=xxx[k][uu]-indiceXB[tt][k][uu];
					cone[number_cones]->SetDirection(-1.0*dirx,-1.0*dirz,-1.0*diry);
					cone[number_cones]->SetCenter(indiceXB[tt][k][uu],indiceZB[tt][k][uu],indiceYB[tt][k][uu]);
					number_cones++;
					conces++;
				}				
				
			}
		}
		t++;
		if(t>=combo->value()+1)
			t=0;
		vec_p++;
		w++;
		ww++;	
	}while(vec_p<(combo->value()+1));
	cual=-1;
	fgg=0;
	play2(ren,flrwi);
	delete[] temp;
	for(ss=0;ss<combo->value()+1;ss++)
	{			
		for(t=0;t<cantidad;t++)
		{
			delete[] indiceXB[ss][t];
			delete[] indiceYB[ss][t];
			delete[] indiceZB[ss][t];

		}
	}


}



void find_points_M(int turno,int u, int carp)
{
    float A,B,C,D,menor,x1,y1,x2,y2,d1,d2,d;
	float z=0.0;
    FILE *fph;
	int i=1,criticos_contourn,j=0;
	criticos=0;
    critic=0;
	pointsC=0;
	pointsM=0;
	pointsL=0;
	j=0;
	char str[200],st3[10];
	strcpy(str,ruta);

	strcat(str,carpeta);	
	if(carp==1)
	{
	itoa(niv,st3,10);	
	strcat(str,st3);	
	}
	strcat(str,"crit");



	strcat(str,archivo);
	char st2[10];
	itoa(u,st2,10);
	strcat(str,st2);
	strcat(str,"crit");
	for(j=0;j<cantidad;j++)
	{
		if(j==0)
		{
			fph=fopen(str,"w");
			fprintf(fph,"%d\n",cantidad);
			for(int y=0;y<cantidad;y++)
				fprintf(fph,"--\n");					
		}
		else
			fph=fopen(str,"a");
		criticos_contourn=0;
		primeroM[u][j]=new point1;
		recorreM[u][j]=new point1;		
		primeroCrit[u][j]=new point1; 
		recorreCrit[u][j]=new point1;
		primeroC[u][j]=new point1;
		recorreC[u][j]=new point1;        			
		primeroL[u][j]=new point1;
		recorreL[u][j]=new point1;
		primeroL[u][j]=NULL;
		primeroC[u][j]=NULL;
		primeroCrit[u][j]=NULL;			
		primeroM[u][j]=NULL;
		
		recorreCrit[u][j]=primeroCrit[u][j];
		recorreL[u][j]=primeroL[u][j];
		recorreC[u][j]=primeroC[u][j];
		recorreM[u][j]=primeroM[u][j];
		recorre[u][j]=primero[u][j];					
		do
		{
		    i++;
		    if( ( ( recorre[u][j]->sig->r - recorre[u][j]->r)>0  && (recorre[u][j]->sig->sig->r-recorre[u][j]->sig->r)<0 ) || (( recorre[u][j]->sig->r - recorre[u][j]->r)<0  && (recorre[u][j]->sig->sig->r-recorre[u][j]->sig->r)>0 ) ||  ( ( recorre[u][j]->sig->t - recorre[u][j]->t)>0  && (recorre[u][j]->sig->sig->t-recorre[u][j]->sig->t)<0 ) || (( recorre[u][j]->sig->t - recorre[u][j]->t)<0  && (recorre[u][j]->sig->sig->t-recorre[u][j]->sig->t)>0 ) )
			{
				polar1M=new point1;
				polar1M->r=recorre[u][j]->sig->r;
				polar1M->t=recorre[u][j]->sig->t;
				polar1M->x=recorre[u][j]->sig->x;
				polar1M->y=recorre[u][j]->sig->y;
				polar1M->z=recorre[u][j]->sig->z;
				polar1M->indice=recorre[u][j]->sig->indice;
				polar1M->tipo=1;
				recorre[u][j]->sig->tipo=1;
				polar1M->sig=NULL;
				if (primeroM[u][j]==NULL)
				{  primeroM[u][j]=polar1M;
	               recorreM[u][j]=polar1M;
				}
				else
				{  recorreM[u][j]->sig=polar1M;
	               recorreM[u][j]=polar1M;
				}
			}
			recorre[u][j]=recorre[u][j]->sig;
		}while(recorre[u][j]->sig!=primero[u][j]);
		
		recorreM[u][j]->sig=primeroM[u][j];
		recorreM[u][j]=primeroM[u][j];
		recorre[u][j]=primero[u][j];
		do
		{
			A=recorreM[u][j]->r*sin(recorreM[u][j]->t)-recorreM[u][j]->sig->r*sin(recorreM[u][j]->sig->t);
			B=recorreM[u][j]->sig->r*cos(recorreM[u][j]->sig->t)-recorreM[u][j]->r*cos(recorreM[u][j]->t);
			C=recorreM[u][j]->r*recorreM[u][j]->sig->r*sin(recorreM[u][j]->sig->t-recorreM[u][j]->t);
			D=pow((double)recorreM[u][j]->r,2)+pow((double)recorreM[u][j]->sig->r,2)-2*recorreM[u][j]->r*recorreM[u][j]->sig->r*cos(recorreM[u][j]->t-recorreM[u][j]->sig->t);
		    while(recorre[u][j]->r!=recorreM[u][j]->r)
			    recorre[u][j]=recorre[u][j]->sig;
			i=0;
			while(recorre[u][j]->r!=recorreM[u][j]->sig->r)
			{   recorre[u][j]->d=(A*recorre[u][j]->r*cos(recorre[u][j]->t)+B*recorre[u][j]->r*sin(recorre[u][j]->t)+C)/sqrt(D);
				recorre[u][j]=recorre[u][j]->sig;
				i++;
			}
		   recorreM[u][j]=recorreM[u][j]->sig;
   		}while(recorreM[u][j]!=primeroM[u][j]);
  
        recorre[u][j]=primero[u][j];
		do
		{
			i++;
			if( ( ( recorre[u][j]->sig->d - recorre[u][j]->d)>0  && (recorre[u][j]->sig->sig->d-recorre[u][j]->sig->d)<0 ) || (( recorre[u][j]->sig->d - recorre[u][j]->d)<0  && (recorre[u][j]->sig->sig->d-recorre[u][j]->sig->d)>0 ) )
			{
			    polar1M=new point1;
				polar1M->r=recorre[u][j]->sig->r;
				polar1M->t=recorre[u][j]->sig->t;

			    polar1M->x=recorre[u][j]->sig->x;
				polar1M->y=recorre[u][j]->sig->y;
				polar1M->z=recorre[u][j]->sig->z;

				polar1M->indice=recorre[u][j]->sig->indice;
				polar1M->tipo=2;
				recorre[u][j]->sig->tipo=2;
				polar1M->sig=NULL;
				if (primeroL[u][j]==NULL)
				{   primeroL[u][j]=polar1M;
					recorreL[u][j]=polar1M;
                }
				else
				{   recorreL[u][j]->sig=polar1M;
                    recorreL[u][j]=polar1M;
				}
			}
			recorre[u][j]=recorre[u][j]->sig;
		}while(recorre[u][j]->sig!=primero[u][j]);

		recorreL[u][j]->sig=primeroL[u][j];	        
		recorre[u][j]=primero[u][j];
		do
		{
			i++;
			if(recorre[u][j]->tipo!=0)
			{
				polar1M=new point1;
				polar1M->r=recorre[u][j]->r;
				polar1M->t=recorre[u][j]->t;
				polar1M->x=recorre[u][j]->x;
				polar1M->y=recorre[u][j]->y;
				polar1M->z=recorre[u][j]->z;
				polar1M->tipo=5;
				polar1M->indice=recorre[u][j]->indice;
				polar1M->sig=NULL;
				if (primeroC[u][j]==NULL)
				{	primeroC[u][j]=polar1M;
	                recorreC[u][j]=polar1M;
					if(du==-1)
						pointsC++;
				}
				else
				{   recorreC[u][j]->sig=polar1M;
                    recorreC[u][j]=polar1M;
					if(du==-1)
						pointsC++;
				} 
			}
			recorre[u][j]=recorre[u][j]->sig;
		}while(recorre[u][j]->sig!=primero[u][j]);
		
		recorreC[u][j]->sig=primeroC[u][j];
		
		recorreC[u][j]=recorreC[u][j]->sig;
        int indis,recorrido=0;;
		float di;
		indis=recorreC[u][j]->indice;		
	    do
        {   recorrido++;
			A=recorreC[u][j]->r*sin(recorreC[u][j]->t)-recorreC[u][j]->sig->sig->r*sin(recorreC[u][j]->sig->sig->t);
			B=recorreC[u][j]->sig->sig->r*cos(recorreC[u][j]->sig->sig->t)-recorreC[u][j]->r*cos(recorreC[u][j]->t);
			C=recorreC[u][j]->r*recorreC[u][j]->sig->sig->r*sin(recorreC[u][j]->sig->sig->t-recorreC[u][j]->t);
			D=pow((double)recorreC[u][j]->r,2.0)+pow((double)recorreC[u][j]->sig->sig->r,2.0)-(2*recorreC[u][j]->r*recorreC[u][j]->sig->sig->r*cos(recorreC[u][j]->t-recorreC[u][j]->sig->sig->t));	      
			di=((  A*recorreC[u][j]->sig->r*cos(recorreC[u][j]->sig->t) )+ ( B*recorreC[u][j]->sig->r*sin(recorreC[u][j]->sig->t) ) +C)/sqrt(D);
			x1 = (float) (recorreC[u][j]->r*cos(recorreC[u][j]->t));
			y1 = (float) (recorreC[u][j]->r*sin(recorreC[u][j]->t));
			x2 = (float) (recorreC[u][j]->sig->r*cos(recorreC[u][j]->sig->t));
			y2 = (float) (recorreC[u][j]->sig->r*sin(recorreC[u][j]->sig->t));
			d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
			x1 = (float) (recorreC[u][j]->sig->r*cos(recorreC[u][j]->sig->t));
			y1 = (float) (recorreC[u][j]->sig->r*sin(recorreC[u][j]->sig->t));
			x2 = (float) (recorreC[u][j]->sig->sig->r*cos(recorreC[u][j]->sig->sig->t));
			y2 = (float) (recorreC[u][j]->sig->sig->r*sin(recorreC[u][j]->sig->sig->t));
			d2 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
			d = d1 + d2;		
			recorreC[u][j]->critical = (float) (d*di/2.0);   	
			recorreC[u][j]=recorreC[u][j]->sig;           
			indis=recorreC[u][j]->indice;
		}while(recorreC[u][j]->sig!=primeroC[u][j]);

		recorreC[u][j]->sig=primeroC[u][j];
		recorreC[u][j]=primeroC[u][j];
		//recorreC[u][j]=recorreC[u][j]->sig;
		menor=0.001;
		i=0;
		int cuantos=0;
		do
		{   
			indis=recorreC[u][j]->indice;
			if(fabs(recorreC[u][j]->critical)>=menor)  ///////ojo
			{
			    cuantos++;
				polar1M=new point1;
				polar1M->r=recorreC[u][j]->r;
				polar1M->t=recorreC[u][j]->t;
				polar1M->x=recorreC[u][j]->x;
				polar1M->y=recorreC[u][j]->y;
				polar1M->z=recorreC[u][j]->z;
				polar1M->tipo=5;	
				polar1M->critical=recorreC[u][j]->critical;
				polar1M->indice=recorreC[u][j]->indice;
				polar1M->sig=NULL;
				if (primeroCrit[u][j]==NULL)
				{   primeroCrit[u][j]=polar1M;
					recorreCrit[u][j]=polar1M;
					if(j==cantidad-interes||todos==1)	
					{
						critic++;
						criticos++;
						criticos_contourn++;
					}
				}
				else
				{   recorreCrit[u][j]->sig=polar1M;
					recorreCrit[u][j]=polar1M;
					if(j==cantidad-interes||todos==1)
					{						
						critic++;
						criticos++;
						criticos_contourn++;
					}
				}
				i++;		
			}
			recorreC[u][j]=recorreC[u][j]->sig;
         }while(recorreC[u][j]->sig!=primeroC[u][j]->sig);
		//printf("%d-%d-%d    ",u,j,cuantos);
		 recorreCrit[u][j]->sig=primeroCrit[u][j];
		 recorreCrit[u][j]=primeroCrit[u][j];	 
		 int gh=0;
		 cuantos=0;
		 do
         { 
			recorre[u][j]=primero[u][j];
			corresp1[u][j]=primcorr1[u][j];
			do
			{
				if(recorre[u][j]->indice==recorreCrit[u][j]->indice)
				{	recorre[u][j]->tipo=5;	
					corresp1[u][j]->tipo=5;					
					fprintf(fph,"%f %f %d\n",corresp1[u][j]->x,corresp1[u][j]->y,corresp1[u][j]->indice);
					cuantos++;
					gh++;

				}			
				recorre[u][j]=recorre[u][j]->sig;
				corresp1[u][j]=corresp1[u][j]->sig;
			}while(recorre[u][j]->sig!=primero[u][j]->sig);            
			recorreCrit[u][j]=recorreCrit[u][j]->sig;
         }while(recorreCrit[u][j]->sig!=primeroCrit[u][j]->sig);
		//corresp1[u][j]->sig=primcorr1[u][j];
		contourn[u][j]=criticos_contourn;	    
		fclose(fph);
		int l=0;
		char ghi[5];
		fph=fopen(str,"r+");
		do
		{   fscanf(fph,"%s\n",ghi);
			l++;
		}while(l<j+1);
		fseek(fph,0,SEEK_CUR);
		if(gh>=10)					
			fprintf(fph,"%d\n",gh);
		else
			fprintf(fph,"0%d\n",gh);
		fclose(fph);			
	}  

}

void buscar(int base,float &x,float &y,float &z,int turno, int j, int u)
{

	int marca=0,l;
	float h=0;
    l=0;
		corresp1[u][j]=primcorr1[u][j];
		do
		{
			if(corresp1[u][j]->indice==base)
			{	
				x = (float) (corresp1[u][j]->x);
				y = (float) (corresp1[u][j]->y);
				z = (float) (corresp1[u][j]->z);
				break;			
			}
			l++;
			if(corresp1[u][j]->indice>corresp1[u][j]->sig->indice)
				base=base-l;
			corresp1[u][j]=corresp1[u][j]->sig;
			
		}while(1);
	
}


int proyectar(float distancia,int base,int turno,int j,int p, int u)
{
	int marca=0,base2,l;
	float h=0.0000,x1,x2,y1,y2,d1;
	u=u+p;
	if(turno==0)
	{   
		l=0;		
		corresp1[u][j]=primcorr1[u][j];			
		do
		{	
			if(corresp1[u][j]->indice==base)
			{	marca=1;
				x1 = (float) (corresp1[u][j]->x);
				y1 = (float) (corresp1[u][j]->y);								
			}
			if(marca==1)
			{
				x2 = (float) (corresp1[u][j]->x);
				y2 = (float) (corresp1[u][j]->y);
				d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));  
				h+=d1;
				x1=x2;y1=y2;

				if(h>distancia)
				{	base2=corresp1[u][j]->indice;
					break;
				}		
			}
			corresp1[u][j]=corresp1[u][j]->sig;
			if(corresp1[u][j]->sig==primcorr1[u][j])
				l++;		
		}while(1);
	}

   return base2;
}

void ordenar_vec(int *a[3],int t)
{

	for(int i=0;i<t;i++)
	{  for(int j=0;j<t-1;j++) 
       {
           if (a[0][j] > a[0][j+1]) 
           {
               int temp = a[0][j]; 
               a[0][j]= a[0][j+1];
               a[0][j+1]= temp;

			   temp = a[1][j]; 
               a[1][j]= a[1][j+1];
               a[1][j+1]= temp;

			   temp = a[2][j]; 
               a[2][j]= a[2][j+1];
               a[2][j+1]= temp;
           }
       }
   } 


}

int repetidos(int *a[3],int t)
{
    int c =0;
	for(int i=1;i<t;i++)
	{  
           if (a[0][i] == a[0][i-1]  &&  a[1][i] == a[1][i-1]) 
           {
               a[0][i-1]= 9999;
               a[1][i-1]= 9999;
			   c++;

	       }
   } 

   return c;
}


void join_correspondencia1(int j,int in, int total,int u)
{

		float x,y,z;
		int nn=0,hh=0;

		FILE *fp;	
		//fp=fopen("correspjoin.txt","a");
		
				char str[100],str1[100];
				strcpy(str,"correspjoin");
				itoa(u,str1,10);
				strcat(str,str1);
				strcat(str,"-");
				
				itoa(j,str1,10);
				strcat(str,str1);
				strcat(str,".txt");
				fp=fopen("correspjoin.txt","a");
		
		pcor[u][j]=pcor[u][j]->sig;
		pcor1[u+1][j]=pcor1[u+1][j]->sig;

		if(in==0)
		{
			pcor[u][j]=pprim[u][j];
			pcor1[u+1][j]=pprim1[u+1][j];		
		}	

		int *vectorA[3],i;
	    vectorA[0]=new int[criticos1+criticos2];		
		vectorA[1]=new int[criticos1+criticos2];		
		vectorA[2]=new int[criticos1+criticos2];		

		for(i=0;i<criticos1;i++)
		{	
			vectorA[0][i]=pcor[u][j]->indice1;
			vectorA[1][i]=pcor[u][j]->indice2;
			vectorA[2][i]=0;
			
			
			pcor[u][j]=pcor[u][j]->sig;
		}
        for(i=criticos1;i<criticos1+criticos2;i++)
		{	
			vectorA[0][i]=pcor1[u+1][j]->indice2;
			vectorA[1][i]=pcor1[u+1][j]->indice1;							
			vectorA[2][i]=-1;
			pcor1[u+1][j]=pcor1[u+1][j]->sig;
		}

		ordenar_vec(vectorA,criticos1+criticos2);
		//int s=repetidos(vectorA,criticos1+criticos2);
		//ordenar_vec(vectorA,criticos1+criticos2);
		for(i=0;i<criticos1+criticos2;i++)
		{   


			if(vectorA[2][i]==0)
			{
				buscar(vectorA[0][i],x,y,z,0,j,u);						
				fprintf(fp,"%d %f %f ",vectorA[0][i],x,y);    
				buscar(vectorA[1][i],x,y,z,0,j,u+1);									
				fprintf(fp,"%d %f %f\n",vectorA[1][i],x,y);
				
			}
			else
			{	buscar(vectorA[0][i],x,y,z,0,j,u+1);						
				fprintf(fp,"%d %f %f ",vectorA[0][i],x,y);    			
				buscar(vectorA[1][i],x,y,z,0,j,u);						
				fprintf(fp,"%d %f %f\n",vectorA[1][i],x,y);
			}
	
			
		}


		fprintf(fp,"0 0 0 0 0 0\n");  							
		fclose(fp);
		delete[] vectorA[0];
		delete[] vectorA[1];
		delete[] vectorA[2];

}


void correspondencias(int turno,int u, int time, int j)
{
		float dd,d1,x1,x2,y1,y2;
		int base;

		if(turno==0)
		{
				pcor[u][j]=new correspon;
				pprim[u][j]=new correspon;
				pcor[u][j]=NULL;
				pprim[u][j]=NULL;
		}
		else
		{
				pcor1[u][j]=new correspon;
				pprim1[u][j]=new correspon;
				pcor1[u][j]=NULL;
				pprim1[u][j]=NULL;		
		}

	if(turno==0)
		{			
		base=0;
		corresp1[u][j]=corresp1[u][j]->sig;		
		do
		{
		ppol=new correspon;			  
		ppol->indice1=corresp1[u][j]->indice;
		ppol->indice2=base;
		x1 = (float) (corresp1[u][j]->x);
		y1 = (float) (corresp1[u][j]->y);	
		dd=0;  
		if (pprim[u][j]==NULL)
		{   pprim[u][j]=ppol;
			pcor[u][j]=ppol;               
		}
		else
		{   pcor[u][j]->sig=ppol;
			pcor[u][j]=ppol;
		}
	
		do
		{				
		corresp1[u][j]=corresp1[u][j]->sig;	
		if(corresp1[u][j]->tipo==5)
		{	x2 = (float) (corresp1[u][j]->x);
			y2 = (float) (corresp1[u][j]->y);
			d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));  
			ppol=new correspon;			  
			ppol->indice1=corresp1[u][j]->indice;
			ppol->indice2=proyectar(dd,base,turno,j,time,u);
			dd+=d1;
		    x1=x2;
			y1=y2;
			if (pprim[u][j]==NULL)
			{   pprim[u][j]=ppol;
				pcor[u][j]=ppol;               
			}
			else
			{   pcor[u][j]->sig=ppol;
				pcor[u][j]=ppol;
			}

		}
		else
		{	x2 = (float) (corresp1[u][j]->x);
			y2 = (float) (corresp1[u][j]->y);
			d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));  
			dd+=d1;
			x1=x2;
			y1=y2;					
		}		
				
		}while(corresp1[u][j]->indice<corresp1[u][j]->sig->indice);		
		corresp1[u][j]=corresp1[u][j]->sig;
		base++;
	}while(base<v[u+1][j]);
		pcor[u][j]->sig=pprim[u][j];

	}

	else
		{			
		base=0;
		corresp1[u][j]=corresp1[u][j]->sig;	
		do
		{
		ppol=new correspon;			  
		ppol->indice2=corresp1[u][j]->indice;
		ppol->indice1=base;
		x1 = (float) (corresp1[u][j]->x);
		y1 = (float) (corresp1[u][j]->y);	
		dd=0;  
		if (pprim1[u][j]==NULL)
		{   pprim1[u][j]=ppol;
			pcor1[u][j]=ppol;               
		}
		else
		{   pcor1[u][j]->sig=ppol;
			pcor1[u][j]=ppol;
		}
	
		do
		{				
		corresp1[u][j]=corresp1[u][j]->sig;	
		if(corresp1[u][j]->tipo==5)
		{	x2 = (float) (corresp1[u][j]->x);
			y2 = (float) (corresp1[u][j]->y);
			d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));  
			ppol=new correspon;			  
			ppol->indice2=corresp1[u][j]->indice;
			ppol->indice1=proyectar(dd,base,0,j,time,u);
			dd+=d1;
		    x1=x2;
			y1=y2;
			if (pprim1[u][j]==NULL)
			{   pprim1[u][j]=ppol;
				pcor1[u][j]=ppol;               
			}
			else
			{   pcor1[u][j]->sig=ppol;
				pcor1[u][j]=ppol;
			}

		}
		else
		{	x2 = (float) (corresp1[u][j]->x);
			y2 = (float) (corresp1[u][j]->y);
			d1 = (float) (sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));  
			dd+=d1;
			x1=x2;
			y1=y2;					
		}		
				
		}while(corresp1[u][j]->indice<corresp1[u][j]->sig->indice);		
		corresp1[u][j]=corresp1[u][j]->sig;

		base++;
	}while(base<v[u-1][j]);
	pcor1[u][j]->sig=pprim1[u][j];
	}

}

void mover(vtkFlRenderWindowInteractor *flrwi,int turno)
{


	if(conto+1>cant1)
		conto=0;
	conto++;
	

}



void mover_B(vtkFlRenderWindowInteractor *flrwi,int turno)
{

	if(contoB+1>cant2)
		contoB=0;	
	contoB++;

}


void quit_cb(Fl_Widget*)
{
   exit(0);
}

void quit_cb1(Fl_Widget*, void*)
{
   ventana1->hide();
}
void quit_cb2(Fl_Widget*, void*)
{
   ventana2->hide();
}
void quit_cb3(Fl_Widget*, void*)
{
   ventana3->hide();
}
void quit_cb6(Fl_Widget*, void*)
{
   //ventana6->hide();
	fgg=88888;
   ventana6->~Fl_Window();
   
}
void quit_cb5(Fl_Widget*, void*)
{
   ventana5->hide();
}


void non_main_window_callback1(Fl_Widget *w, void *flrwi)
{
   ((vtkFlRenderWindowInteractor*)flrwi)->GetRenderWindow()->WindowRemap();
 
   ((vtkFlRenderWindowInteractor*)flrwi)->Delete();
   
   delete w;

   
}
void Iniciar(int vez)
{  int u;
	du=-1;	

	todos=1;

	for(u=0;u<quant;u++)
	{
		conversion_rec_polar(0,u,vez);
		if(vez==0)
		{
		progress->value(u);       
        Fl::check();                    
        usleep(100);   
		}

	}
	for(u=0;u<quant;u++)
	{
		find_points_M(0,u,vez);
		delete[] recorre[u];
		
		delete[] recorreM[u];
        delete[] recorreL[u];
		delete[] recorreC[u];
		delete[] recorreCrit[u];

		delete[] primero[u];
        delete[] primeroC[u];
		delete[] primeroM[u];
		delete[] primeroL[u];       
		delete[] primeroCrit[u];
		if(vez==0)
		{
		progress1->value(u);       
        Fl::check();                    
        usleep(100);   
		}
	}

	}

void pintar_final(vtkFlRenderWindowInteractor *flrwi,int sec,vtkRenderer *ren1,int inter, int VENT)
{   int h=0,borrar=1,hh=0,gr=0;
    todos=0;
	sec=1;	
	for(int u=0;u<combo->value()+1;u++)
	{
		dibujar_arbol(ren1,74,74,74,(u)+(h*DESP_Y),u,h*DESP_X,0,0,5,VENT,inter);
		h++;
	}

}

void pintar4(vtkFlRenderWindowInteractor *flrwi,int sec, int ventana)
{   
	
	todos=1;
	int u=interes1;
	
		dibujar_contorno_total(renglob,74,74,74,0,flrwi,sec,0,u,0,ventana,0);
	
	
}
void pintar6(vtkFlRenderWindowInteractor *flrwi,int sec, int ventana)
{   
	
	todos=1;
	int u=interes1;
	final_correspondence();
	dibujar_contorno_total_vector(renglobVec,74,74,74,0,flrwi,sec,0,u,0,ventana,0);
	
	
}


void create_LV(vtkFlRenderWindowInteractor *flrwi,int turno, int pp)
{
 	
	if(turno==0)
	{
		renglob4 = vtkRenderer::New();
		renglob4->SetBackground(0,0,0);
		vtkRenderWindow *renWindow = vtkRenderWindow::New();
		renWindow->AddRenderer(renglob4);
		flrwi->SetRenderWindow(renWindow);
		flrwi->Initialize();

	}
    interes1=pp;
	DESP_X=150;
	DESP_Y=75;
  	arbol(1);
}


void create_LV_3(vtkFlRenderWindowInteractor *flrwi,int turno, int pp)
{
		vtkCamera *aCamera = vtkCamera::New();

		renglob = vtkRenderer::New();
		renglob->SetBackground(0,0,0);
		vtkRenderWindow *renWindow2 = vtkRenderWindow::New();
		renWindow2->AddRenderer(renglob);

		flrwi->SetRenderWindow(renWindow2);
		flrwi->Initialize();
		pintar4(flrwi,0,1); 
}

void create_LV_6(vtkFlRenderWindowInteractor *flrwi,int turno, int pp)
{
		vtkCamera *aCamera = vtkCamera::New();

		renglobVec = vtkRenderer::New();
		renglobVec->SetBackground(0,0,0);
		vtkRenderWindow *renWindow2 = vtkRenderWindow::New();
		renWindow2->AddRenderer(renglobVec);

		flrwi->SetRenderWindow(renWindow2);
		flrwi->Initialize();
		pintar6(flrwi,0,2); 
}

void create_LV1(vtkFlRenderWindowInteractor *flrwi)
{
		renglob3 = vtkRenderer::New();
		renglob3->SetBackground(0,0,0);
		vtkRenderWindow *renWindow = vtkRenderWindow::New();
		renWindow->AddRenderer(renglob3);
		flrwi->SetRenderWindow(renWindow);
		flrwi->Initialize();
}

void create_LV2(vtkFlRenderWindowInteractor *flrwi)
{
		renglob10 = vtkRenderer::New();
		renglob10->SetBackground(0,0,0);
		vtkRenderWindow *renWindow = vtkRenderWindow::New();
		renWindow->AddRenderer(renglob10);
		flrwi->SetRenderWindow(renWindow);
		flrwi->Initialize();		
}

void back_A(Fl_Widget* o, void* v)
{
  Fl_Slider *menu = static_cast<Fl_Slider *>(o);
  Fl_Window *w = (Fl_Window*)v;
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
  contoA=menu->value();
  dibujar_criticos();
  char *s1,s2[10],*s3;
  s1=new char[50];
  s3=new char[50];
  itoa(contoA+1,s2,10);
  strcpy(s1," Contorno: ");
  strcat(s1,s2);
  box_contorno->label(s1);
  itoa(crit_dibuj,s2,10);
  strcpy(s3," Puntos Criticos: ");
  strcat(s3,s2);
  box_criticos->label(s3);
  w->redraw();
  
}


void forward_A(Fl_Widget* o, void* v)
{
   vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
   mover(flrwi,0);
}



void back_B(Fl_Widget* o, void* v)
{
  Fl_Window *w = (Fl_Window*)v;
  Fl_Slider *menu = static_cast<Fl_Slider *>(o);
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
  contoB=menu->value();	
  dibujar_criticos();
  char *s1,*s3,s2[10];
  s1=new char[50];
  s3=new char[50];
  itoa(contoB+1,s2,10);
  strcpy(s1," Tiempo: ");
  strcat(s1,s2);
  box_tiempo->label(s1);
  itoa(crit_dibuj,s2,10);
  strcpy(s3," Puntos Criticos: ");
  strcat(s3,s2);
  box_criticos->label(s3);
  w->redraw();
}


void back_B1(Fl_Widget* o, void* v)
{
  Fl_Window *w = (Fl_Window*)v;
  Fl_Slider *menu = static_cast<Fl_Slider *>(o);
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
  int r=menu->value();	
  renglob12->RemoveActor(contornoActorE);
  renglob12->RemoveActor(contornoActorH);
  w->redraw();
  
  pintar_final(flrwi,0,renglob12,r,6);  
  pintar_final_correspondence(flrwi,renglob12,6,r);
  

}

void back_B2(Fl_Widget* o, void* v)
{
  Fl_Window *w = (Fl_Window*)v;
  Fl_Slider *menu = static_cast<Fl_Slider *>(o);
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
  int r=menu->value();	  
  renglob13->RemoveActor(contornoActorF);
  renglob13->RemoveActor(contornoActorI);
	w->redraw();
  pintar_final(flrwi,0,renglob13,r,7);
  pintar_final_correspondence(flrwi,renglob13,7,r);
}

void back_B3(Fl_Widget* o, void* v)
{
  Fl_Window *w = (Fl_Window*)v;
  Fl_Slider *menu = static_cast<Fl_Slider *>(o);
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)v;
  int r=menu->value();	
  
  renglob14->RemoveActor(contornoActorG);
  renglob13->RemoveActor(contornoActorJ);
  w->redraw();
  pintar_final(flrwi,0,renglob14,r,8);
  pintar_final_correspondence(flrwi,renglob14,8,r);
}
void deletionProcess(int u,int turno,int interesting)
{
	float *rho,*theta,*distance,d1,d2,x,y,z,x1,y1,x2,y2,x3,y3;
	double *critical1,*critical2;
	double menor,may;//0.00003;
	int j;int inte=interesting;
	rho=new float[mej[u][inte]];
	theta=new float[mej[u][inte]];
	distance=new float[mej[u][inte]];
	critical1=new double[mej[u][inte]];					
	critical2=new double[mej[u][inte]];					
	int ya=0,borrar;
	int obj=mej[u][inte]/2;
	do
	{
	ordenar1(bestX,bestY,u,mej[u][inte],interesting);	
	if(ya==1)
		mej[u][inte]--;
	ya=1;
	for(j=1;j<mej[u][inte]-1;j++)
	{	
		buscar(bestX[u][inte][j-1],x1,y1,z,0,interesting,u);																				
		buscar(bestX[u][inte][j],x,y,z,0,interesting,u);
		buscar(bestX[u][inte][j+1],x2,y2,z,0,interesting,u);
		/*
		x1=bestXx[u][inte][j-1];
		y1=bestXy[u][inte][j-1];

		x=bestXx[u][inte][j];
		y=bestXy[u][inte][j];
		
		x2=bestXx[u][inte][j+1];
		y2=bestXy[u][inte][j+1];
		*/




		d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
		x3=(x1+x2)/2;
		y3=(y1+y2)/2;
		d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
		critical1[j]=(d1*d2)/2;		

		buscar(bestY[u][inte][j-1],x1,y1,z,0,interesting,u);																				
		buscar(bestY[u][inte][j],x,y,z,0,interesting,u);
		buscar(bestY[u][inte][j+1],x2,y2,z,0,interesting,u);
/*
		x1=bestYx[u][inte][j-1];
		y1=bestYy[u][inte][j-1];

		x=bestYx[u][inte][j];
		y=bestYy[u][inte][j];
		
		x2=bestYx[u][inte][j+1];
		y2=bestYy[u][inte][j+1];
*/
		
		
		d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
		x3=(x1+x2)/2;
		y3=(y1+y2)/2;
		d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
		critical2[j]=(d1*d2)/2;

	}
	
	buscar(bestX[u][inte][mej[u][inte]-1],x1,y1,z,0,interesting,u);																				
	buscar(bestX[u][inte][0],x,y,z,0,interesting,u);
	buscar(bestX[u][inte][1],x2,y2,z,0,interesting,u);
		/*
		x1=bestXx[u][inte][mej[u][inte]-1];
		y1=bestXy[u][inte][mej[u][inte]-1];

		x=bestXx[u][inte][0];
		y=bestXy[u][inte][0];
		
		x2=bestXx[u][inte][1];
		y2=bestXy[u][inte][1];
*/


	d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
	x3=(x1+x2)/2;
	y3=(y1+y2)/2;
	d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
	critical1[0]=(d1*d2)/2;			

	
	buscar(bestX[u][inte][mej[u][inte]-2],x1,y1,z,0,interesting,u);																				
	buscar(bestX[u][inte][mej[u][inte]-1],x,y,z,0,interesting,u);
	buscar(bestX[u][inte][0],x2,y2,z,0,interesting,u);
	
/*
		x1=bestXx[u][inte][mej[u][inte]-2];
		y1=bestXy[u][inte][mej[u][inte]-2];

		x=bestXx[u][inte][mej[u][inte]-1];
		y=bestXy[u][inte][mej[u][inte]-1];
		
		x2=bestXx[u][inte][0];
		y2=bestXy[u][inte][0];
*/
	d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
	x3=(x1+x2)/2;
	y3=(y1+y2)/2;
	d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
	critical1[mej[u][inte]-1]=(d1*d2)/2;			

	buscar(bestY[u][inte][mej[u][inte]-1],x1,y1,z,0,interesting,u);																				
	buscar(bestY[u][inte][0],x,y,z,0,interesting,u);
	buscar(bestY[u][inte][1],x2,y2,z,0,interesting,u);
	/*
		x1=bestYx[u][inte][mej[u][inte]-1];
		y1=bestYy[u][inte][mej[u][inte]-1];

		x=bestYx[u][inte][0];
		y=bestYy[u][inte][0];
		
		x2=bestYx[u][inte][1];
		y2=bestYy[u][inte][1];
*/
	d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
	x3=(x1+x2)/2;
	y3=(y1+y2)/2;
	d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
	critical2[0]=(d1*d2)/2;			
	
	buscar(bestY[u][inte][mej[u][inte]-2],x1,y1,z,0,interesting,u);																				
	buscar(bestY[u][inte][mej[u][inte]-1],x,y,z,0,interesting,u);
	buscar(bestY[u][inte][0],x2,y2,z,0,interesting,u);
	
	/*	x1=bestYx[u][inte][mej[u][inte]-2];
		y1=bestYy[u][inte][mej[u][inte]-2];

		x=bestYx[u][inte][mej[u][inte]-1];
		y=bestYy[u][inte][mej[u][inte]-1];
		
		x2=bestYx[u][inte][0];
		y2=bestYy[u][inte][0];

*/

	d1=(sqrt(pow((double)x1-x2,2.0)+pow((double)y1-y2,2.0)));
	x3=(x1+x2)/2;
	y3=(y1+y2)/2;
	d2=(sqrt(pow((double)x-x3,2.0)+pow((double)y-y3,2.0)));
	critical2[mej[u][inte]-1]=(d1*d2)/2;			

	menor=90000;
	for(j=0;j<mej[u][inte];j++)
	{
		if(critical1[j]>critical2[j])
		   may=critical1[j];
		else
		   may=critical2[j];
		if(may<menor)
		{
			menor=may;
			borrar=j;
		}			
		
	}
	bestX[u][inte][borrar]=9999;
	bestY[u][inte][borrar]=9999;

	}while(mej[u][inte]>obj);

	delete[] rho;
	delete[] critical1;
	delete[] critical2;
	delete[] theta;
	delete[] distance;
}

void promediarA(int u,int interesting)
{
	FILE *fp,*fp1;
	float x,y,z,x1,y1,z1;
	int j,q,yy,qq;
	int inte=interesting;

	ordenar(bestX,u,mej[u][inte],interesting);
	ordenar(bestY,u,mej[u][inte],interesting);
	q=0;
	for(yy=0;yy<mej[u][inte];yy++)
		if(bestX[u][inte][yy]!=9999)
			q++;
	qq=0;
	for(yy=0;yy<mej[u][inte];yy++)
		if(bestY[u][inte][yy]!=9999)
			qq++;
	if(q>qq)
		q=qq;		
	fp=fopen("curvefit1.txt","w");
	fp1=fopen("curvefit2.txt","w");		
	fprintf(fp,"%d",q+2);
	fprintf(fp1,"%d",q+2);
	for(j=0;j<q;j++)
	{	if(bestX[u][inte][j]==9999||bestY[u][inte][j]==9999)
			break;
		buscar(bestX[u][inte][j],x,y,z,0,interesting,u);																		
		buscar(bestY[u][inte][j],x1,y1,z1,0,interesting,u+1);																				
		/*x=bestXx[u][inte][j];
		y=bestXy[u][inte][j];
		x1=bestYx[u][inte][j];
		y1=bestYy[u][inte][j];
*/

		fprintf(fp,"\n%f  %f",x,y);
		fprintf(fp1,"\n%f  %f",x1,y1);

	}
	for(j=0;j<3;j++)
	{		
		buscar(bestX[u][inte][j],x,y,z,0,interesting,u);																				
		buscar(bestY[u][inte][j],x1,y1,z1,0,interesting,u+1);																		
		/*bestXx[u][inte][j];
		y=bestXy[u][inte][j];
		x1=bestYx[u][inte][j];
		y1$=bestYy[u][inte][j];*/
		fprintf(fp,"\n%f  %f",x,y);
		fprintf(fp1,"\n%f  %f",x1,y1);
	}
	fclose(fp);
	fclose(fp1);

}




void niveles(int yy,void*data)
{   Fl_Window *w = (Fl_Window*)data;
	int x,op,j,u,prim,f,z,ni;
	FILE *fp;
	x=1;
	progress3->minimum(0);               
    progress3->maximum((quant-1)*cantidad);
	ni=0;
	for(f=0;f<quant-1;f++)
	{	
			pprim[f]=new pccorrs[cantidad];		
			pcor[f]=new pccorrs[cantidad];
			pprim1[f+1]=new pccorrs[cantidad];		
			pcor1[f+1]=new pccorrs[cantidad];		
		    prim=0;
			
			for(z=0;z<cantidad;z++)	
			{
        		correspondencias(0,f,1,z);	
				correspondencias(1,f+1,-1,z);	
				progress3->value(ni);       
				ni++;
				Fl::check();


			}
	}
	/*	for(f=0;f<quant-1;f++)
	{

		delete[] contourn[f];
        delete[] v[f];		
	}

		for(f=0;f<quant-1;f++)
	{
	delete[] corresp1[f];
	delete[] primcorr1[f];
	
		delete[] pprim[f];
		delete[] pcor[f];

		delete[] pprim1[f+1];
		delete[] pcor1[f+1];
	}			
*/

for(f=0;f<quant-1;f++)
	{	
		prim=0;
		for(z=0;z<cantidad;z++)	
			{
			
				if(v[f][z]>v[f+1][z])
					op=v[f][z];
				else
					op=v[f+1][z];
				char str[100],str1[100];
				strcpy(str,"correspjoin");
				itoa(f,str1,10);
				strcat(str,str1);
				strcat(str,"-");
				
				itoa(z,str1,10);
				strcat(str,str1);
				strcat(str,".txt");
				fp=fopen("correspjoin.txt","w");
				
				criticos1=contourn[f][z];
				criticos2=contourn[f+1][z];

				fprintf(fp,"%d %d\n",op,(criticos2+criticos1));
				fclose(fp);	
				for(int y=0;y<op;y++)	
					join_correspondencia1(z,y,(criticos1+criticos2),f);


			x=find_correspondence(f,z);
			deletionProcess(f,0,z);					
			promediarA(f,z);
			bsplineA(f,prim,z,niv,ruta,cantidad,carpeta,archivo,menorCont[z]);					
			prim++;		
			delete[] bestX[f][z];
			delete[] bestY[f][z];
			
			progress2->value(niv_arch);       
			niv_arch++;
			Fl::check();                    
			}

	}
	for(f=0;f<quant-1;f++)
	{

		delete[] contourn[f];
        delete[] v[f];		
	}

		for(f=0;f<quant-1;f++)
	{
	delete[] corresp1[f];
	delete[] primcorr1[f];
	
		delete[] pprim[f];
		delete[] pcor[f];

		delete[] pprim1[f+1];
		delete[] pcor1[f+1];
	}			
	/*for(u=0;u<quant-1;u++)
	{
		prim=0;
		for(j=0;j<cantidad;j++)
		{/*
			if(v[u][j]>v[u+1][j])
				op=v[u][j];
			else
				op=v[u+1][j];
			fp=fopen("correspjoin.txt","w");	
			criticos1=contourn[u][j];
			criticos2=contourn[u+1][j];

			fprintf(fp,"%d %d\n",op,(criticos2+criticos1));
			fclose(fp);	
			for(int y=0;y<op;y++)	
				join_correspondencia1(j,y,(criticos1+criticos2),u);
			
						
			bsplineA(u,prim,j,niv,ruta,cantidad,carpeta,archivo,menorCont[j]);					
			prim++;		
			delete[] bestX[u][j];
			delete[] bestY[u][j];
			progress2->value(niv_arch);       
			niv_arch++;
			Fl::check();                    
			//usleep(10);   
		}	
		/*if(u>2)
		{
		delete[] pprim[u-2];
		delete[] pcor[u-2];
		delete[] corresp1[u-2];
		delete[] primcorr1[u-2];
		delete[] pprim1[u-2];
		delete[] pcor1[u-2];
		}
/*

	}
	progress3->value(0);       
	ni++;
	Fl::check();                    
	usleep(100);   
/*
	for(f=0;f<quant-1;f++)
	{
		delete[] pprim[f];
		delete[] pcor[f];

		delete[] pprim1[f+1];
		delete[] pcor1[f+1];

		delete[] contourn[f];
        delete[] v[f];		
		
	}
*/
}

void expandir(void*data)
{

	Fl_Window *w = (Fl_Window*)data;
	int sec=0,borrar=1;
	niv_arch=1;
	for(int y=0;y<quant1-1;y++)
	{		
		niveles(y,w);    			
		todos=0;				
		niv++;
		quant--;
		Iniciar(1);		
		prime++;
		

		
	}
flbox1->label("listo");
Fl::check();                    
}

                   
void dibujar_arbol(vtkRenderer *ren,float r, float g, float b, float desp,int u, int despY,int carp,int sec,int gr,int vent,int interes_c)
{
	int i,c;
	float rr,gg,bb,x,y,z;
	int j,ii=0,*temp;	
	vtkPoints *points = vtkPoints::New();
	vtkCellArray *polys = vtkCellArray::New();
	char s1[200],s2[100],s[100];
	FILE *coords;
	interes1=u;
	itoa(interes1,s,10);		
	itoa(carp,s2,10);
	strcpy(s1,ruta);
	strcat(s1,carpeta);		
	if(carp!=0)
		strcat(s1,s2);
	strcat(s1,archivo);
	strcat(s1,s);				
	coords=fopen(s1,"r");
	
	fscanf(coords,"%d",&c);	
	
	temp=new int[cantidad];
	for(j=0;j<cantidad;j++)
		fscanf(coords,"%d\n",&temp[j]);		
	j=0;
	do
	{
       	if(j==cantidad-interes_c)
			polys->InsertNextCell(temp[j]);							
		i=0;
		int ii=0;
		do
		{
			fscanf(coords,"%f %f %f\n",&x,&y,&z);			
			if(j==cantidad-interes_c)
			{	
				if(gr==5)
					points->InsertNextPoint(u*10,y,x);//h*10,y,x
				else
					points->InsertNextPoint(x+desp,y+despY,0);
				polys->InsertCellPoint(ii);
				ii++;
			}
			i++;
		}while(i<temp[j]);
		j++;
	}while(j<cantidad);
		
	vtkPolyData *contorno = vtkPolyData::New();
	contorno->SetPoints(points);
	contorno->SetPolys(polys);
	points->Delete();
	polys->Delete();
	vtkSmoothPolyDataFilter *poligono = vtkSmoothPolyDataFilter::New();
	poligono->SetInput(contorno);	
	vtkPolyDataMapper *poligonoMapper = vtkPolyDataMapper::New();
	poligonoMapper->SetInput(poligono->GetOutput());

	switch(vent)
	{   case 1:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorC10);
				contornoActorC10	= vtkActor::New();
				contornoActorC10->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorC10->GetProperty()->SetColor(rr,gg,bb);
				contornoActorC10->GetProperty()->SetAmbient(1);
				contornoActorC10->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorC10->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorC10->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorC10);	
				contornoActorC10->Delete();
				break;
		case 2:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorA);
				contornoActorA	= vtkActor::New();
				contornoActorA->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorA->GetProperty()->SetColor(rr,gg,bb);
				contornoActorA->GetProperty()->SetAmbient(1);
				contornoActorA->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorA->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorA->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorA);	
				contornoActorA->Delete();
				break;
		case 3:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorB);
				contornoActorB	= vtkActor::New();
				contornoActorB->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorB->GetProperty()->SetColor(rr,gg,bb);
				contornoActorB->GetProperty()->SetAmbient(1);
				contornoActorB->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorB->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorB->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorB);	
				contornoActorB->Delete();
				break;
		case 4:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorC);
				contornoActorC	= vtkActor::New();
				contornoActorC->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorC->GetProperty()->SetColor(rr,gg,bb);
				contornoActorC->GetProperty()->SetAmbient(1);
				contornoActorC->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorC->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorC->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorC);	
				contornoActorC->Delete();
				break;
		case 5:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorD);
				contornoActorD	= vtkActor::New();
				contornoActorD->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorD->GetProperty()->SetColor(rr,gg,bb);
				contornoActorD->GetProperty()->SetAmbient(1);
				contornoActorD->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorD->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorD->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorD);	
				contornoActorD->Delete();
				break;
		case 6:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorE);
				contornoActorE	= vtkActor::New();
				contornoActorE->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorE->GetProperty()->SetColor(rr,gg,bb);
				contornoActorE->GetProperty()->SetAmbient(1);
				contornoActorE->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorE->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorE->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorE);	
				contornoActorE->Delete();
				break;
		case 7:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorF);
				contornoActorF	= vtkActor::New();
				contornoActorF->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorF->GetProperty()->SetColor(rr,gg,bb);
				contornoActorF->GetProperty()->SetAmbient(1);
				contornoActorF->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorF->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorF->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorF);	
				contornoActorF->Delete();
				break;
		case 8:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorG);
				contornoActorG	= vtkActor::New();
				contornoActorG->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorG->GetProperty()->SetColor(rr,gg,bb);
				contornoActorG->GetProperty()->SetAmbient(1);
				contornoActorG->GetProperty()->SetDiffuse(0);
				if(gr==5)
					contornoActorG->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorG->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorG);	
				contornoActorG->Delete();
				break;

	}

	
	poligonoMapper->Delete();
	fclose(coords);
	delete[] temp;
}


void dibujar_arbol_puntos(vtkRenderer *ren,float r, float g, float b, float desp,int u, int despY,int carp,int sec,int gr, int vent,int interes_c)
{
	int i,c;
	vtkPoints *points = vtkPoints::New();
	vtkCellArray *polys = vtkCellArray::New();
	char s1[200],s2[100],s[100];
	FILE *coords;
	interes1=u;
	itoa(interes1,s,10);		
	itoa(carp,s2,10);
	strcpy(s1,ruta);

	strcat(s1,carpeta);
	if(carp!=0)
		strcat(s1,s2);
	strcat(s1,"crit");
	strcat(s1,archivo);
	strcat(s1,s);	
	strcat(s1,"crit");	
	coords=fopen(s1,"r");				
	fscanf(coords,"%d",&c);	
	float rr,gg,bb,x,y;
	int z;
	int j,ii=0,*temp;	
	temp=new int[cantidad];
	for(j=0;j<cantidad;j++)
	{	
		fscanf(coords,"%d\n",&temp[j]);
	}
	j=0;
	do
	{
	   	if(j==cantidad-interes_c)
			polys->InsertNextCell(temp[j]);					
		i=0;
		do
		{
			fscanf(coords,"%f %f %d\n",&x,&y,&z);			
			if(j==cantidad-interes_c)
			{	
				if(gr==5)
					points->InsertNextPoint(u*10,y,x);
				else
					points->InsertNextPoint(x+desp,y+despY,0);
				polys->InsertCellPoint(i);
				crit_dibuj++;
			}
			i++;
		}while(i<temp[j]);
		j++;
	}while(j<cantidad);				
	fclose(coords);
	vtkPolyData *contorno = vtkPolyData::New();
	contorno->SetPoints(points);
	contorno->SetPolys(polys);
	points->Delete();
	polys->Delete();
	
	vtkSmoothPolyDataFilter *poligono = vtkSmoothPolyDataFilter::New();
	poligono->SetInput(contorno);
	
	vtkPolyDataMapper *poligonoMapper = vtkPolyDataMapper::New();
	poligonoMapper->SetInput(poligono->GetOutput());	
	
	switch(vent)
	{   case 1:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorC20);
				contornoActorC20	= vtkActor::New();
				contornoActorC20->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorC20->GetProperty()->SetColor(rr,gg,bb);
				contornoActorC20->GetProperty()->SetAmbient(1);
				contornoActorC20->GetProperty()->SetDiffuse(0);
				contornoActorC20->GetProperty()->SetPointSize(2);
				/*if(gr==5)
					contornoActorC20->GetProperty()->SetRepresentationToWireframe();
				else*/
					contornoActorC20->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorC20);	
				contornoActorC20->Delete();
				break;
		case 2:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorAA);
				contornoActorAA	= vtkActor::New();
				contornoActorAA->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorAA->GetProperty()->SetColor(rr,gg,bb);
				contornoActorAA->GetProperty()->SetAmbient(1);
				contornoActorAA->GetProperty()->SetDiffuse(0);
				contornoActorAA->GetProperty()->SetPointSize(2);
				/*if(gr==5)
					contornoActorAA->GetProperty()->SetRepresentationToWireframe();
				else*/
					contornoActorAA->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorAA);	
				contornoActorAA->Delete();
				break;
		case 3:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorBB);
				contornoActorBB	= vtkActor::New();
				contornoActorBB->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorBB->GetProperty()->SetColor(rr,gg,bb);
				contornoActorBB->GetProperty()->SetAmbient(1);
				contornoActorBB->GetProperty()->SetDiffuse(0);
				contornoActorBB->GetProperty()->SetPointSize(2);
				/*if(gr==5)
					contornoActorBB->GetProperty()->SetRepresentationToWireframe();
				else*/
					contornoActorBB->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorBB);	
				contornoActorBB->Delete();
				break;
		case 4:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorCC);
				contornoActorCC	= vtkActor::New();
				contornoActorCC->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorCC->GetProperty()->SetColor(rr,gg,bb);
				contornoActorCC->GetProperty()->SetAmbient(1);
				contornoActorCC->GetProperty()->SetDiffuse(0);
				contornoActorCC->GetProperty()->SetPointSize(2);
				/*if(gr==5)
					contornoActorCC->GetProperty()->SetRepresentationToWireframe();
				else*/
					contornoActorCC->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorCC);	
				contornoActorCC->Delete();
				break;
		case 5:	if(gr==0||gr==2)
					ren->RemoveActor(contornoActorD);
				contornoActorD	= vtkActor::New();
				contornoActorD->SetMapper(poligonoMapper);
				rr = r; gg = g; bb = b;
				contornoActorD->GetProperty()->SetColor(rr,gg,bb);
				contornoActorD->GetProperty()->SetAmbient(1);
				contornoActorD->GetProperty()->SetDiffuse(0);
				contornoActorD->GetProperty()->SetPointSize(2);
				if(gr==5)
					contornoActorD->GetProperty()->SetRepresentationToWireframe();
				else
					contornoActorD->GetProperty()->SetRepresentationToPoints();	
				ren->AddActor(contornoActorD);	
				contornoActorD->Delete();
				break;
	}
	
	poligonoMapper->Delete();	
	fclose(coords);
	delete[] temp;

}

void create_LV_5(vtkFlRenderWindowInteractor *flrwi,vtkFlRenderWindowInteractor *flrwi1,vtkFlRenderWindowInteractor *flrwi3,int a,int b)
{
		renglob12 = vtkRenderer::New();
		renglob12->SetBackground(0,0,0);
		vtkRenderWindow *renWindow12 = vtkRenderWindow::New();
		renWindow12->AddRenderer(renglob12);
		flrwi->SetRenderWindow(renWindow12);
		flrwi->Initialize();
if(a==1)
{
		renglob13 = vtkRenderer::New();
		renglob13->SetBackground(0,0,0);
		vtkRenderWindow *renWindow3 = vtkRenderWindow::New();
		renWindow3->AddRenderer(renglob13);
		flrwi1->SetRenderWindow(renWindow3);
		flrwi1->Initialize();
}
if(b==1)
{


		renglob14 = vtkRenderer::New();
		renglob14->SetBackground(0,0,0);
		vtkRenderWindow *renWindow14 = vtkRenderWindow::New();
		renWindow14->AddRenderer(renglob14);
		flrwi3->SetRenderWindow(renWindow14);
		flrwi3->Initialize();
}
}

void create_LV_2(vtkFlRenderWindowInteractor *flrwi,int turno, int pp)
{
 		renglob1 = vtkRenderer::New();
		renglob1->SetBackground(0,0,0);
		vtkRenderWindow *renWindow1 = vtkRenderWindow::New();
		renWindow1->AddRenderer(renglob1);
		flrwi->SetRenderWindow(renWindow1);
		flrwi->Initialize();		
        dibujar_criticos();
}

void create_window_with_rwi5(vtkFlRenderWindowInteractor *&flrwi1,vtkFlRenderWindowInteractor *&flrwi2,vtkFlRenderWindowInteractor *&flrwi3,Fl_Window *&flw,char *title)
{
    flw = new Fl_Window(655,700,title);
    Fl_Box *bb = new Fl_Box(2,2,651,696);
    bb->box(FL_ENGRAVED_BOX);
	bb->color(FL_BLACK);	

    Fl_Box *bb1 = new Fl_Box(18,23,624,154);
    bb1->box(FL_ENGRAVED_BOX);
	bb1->color(FL_WHITE);	

	flrwi1 = new vtkFlRenderWindowInteractor(20,25,600,150,NULL);

	Fl_Box *b = new Fl_Box(10,5,60,25,"Base");
	b->labelcolor(FL_WHITE);
	b->labelsize(12);




	int a,bab;
	if(cantidad==1)
	{	
		bases=1;		
		a=0;bab=0;
		flw->resize(0,0,655,300);
	}
	
	if(cantidad==2)
	{	
		bases=2;
		ecuador=1;		
		a=1;
		bab=0;
	}
	if(cantidad==3)
	{	
		apex=3;
		ecuador=2;	
		bases=1;
		a=1;
		bab=1;
	}
	if(cantidad>3)
	{
	a=1;bab=1;
	apex=cantidad*0.97;
	ecuador=cantidad/2;	
	bases=cantidad*0.03;
	}

    flrwi2 = new vtkFlRenderWindowInteractor(20,200,600,150,NULL);
	flrwi3 = new vtkFlRenderWindowInteractor(20,380,600,150,NULL);
	create_LV_5(flrwi1,flrwi2,flrwi3,a,bab);
    final_correspondence();
	
	pintar_final(flrwi1,0,renglob12,bases,6);
	pintar_final_correspondence(flrwi1,renglob12,6,bases);
	if(cantidad>1)
	{
	Fl_Box *bb2 = new Fl_Box(18,198,624,154);
    bb2->box(FL_ENGRAVED_BOX);
	bb2->color(FL_WHITE);	
	
	
	Fl_Box *c = new Fl_Box(10,175,60,25,"Ecuador");
	c->labelcolor(FL_WHITE);
	c->labelsize(12);
/*	Fl_Slider* s2 = new Fl_Value_Slider(622, 200, 20, 150); 
	s2->range(31, 60);
	s2->step(1);
	s2->callback(back_B2, flrwi2);
	s2->type(FL_VERT_NICE_SLIDER);*/

	pintar_final(flrwi2,0,renglob13,ecuador,7);
	pintar_final_correspondence(flrwi2,renglob13,7,ecuador);
		flw->resize(0,0,655,500);
	}
	if(cantidad>2)
	{
	Fl_Box *bb3 = new Fl_Box(18,378,624,154);
    bb3->box(FL_ENGRAVED_BOX);
	bb3->color(FL_WHITE);	


	Fl_Box *d = new Fl_Box(10,355,60,25,"Apex");
	d->labelcolor(FL_WHITE);
	d->labelsize(12);

	/*Fl_Slider* s3 = new Fl_Value_Slider(622, 380, 20, 150); 
	s3->range(61,cantidad);
	s3->step(1);
	s3->callback(back_B3, flrwi3);
	s3->type(FL_VERT_NICE_SLIDER);*/
	pintar_final(flrwi3,0,renglob14,apex,8);
	pintar_final_correspondence(flrwi3,renglob14,8,apex);
	flw->resize(0,0,655,700);
	}

    flw->callback(non_main_window_callback, flrwi2);   	
    
	/*Fl_Slider* sl = new Fl_Value_Slider(622, 25, 20, 150); 
	sl->range(1, 30);
	sl->step(1);
	sl->callback(back_B1, flrwi1);
	sl->type(FL_VERT_NICE_SLIDER);*/



	flw->resizable(flw);
	flw->end();   	
}

void dibujar_criticos()
{ int l=0,u=0,h=0,gr=2;
  l=contoB;
  r=contoA;
  dibujar_arbol(renglob1,74,74,74,0,l,0,u,0,gr,1,r);
  crit_dibuj=0;
  dibujar_arbol_puntos(renglob1,255,255,0,0,l,0,u,0,gr,1,r);
}



void arbol(int interes_c)
{
	int r=combo->value()+1,u=0,l,h,gr=1;h=0;
	for(u=0;u<combo->value()+1;u++)
	{			
		for(l=0;l<r;l++)
			dibujar_arbol(renglob4,74,74,74,(l*DESP_X)+(h*DESP_Y),l,h*DESP_X,u,0,gr,5,interes_c);
		h++;
		r--;
	}
	h=0;
	r=combo->value()+1;
	for(u=0;u<combo->value()+1;u++)
	{		
		for(l=0;l<r;l++)
			dibujar_arbol_puntos(renglob4,255,255,0,(l*DESP_X)+(h*DESP_Y),l,h*DESP_X,u,0,gr,5,interes_c);
		h++;
		r--;
	}
}

void final_correspondence()
{
	int i;
	float x,y;	
	FILE *fp;
	char s2[10],s1[200];
	strcpy(s1,ruta);
	strcat(s1,carpeta);

	itoa(combo->value(),s2,10);
	strcat(s1,s2);
	strcat(s1,"crit");
	strcat(s1,archivo);
	strcat(s1,"0crit");
	
	fp=fopen(s1,"r");
	fscanf(fp,"%d",&final_cant);
	float z=0.0;
	final_crit=new int[final_cant]; 
	for(int j=0;j<cantidad;j++)
	{	
		fscanf(fp,"%d\n",&final_crit[j]);		
		indice[j]=new int[final_crit[j]];		
	
	}
	j=0;
	do
	{   i=0;
		do
		{
            fscanf(fp,"%f %f %d\n",&x,&y,&indice[j][i]);	
			i++;
		}while(i<final_crit[j]);	
		
		j++;		
	}while(j<cantidad);
	fclose(fp);	
	
	FILE *coords;
	char s[200];
	int c,*temp;
	for(int ss=0;ss<combo->value()+1;ss++)
		{   
			itoa(ss,s,10);	
			strcpy(s1,ruta);
			strcat(s1,carpeta);		
			strcat(s1,archivo);
			strcat(s1,s);	
			coords=fopen(s1,"r");				
			fscanf(coords,"%d",&c);	
			temp=new int[cantidad];	
   			for(j=0;j<cantidad;j++)
				fscanf(coords,"%d\n",&temp[j]);	
			j=0;
			int rre=0;
			do
			{   puntop[ss][j][0]=new float[temp[j]];
				puntop[ss][j][1]=new float[temp[j]];
				puntop[ss][j][2]=new float[temp[j]];

				
				i=0;
				do
				{   
					fscanf(coords,"%f %f %f\n",&x,&y,&z);	
					puntop[ss][j][0][i]=x;
					puntop[ss][j][1][i]=y;
					puntop[ss][j][2][i]=z;
					i++;
				}while(i<temp[j]);	
				j++;
			}while(j<cantidad);
		}
}


void pintar_final_correspondence(vtkFlRenderWindowInteractor *flrwi,vtkRenderer *ren,int ven, int interes_c)
{

	int i,c,ss;
	char s1[200],s[200];
	FILE *coords;
	float rr,gg,bb,x,y,z,yy[16],xx[16],hh[16];
	int u,k;
	int j,ii=0,*temp;	
	rr=0;gg=255;bb=0;
	
	vtkPoints *points = vtkPoints::New();
	vtkCellArray *polys = vtkCellArray::New();
	k=0;
	int t,f=0;
	ii=0;	
	int rre=0;
		for(ss=0;ss<combo->value()+1;ss++)
		{   rre=0;
			indiceX[ss]=new float[final_crit[cantidad-interes_c]];		
			indiceY[ss]=new float[final_crit[cantidad-interes_c]];		
			for(k=0;k<cantidad;k++)
			{
				if(indice[cantidad-interes_c][rre]==k)
				{
					indiceX[ss][rre]=puntop[ss][cantidad-interes_c][0][k];
					indiceY[ss][rre]=puntop[ss][cantidad-interes_c][1][k];
					rre++;
					if(rre==final_crit[cantidad-interes_c])
					{   //k=cantidad;
						//ss=combo->value()+2;
						break;
					}
				}
			}
				if(rre-final_crit[cantidad-interes_c]<0)
					f=final_crit[cantidad-interes_c]-rre;
				else
					f=0;
		}
			/*
			itoa(ss,s,10);	
			strcpy(s1,ruta);
			strcat(s1,carpeta);		
			strcat(s1,archivo);
			strcat(s1,s);	
			coords=fopen(s1,"r");				
			fscanf(coords,"%d",&c);	
			temp=new int[cantidad];	
   			for(j=0;j<cantidad;j++)
				fscanf(coords,"%d\n",&temp[j]);	
			j=0;
			int rre=0;
			do
			{   i=0;
				do
				{
					fscanf(coords,"%f %f %f\n",&x,&y,&z);			
					if(j==cantidad-interes_c)
					{	
						if(indice[j][rre]>temp[j])
						{

							indiceX[ss][rre]=x;
							indiceY[ss][rre]=y;
							rre++;
							if(rre==final_crit[j])
								break;
						}
						else

						if(i==indice[j][rre])
						{
							indiceX[ss][rre]=x;
							indiceY[ss][rre]=y;
							rre++;
							if(rre==final_crit[j])
								break;
						}
					}
					i++;
				}while(i<temp[j]);	
				if(rre-final_crit[j]<0)
					f=final_crit[j]-rre;
				else
					f=0;

				j++;
			}while(j<cantidad);			
			fclose(coords);						
		}	
    

*/

	int cc=0,g;
	
	for(u=0;u<final_crit[cantidad-interes_c]-f;u++)
	{

		polys->InsertNextCell((combo->value()+1)*2);
		cc=0;
		for(t=0;t<combo->value()+1;t++)
		{
	
			points->InsertNextPoint(t*10,indiceY[t][u],indiceX[t][u]);														
			polys->InsertCellPoint(ii);	
		
				
			hh[cc]=t;
			yy[cc]=indiceY[t][u];
			xx[cc]=indiceX[t][u];
			cc++;
			ii++;							

		}
		
		for(g=cc-1;g>=0;g--)
		{
			points->InsertNextPoint(hh[g]*10,yy[g],xx[g]);														
			polys->InsertCellPoint(ii);	

			ii++;							
		}
		
		switch(ven)
		{
			case 6:		vtkPolyDataMapper *poligonoMapper;
						vtkSmoothPolyDataFilter *poligono;
						vtkPolyData *contorno ;
				        contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorH= vtkActor::New();
						contornoActorH->SetMapper(poligonoMapper);
						contornoActorH->GetProperty()->SetColor(rr,gg,bb);
						contornoActorH->GetProperty()->SetAmbient(1);
						contornoActorH->GetProperty()->SetDiffuse(0);
						contornoActorH->GetProperty()->SetPointSize(2);
						contornoActorH->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorH);	
						contornoActorH->Delete();	
						break;
			case 7:		contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorI= vtkActor::New();
						contornoActorI->SetMapper(poligonoMapper);
						contornoActorI->GetProperty()->SetColor(rr,gg,bb);
						contornoActorI->GetProperty()->SetAmbient(1);
						contornoActorI->GetProperty()->SetDiffuse(0);
						contornoActorI->GetProperty()->SetPointSize(2);
						contornoActorI->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorI);	
						contornoActorI->Delete();			
						break;
			case 8:		contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorJ	= vtkActor::New();
						contornoActorJ->SetMapper(poligonoMapper);
						contornoActorJ->GetProperty()->SetColor(rr,gg,bb);
						contornoActorJ->GetProperty()->SetAmbient(1);
						contornoActorJ->GetProperty()->SetDiffuse(0);
						contornoActorJ->GetProperty()->SetPointSize(2);
						contornoActorJ->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorJ);	
						contornoActorJ->Delete();									
						break;
		}
}
	/*
	
		u=final_crit[cantidad-interes_c]-1;
	
		float dify;
		int dt;

		dif=indiceX[0][0]-indiceX[0][final_crit[cantidad-interes_c]-1];
		dif1=indiceX[0][1]-indiceX[0][0];
		dify=indiceY[0][1]-indiceY[0][0];		
		dt=dif/dif1;
		for(int yt=0;yt<dt;yt++)
		{
			polys->InsertNextCell((combo->value()+1)*2);
			cc=0;
			dif1=0;
			for(t=0;t<combo->value()+1;t++)
			{
				
				dif=indiceX[t][0]-indiceX[t][final_crit[cantidad-interes_c]-1];
				dif1=indiceX[t][final_crit[cantidad-interes_c]-1]-indiceX[t][final_crit[cantidad-interes_c]-2];
				dify=indiceY[t][final_crit[cantidad-interes_c]-1]-indiceY[t][final_crit[cantidad-interes_c]-2];						
				//dify=dify*-1;	
				//dif1=dif1*-1;	
				
				points->InsertNextPoint(t*10,indiceY[t][u],indiceX[t][u]+(dif1*(yt+1)));
				polys->InsertCellPoint(ii);				
				hh[cc]=t;
				yy[cc]=indiceY[t][u];
				xx[cc]=indiceX[t][u]+(dif1*(yt+1));
				cc++;
				ii++;						
			}
			for(g=cc-1;g>=0;g--)
			{
				points->InsertNextPoint(hh[g]*10,yy[g],xx[g]);														
				polys->InsertCellPoint(ii);	
				ii++;							
			}
		
		switch(ven)
		{
			case 6:		vtkPolyDataMapper *poligonoMapper;
						vtkSmoothPolyDataFilter *poligono;
						vtkPolyData *contorno ;
				        contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorH= vtkActor::New();
						contornoActorH->SetMapper(poligonoMapper);
						contornoActorH->GetProperty()->SetColor(0,1,255);
						contornoActorH->GetProperty()->SetAmbient(1);
						contornoActorH->GetProperty()->SetDiffuse(0);
						contornoActorH->GetProperty()->SetPointSize(2);
						contornoActorH->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorH);	
						contornoActorH->Delete();	
						break;
			case 7:		contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorI= vtkActor::New();
						contornoActorI->SetMapper(poligonoMapper);
						contornoActorI->GetProperty()->SetColor(0,1,255);
						contornoActorI->GetProperty()->SetAmbient(1);
						contornoActorI->GetProperty()->SetDiffuse(0);
						contornoActorI->GetProperty()->SetPointSize(2);
						contornoActorI->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorI);	
						contornoActorI->Delete();			
						break;
			case 8:		contorno = vtkPolyData::New();
						contorno->SetPoints(points);
						contorno->SetPolys(polys);
						points->Delete();
						polys->Delete();	
						poligono = vtkSmoothPolyDataFilter::New();
						poligono->SetInput(contorno);		
						poligonoMapper = vtkPolyDataMapper::New();
						poligonoMapper->SetInput(poligono->GetOutput());
						contornoActorJ	= vtkActor::New();
						contornoActorJ->SetMapper(poligonoMapper);
						contornoActorJ->GetProperty()->SetColor(0,1,255);
						contornoActorJ->GetProperty()->SetAmbient(1);
						contornoActorJ->GetProperty()->SetDiffuse(0);
						contornoActorJ->GetProperty()->SetPointSize(2);
						contornoActorJ->GetProperty()->SetRepresentationToWireframe();
						poligonoMapper->Delete();
						ren->AddActor(contornoActorJ);	
						contornoActorJ->Delete();									
						break;
		}
		}
*/
	
	//delete[] temp;
	for(ss=0;ss<quant1;ss++)
	{
		delete[] indiceX[ss];
		delete[] indiceY[ss];
	}

}

void cb_menu1(Fl_Widget *w, void *data) {
  
  Fl_Menu_Button *menu = static_cast<Fl_Menu_Button *>(w);
  vtkFlRenderWindowInteractor *flrwi = (vtkFlRenderWindowInteractor*)data;
  if (menu->changed()) 
  {	
    interes1=menu->value();	
	first=1;	
	pintar4(flrwi,0,3);	
  }
}


void create_window_with_rwi2(vtkFlRenderWindowInteractor *&flrwi1,Fl_Window *&flw,char *title)
{
    flw = new Fl_Window(380,400,title);    
    Fl_Box *box1 = new Fl_Box(5, 5, 370,390);    
    box1->box(FL_ENGRAVED_BOX);
	box1->color(FL_BLACK);	
    Fl_Box *box2 = new Fl_Box(25, 80, 320,285);    
    box2->box(FL_ENGRAVED_BOX);
	box2->color(FL_WHITE);	
	box_tiempo= new Fl_Box(20,20,70,15,"    Tiempo: 0");
    box_tiempo->labelcolor(FL_WHITE);
	box_tiempo->labelsize(12);
	box_tiempo->align(FL_ALIGN_INSIDE);
	box_contorno= new Fl_Box(20,40,80,15,"    Contorno: 0 ");
    box_contorno->labelcolor(FL_WHITE);
	box_contorno->labelsize(12);
	box_contorno->align(FL_ALIGN_INSIDE);
	box_criticos= new Fl_Box(20,60,120,15,"     Puntos Críticos: 0");
    box_criticos->labelcolor(FL_WHITE);
	box_criticos->labelsize(12);
	box_criticos->align(FL_ALIGN_INSIDE);
	flrwi1 = new vtkFlRenderWindowInteractor(30,85,290,260,NULL);	
	s2 = new Fl_Value_Slider(30, 345, 310, 15); 
	s2->range(1, cantidad);
	s2->step(1);
	s2->callback(back_A, flrwi1);
    s2->type(FL_HOR_NICE_SLIDER);
	Fl_Slider* sl = new Fl_Value_Slider(320, 85, 20, 260); 
	sl->range(1, quant1-1);
	sl->step(1);
	sl->callback(back_B, flrwi1);
	sl->type(FL_VERT_NICE_SLIDER);
    flw->callback(non_main_window_callback1, flrwi1);     	
	flw->end();   
	flw->resizable(flw);
	
}

void butt_cbt(Fl_Widget* o, void* data)
{   
	play(renglob,fl_vtk_windowAS);
}
void butt_cbt1(Fl_Widget* o, void* data)
{   
	play2(renglobVec,fl_vtk_windowAS);
}

void create_window_with_rwi3(vtkFlRenderWindowInteractor *&flrwi3,Fl_Window *&flw, char *title)
{
    flw = new Fl_Window(310,350,title);
	flrwi3 = new vtkFlRenderWindowInteractor(10,10,290,260,NULL);
    
	
	Fl_Button *buttAA= new Fl_Button(10,270,20,20,">");
    buttAA->callback(butt_cbt, flrwi3);    
	progressA = new Fl_Progress(30,275,265,10);
    progressA->minimum(0);               
    progressA->maximum(quant1-1);
    progressA->color(FL_GREEN);

	flw->callback(non_main_window_callback1, flrwi3);  	
	flw->resizable();
	flw->end();   	
}

void create_window_with_rwi6(vtkFlRenderWindowInteractor *&flrwi3,Fl_Window *&flw, char *title)
{
    flw = new Fl_Window(310,350,title);
	flrwi3 = new vtkFlRenderWindowInteractor(10,10,290,260,NULL);    
	
	Fl_Button *buttAA= new Fl_Button(10,270,20,20,">");
    buttAA->callback(butt_cbt1, flrwi3);    
	progressB = new Fl_Progress(30,275,265,10);
    progressB->minimum(0);               
    progressB->maximum(combo->value());
    progressB->color(FL_GREEN);

	flw->callback(non_main_window_callback1, flrwi3);  	
	flw->resizable(flw);
	flw->end();   	
}


void lanzar()
{

  vtkFlRenderWindowInteractor *fl_vtk_window;
  fl_vtk_window = NULL;  
  ventana1 = NULL;    
  create_window_with_rwi(fl_vtk_window, ventana1,"LV Contourn");
  ventana1->callback(quit_cb1, fl_vtk_window);
  ventana1->show();
  fl_vtk_window->show();
  create_LV(fl_vtk_window,0,0);
  int fl_ret = Fl::run();
  fl_vtk_window->Delete();
  delete ventana1;   
}


void lanzar2()
{
  vtkFlRenderWindowInteractor *fl_vtk_window2;
  fl_vtk_window2 = NULL;  
  ventana2= NULL;    
  create_window_with_rwi2(fl_vtk_window2, ventana2,"Puntos Críticos");  
  ventana2->callback(quit_cb2, fl_vtk_window2);   
  ventana2->show();
  fl_vtk_window2->show();  
  create_LV_2(fl_vtk_window2,1,0);  
  int fl_ret = Fl::run();
  fl_vtk_window2->Delete();  
  delete ventana2;   
}


void lanzar3()
{
  
  fl_vtk_windowAS = NULL;  
  ventana3= NULL;    
  create_window_with_rwi3(fl_vtk_windowAS, ventana3,"LV Contourn");
  ventana3->callback(quit_cb3,fl_vtk_windowAS);   
  ventana3->show();
  fl_vtk_windowAS->show();
  create_LV_3(fl_vtk_windowAS,2,0);
  int fl_ret = Fl::run();
  fl_vtk_windowAS->Delete();
  delete ventana3;   
}


void lanzar6()
{
  
  fl_vtk_windowV = NULL;  
  ventana6= NULL;    
  create_window_with_rwi6(fl_vtk_windowV, ventana6,"LV Contourn");
  ventana6->callback(quit_cb6,fl_vtk_windowV);   
  ventana6->show();
  fl_vtk_windowV->show();
  create_LV_6(fl_vtk_windowV,2,0);
  int fl_ret = Fl::run();
  fl_vtk_windowV->Delete();
  delete ventana6;   
}


void lanzar4()
{
  vtkFlRenderWindowInteractor *fl_vtk_window5,*fl_vtk_window6,*fl_vtk_window7;
  fl_vtk_window5 = NULL;  
  fl_vtk_window6 = NULL;
  fl_vtk_window7 = NULL;
  ventana5= NULL;    
  create_window_with_rwi5(fl_vtk_window5,fl_vtk_window6,fl_vtk_window7, ventana5,"LV Contourn");
  ventana5->callback(quit_cb5, fl_vtk_window5);   
  ventana5->show();
  fl_vtk_window5->show();  
  int fl_ret = Fl::run();
  fl_vtk_window5->Delete();
  fl_vtk_window6->Delete();
  fl_vtk_window7->Delete();

  delete ventana5;   
}

void butt_cb(Fl_Widget *butt, void *data) {
	lanzar();
}
void butt_cb2(Fl_Widget *butt, void *data) {
	lanzar2();
}

void butt_cb5(Fl_Widget *butt, void *data) {
	lanzar3();
}

void butt_cb6(Fl_Widget *butt, void *data) {
	lanzar4();
}
void butt_cb10(Fl_Widget *butt, void *data) {
	lanzar6();
}


void butt_cb1(Fl_Widget *butt, void *data) {
   
	char x[10],f[10];		
	int r=combo->value();
	itoa(r+1,f,10);
    strcpy(x,f);
	quant=atoi(x);
	quant1=quant;

	DESP_X=	150;
	DESP_Y=	75;

    Fl_Window *w = (Fl_Window*)data;
	w->begin();              
	Fl_Box *box1= new Fl_Box(20,80,100,25,"Cargando Data");
    box1->labelcolor(FL_WHITE);
	box1->labelsize(12);

    
	Fl_Box *box2= new Fl_Box(20,110,130,25,"Calculando Ptos Criticos");
    box2->labelcolor(FL_WHITE);
	box2->labelsize(12);
	
	Fl_Box *box3= new Fl_Box(20,140,130,25,"Correspondencias");
    box3->labelcolor(FL_WHITE);
	box3->labelsize(12);

	Fl_Box *box4= new Fl_Box(20,170,130,25,"Niveles");
    box4->labelcolor(FL_WHITE);
	box4->labelsize(12);

    w->redraw(); 
    progress = new Fl_Progress(165,85,110,10);
    progress->minimum(0);               
    progress->maximum(quant1-1);
    progress->color(FL_BLUE);
    progress1 = new Fl_Progress(165,115,110,10);
    progress1->minimum(0);               
    progress1->maximum(quant1-1);
    progress1->color(FL_BLUE);
    int c=0;
	for(int i=quant1;i>1;i--)
	{     c+=(i*cantidad);
	}
	progress2 = new Fl_Progress(165,175,110,10);
    progress2->minimum(0);               
    progress2->maximum(c);
    progress2->color(FL_BLUE);

	progress3 = new Fl_Progress(165,145,110,10);   
    progress3->color(FL_BLUE);
                 
	Iniciar(0);
	expandir(w);
	w->end();   
	butt->activate();
    w->redraw();    
}

void butt_cb3(Fl_Widget* o, void* vx)
{
    Fl_Window *w = (Fl_Window*)vx;
	expandir(w);
	
}


void butt_cb4(Fl_Widget* o, void* vx)
{   
	lanzar();
}

void open_cb(Fl_Widget* , void*) {
    Fl_File_Chooser chooser(".","*",Fl_File_Chooser::SINGLE,"Title Of Chooser");	
    chooser.show();
    while(chooser.shown())
        { Fl::wait(); }
    if ( chooser.value() == NULL )
        { fprintf(stderr, "(User hit 'Cancel')\n"); return; }
    fprintf(stderr, "--------------------\n");
    fprintf(stderr, "DIRECTORY: '%s'\n", chooser.directory());
    fprintf(stderr, "    VALUE: '%s'\n", chooser.value());
    fprintf(stderr, "    COUNT: %d files selected\n", chooser.count());
	ruta1=(char *) chooser.value();

	int g=chooser.count();
//	struct direct **files;
	struct dirent **dir = NULL;

	int file_select();
	
	//dirent ***list;
	
	//input->value(d);
	char ruta2[600];
	
	FILE *coords;
		char temp[200];
	
	strcpy(ruta2,ruta1);
	int f,l=0,j=0,i;
	do
	{
	f=strlen(ruta2);
	if(l==0)
	{
		temp[j]=ruta2[f-1];
		j++;
		ruta2[f-1]='\0';
		l++;
	}
	else
	if(ruta2[f-1]!='/')
	{
		temp[j]=ruta2[f-1];
		j++;
		ruta2[f-1]='\0';
		
	}
	else
	{l++;
	ruta2[f-1]='\0';}
	if(l==2)
		break;
	}while(1);
	temp[j]='\0';
	g=strlen(temp);
	archivo[0]='/';
int tam=strlen(temp);
	for(i=1;i<tam+1;i++)
	{	archivo[i]=temp[g-1];
		g--;
	}
	archivo[i]='\0';
    printf("Archivo %s",carpeta);
j=0;l=0;
strcpy(ruta3,ruta2);
do
	{
	f=strlen(ruta2);
	if(l==0)
	{
		temp[j]=ruta2[f-1];
		j++;
		ruta2[f-1]='\0';
		l++;
	}
	else
	if(ruta2[f-1]!='/')
	{
		temp[j]=ruta2[f-1];
		j++;
		ruta2[f-1]='\0';
		
	}
	else
	{l++;
	ruta2[f-1]='\0';}
	if(l==2)
		break;
	}while(1);
	temp[j]='\0';		
	g=strlen(temp);
	carpeta[0]='/';
	tam=strlen(temp);
	for(i=1;i<tam+1;i++)
	{	carpeta[i]=temp[g-1];
		g--;
	}
	carpeta[i]='\0';
    printf("Carpeta %s",carpeta);

	Fl_File_Sort_F *sort = fl_numericsort;
	//int fl_filename_list(const char *d, dirent ***list, Fl_File_Sort_F *sort = fl_numericsort);
	int count=fl_filename_list(ruta3,&dir, sort);
	quant=quant1=count-2;
	char *d;
	d=new char[15];	
	itoa(quant,d,10);


	strcpy(ruta,ruta2);
	strcpy(temp,ruta3);
	strcat(temp,"crit");
	CreateDirectory (temp, NULL);
	for(i=1;i<=quant1;i++)
	{	itoa(i,d,10);		
		strcpy(temp,ruta);
		strcat(temp,carpeta);
		strcat(temp,d);
		if(i!=quant1)
		{	CreateDirectory (temp, NULL);
			strcat(temp,"crit");
			CreateDirectory (temp, NULL);
		}
		combo->add(d);
	}


	strcat(ruta2,carpeta);		
	strcat(ruta2,archivo);
	coords=fopen(ruta2,"r");				
	fscanf(coords,"%d",&cantidad);	
	fclose(coords);
	
	g=strlen(archivo);
	archivo[g-1]='\0';
	butt1->activate();
}

void open_cb1(Fl_Widget* , void*) {
	butt3->activate();
	butt5->activate();
	butt6->activate();
	butt7->activate();
	butt10->activate();


}

int find_correspondence(int u, int inte)
{
	int i,k,p,q,yaux,ll,tt;
	Mm=2;
	FILE *coords;

				char str[100],str1[100];
				strcpy(str,"correspjoin");
				itoa(u,str1,10);
				strcat(str,str1);
				strcat(str,"-");
				
				itoa(inte,str1,10);
				strcat(str,str1);
				strcat(str,".txt");
	//			coords=fopen(str,"r");

	coords=fopen("correspjoin.txt","r");
	fscanf(coords,"%d %d \n",&p,&q);				
	emin = 200000.0;
	R = new double*[Mm+1];
	t = new double[Mm+1];
	Rmin = new double*[Mm+1];
	tmin = new double[Mm+1];
	for(i=1;i<=Mm;i++)
	{
		R[i] = new double[Mm+1];
		Rmin[i] = new double[Mm+1];
	}
	Nn = q+5;
	bestX[u][inte] = new int[Nn];
	bestY[u][inte] = new int[Nn];
	

	
	for(int y=0;y<p;y++)
	{				
		Xx = new float[Nn];
		Xy = new float[Nn];
		Yx = new float[Nn];
		Yy = new float[Nn];
		indX = new int[Nn];
		indY = new int[Nn];				
		i=0;
		tt=0;
		do
		{
			fscanf(coords,"%d %f %f %d %f %f\n",&indX[i],&Xx[i],&Xy[i],&indY[i],&Yx[i],&Yy[i]);			
			if(indX[i]==0&&Xx[i]==0&&Xy[i]==0&&indY[i]==0&&Yx[i]==0&&Yy[i]==0)
			{
				fscanf(coords,"%d %f %f %d %f %f\n",&indX[i],&Xx[i],&Xy[i],&indY[i],&Yx[i],&Yy[i]);	
				break;
			}
			i++;
			tt++;
		}while(1);
	    tt--;
		e = LeastSquareError(Mm,tt,Xx,Xy,Yx,Yy,&Cc,t,R);
		if(e<emin)
		{
			emin = e;
			cmin = Cc;
			yaux=y;
			mej[u][inte]=tt;
			for(ll=0;ll<tt;ll++)
			{
				bestX[u][inte][ll]=indX[ll];							
				bestY[u][inte][ll]=indY[ll];	

				
			}
			for(i=1;i<=Mm;i++)
			{
				tmin[i] = t[i];
				for(k=1;k<=Mm;k++)
					Rmin[i][k] = R[i][k];
			}
		}
		delete[] Xx;
		delete[] Xy;
		delete[] Yx;
		delete[] Yy;	
		delete[] indX;	
		delete[] indY;	
		delete[] indC;	
	}
	fclose(coords);
	delete[] t;
	delete[] tmin;
	for(i=1;i<=Mm;i++)
	{
		delete[] R[i];
		delete[] Rmin[i];
	}
	return yaux;
}


int main( int argc, char *argv[] )
{

    Fl_Window win(300,480,"LV Contorun");
    win.callback(quit_cb);
    Fl_Box *box1 = new Fl_Box(5, 5, 285,465);    
    box1->box(FL_ENGRAVED_BOX);
	  box1->color(FL_BLACK);	
    Fl_Box *box = new Fl_Box(10, 10, 275,30," Directorio de Entrada:                             ");    
	  box->labelcolor(FL_WHITE);
    Fl_Button butt(182,13,100,25,"Examinar");
    butt.callback(open_cb, &win);
    butt1= new Fl_Button(180,50,100,25,"Iniciar Proceso");    
    butt1->deactivate();
	  butt1->callback(butt_cb1, &win);	
    Fl_Box *boxf = new Fl_Box(50,50,20,25,"Nº Tiempos");    
	  boxf->labelcolor(FL_WHITE);
    combo = new Fl_Choice(100, 50, 40, 25, "Tiempo:");
  	combo->callback(open_cb1,&win);
    flbox1 = new Fl_Box(100,250,20,25,"Procesando...");    
	  flbox1->labelcolor(FL_WHITE);
	  butt6=new Fl_Button (45,290,210,25,"Contorno 3-D");
    butt6->callback(butt_cb5, &win);   
	  butt6->deactivate();
	  butt3=new Fl_Button (45,320,210,25,"Ver puntos criticos");
    butt3->callback(butt_cb2, &win);
  	butt3->deactivate();
	  butt5=new Fl_Button (45,350,210,25,"Ver Arbol de Correspondencias");
    butt5->callback(butt_cb4,&win);
	  butt5->deactivate();
	  butt7=new Fl_Button (45,380,210,25,"Correspondencia Final");
    butt7->callback(butt_cb6,&win);
	  butt7->deactivate();
	  butt10=new Fl_Button(45,410,210,25,"Vector Correspondencias");
    butt10->callback(butt_cb10,&win);
	  butt10->deactivate();
    win.show();
    return(Fl::run());
}
