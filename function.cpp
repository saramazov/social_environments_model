#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "function.h"
#include <random>

using namespace std;




double rand2() {

random_device rd;unsigned long int seed=rd();
unsigned int m_a=1664525;
unsigned int m_c=1013904223;
unsigned int m_m=pow(2,31);

double d;
int n[2];

n[0]=seed;
n[1]=(m_a*n[0]+m_c)% m_m;
seed=n[1];
d=static_cast<double>(n[1])/static_cast<double>(m_m-1);


return d;
}


int uniform(int a,int b) {

double x=rand2();
double n=a+(b-a)*x;

n=n+0.5;
int m = (int)n;

return m;
}

int bernoulli(int p){

int pu=uniform(1,100);
//cout<<pu<<" ";

if (pu<=p){
	return 1;
}
else{
	return 0;
}

}



double gauss(double mean,double sigma){

double a=mean-5.0*sigma;
double b=mean+5.0*sigma;

double x,y,f;

//MonteCarlo method

	do {
		
		x=a+(b-a)*rand2();
		
		y=rand2()/sigma;
		f=exp((-pow((x-mean),2))/(2*pow(sigma,2)));
		f=f/sigma;
		
	}while (f < y); 

return x;
}



double experiment(double** x,int i, int j,double* d,double* q,double mean_0,double mean_social,double b,int decision,int choice,int stick,double delta){


double appo1, appo2, pappo,bias;
double mu1,mu2;
int integer,selection;

if(choice==1){	
	
	if(decision==1){
		
		mu1=mean_social+b*q[j-1];
		appo1=gauss(mu1,1.0);

		mu2=mean_0;	
		appo2=gauss(mu2,1.0);
		//cout<<appo<<" ";
		//cout<<d[i]<<" ";
	
		if((appo1>=d[i])&&(appo2>=d[i])){
	
			pappo=1.0;

		}

		else if((appo1<=-d[i])&&(appo2<=-d[i])){

			pappo=0.0;

		}

		else  {
	
			if(stick==0){

				bias=q[j-1]+delta*(q[j-1])*(1-q[j-1])*(2*q[j-1]-1);
				bias=100*bias;
				bias=bias+0.5;
				integer=(int)bias;
				selection=bernoulli(integer);
				//pappo=x[i][j-1];
			
				if(selection==1){

					pappo=1.0;
		
				}

				else{

					pappo=0.0;

				}
			}
				
			else{

				pappo=x[i][j-1];
		
			}

		}
	
	}

	else{

		pappo=x[i][j-1];	

	}
}

else{

	if(decision==1){
	
		appo2=gauss(mean_0,1.0);
		//cout<<appo<<" ";
		//cout<<d[i]<<" ";
	
		if(appo2>=d[i]){

			pappo=1.0;

		}

		else if(appo2<=-d[i]){

			pappo=0.0;

		}

		else  {

			if(stick==0){

				bias=q[j-1]+delta*(q[j-1])*(1-q[j-1])*(2*q[j-1]-1);
				bias=100*bias;
				bias=bias+0.5;
				integer=(int)bias;
				selection=bernoulli(integer);
				//pappo=x[i][j-1];
			
				if(selection==1){

					pappo=1.0;
			
				}

				else{

					pappo=0.0;

				}
			}

			else{

				pappo=x[i][j-1];

			}
		}
	
	}

	else{

		pappo=x[i][j-1];	

	}

}

//cout<<pappo<<endl;
return pappo;
}



int decide_threshold(int i, int j, double* q, double** x, double alfa, double c, double q_0){

	double appo=rand2();
	double appo2=rand2();
	int decision;
	double qappo=s_curve(alfa,c,q,q_0,j);
	double qappo2=s_curve(-alfa,c,q,(1-q_0),j);


	if(x[i][j-1]==0.0){

		if(appo<=qappo){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}
	

	else{

		if(appo<=qappo2){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}

return decision;
	
}


int decide_quadratic(int i, int j, double* q, double** x){

	double appo=rand2();
	double appo2=rand2();
	int decision;
	double qappo=pow(q[j-1],2);
	double qappo2=pow((1-q[j-1]),2);


	if(x[i][j-1]==0.0){

		if(appo<=qappo){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}
	

	else{

		if(appo<=qappo2){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}

return decision;	

}


int decide_conformism(int i, int j, double* q, double** x,double a){

	double appo=rand2();
	double appo2=rand2();
	int decision;


if(appo2<=a){


	if(x[i][j-1]==0.0){

		if((q[j-1]>=0.5)&&(appo<=q[j-1])){

			decision=1;
		
		}

		else{

			decision=0;

		}	

	}
	

	else{

		if((q[j-1]<=0.5)&&(appo<=(1-q[j-1]))){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}

}


else{

	if(x[i][j-1]==0.0){

		if(appo<=q[j-1]){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}
	

	else{

		if(appo<=(1-q[j-1])){

			decision=1;

		}
	
		else{

			decision=0;

		}

	}
}

	
return decision;

}


double s_curve(double alfa,double c,double* q,double q_0,int j){

	double appo1=alfa*(q[j-1]-q_0);
	double appo2=exp(appo1);
	appo2=c*appo2;
	double value=(appo2)/(1+appo2);
	
return value;

}
