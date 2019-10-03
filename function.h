#ifndef __function_h__
#define __function_h__

#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>

using namespace std;


double rand2();

int uniform(int a, int b);

int bernoulli(int p);

double gauss(double mean,double sigma);

double experiment(double** x,int i, int j,double* d,double* q,double mean_0,double mean_social,double b,int decision,int choice,int stick,double delta);

int decide_threshold(int i, int j, double* q, double** x, double alfa, double c, double q_0);

int decide_quadratic(int i, int j, double* q, double** x);

int decide_conformism(int i, int j, double* q, double** x,double a);

double s_curve(double alfa,double c,double* q,double q_0,int j);

#endif
