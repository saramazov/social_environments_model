#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>
#include "function.h"


using namespace std;


int main() {

int n,t,decision,choice,appoggio,choice_decision,choice_experiment,initial,stick;
double mean_0,b,threshold,a,alfa,c,q_0,mean_social,delta;
double** x;
double* q;
double* d;
ofstream giuseppe;

cout<<"How many individuals?"<<endl;
cin>>n;

cout<<"Timesteps?"<<endl;
cin>>t;

cout<<"Threshold?"<<endl;
cin>>threshold;

cout<<"Mean of gaussian?"<<endl;
cin>>mean_0;

cout<<"Initial percentage of q? (integer number)"<<endl;
cin>>initial;

cout<<"Variable environment? 1 for yes, 0 for no"<<endl;
cin>>choice;

if(choice==1){

	cout<<"Mean of social environment?"<<endl;
	cin>>mean_social;

	cout<<"Parameter of linear mean change?"<<endl;
	cin>>b;

}

else{
	
	b=0;	
	mean_social=0;	

}

cout<<"Everyone experiments? 1 for yes, 0 for no"<<endl;
cin>>choice_experiment;

cout<<"Inconclusive experiment: stick with trait or copy at random (perhaps with conformism)? 1 for stick, 0 for copy"<<endl;
cin>>stick;

if(choice_experiment==0){

	cout<<"Decision: threshold, normal, or quadratic? 0 for threshold, 1 for normal, 2 for quadratic"<<endl;
	cin>>choice_decision;

	if(choice_decision==0){

	cout<<"Parameter alfa (exponent)?"<<endl;
	cin>>alfa;

	
	cout<<"Parameter c (coefficient)?"<<endl;
	cin>>c;


	cout<<"Parameter q_0 (threshold)?"<<endl;
	cin>>q_0;

	}


	else if(choice_decision==1){
	
	cout<<"Proportion of conformism?"<<endl;
	cin>>a;

	}

delta=0;	

}

else{

	if(stick==0){

		cout<<"Delta? (Parameter for conformism. Suggestion: use zero if not everyone expriments)"<<endl;
		cin>>delta;

	}

	else{

		delta=0;

	}

	choice_decision=-1;
	
}


q=new double[t];

for(int i=0; i<t; i++){

	q[i]=0;

}


d=new double[n];


for(int i=0; i<n; i++){

	d[i]=threshold;

}


x = new double*[n];
	for(int i = 0; i < n; i++){
		x[i] = new double[t]; 
		for(int j = 0; j < t; j++){
			x[i][j]=0.0;
		}
	}


for(int i=0; i<n; i++){

	appoggio=bernoulli(initial);		
	x[i][0] = static_cast<double>(appoggio);
	q[0]+=x[i][0];

}


q[0]=q[0]/static_cast<double>(n);


for(int j=1; j<t; j++){

	for(int i=0; i<n; i++){

		
		if(choice_decision==0){

			decision=decide_threshold(i,j,q,x,alfa,c,q_0);

		}

		else if(choice_decision==1){

			decision=decide_conformism(i,j,q,x,a);

		}

		else if(choice_decision==2){

			decision=decide_quadratic(i,j,q,x);

		}

		else{

			decision=1;
		
		}

	
		x[i][j]=experiment(x,i,j,d,q,mean_0,mean_social,b,decision,choice,stick,delta);
		
		q[j]+=x[i][j];

	}

q[j]=q[j]/static_cast<double>(n);

}

giuseppe.open("output.txt");

for(int i=0;i<t;i++){

	giuseppe<<q[i]<<endl;

}

giuseppe.close();


delete[] q;
delete[] d;

for(int i = 0; i < n; i++){

	delete[] x[i]; 
}

delete[] x;

return 0;
}
