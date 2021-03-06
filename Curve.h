/*
 * Curve.h
 *
 *  Created on: Mar 6, 2015
 *      Author: wangchengbin
 */

#ifndef CURVE_H_
#define CURVE_H_

#include <iostream>
#include <string>
#include <random>
#include "Utils.cpp"
#include "Logging.cpp"
using namespace std;

class Curve {

public:

	float alpha;
	float sigma;
	float beta1;
	float beta2;
	float beta3;
	float beta4;
	float lamda1;
	float lamda2;

	 float beta1_i;
	 float beta2_i;
	 float beta3_i;
	 float beta4_i;
	 float lamda1_i;
	 float lamda2_i;

	 float Drift;
	 float Volatility;
	 float r0;

	char currency;
	double dt;
	std::default_random_engine generator;
	normal_distribution<double> beta1_dist;
	normal_distribution<double> beta2_dist;
	normal_distribution<double> beta3_dist;
	normal_distribution<double> beta4_dist;
	normal_distribution<double> lamda1_dist;
	normal_distribution<double> lamda2_dist;

	std::normal_distribution<double> std_dist;

	//log4cpp::Category&  root=InitLogging::getRoot();

    Curve();
	Curve(char currency) ;
	void reset();
	void rolling();
	double  getYield(double ti);
	double  getFxRate(float t);


};

#endif /* CURVE_H_ */
