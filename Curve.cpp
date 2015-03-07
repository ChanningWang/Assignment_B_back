

#include <iostream>
#include <string>
#include <random>
#include "Utils.cpp"
//#include "Logging.cpp"
#include <sstream>
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

Curve() {

}

	Curve(char currency) {
		this->currency=currency;
		if (currency == 'U') {
			alpha = stof(Utils::getParam("Config.txt", "alpha_usd"));
			sigma = stof(Utils::getParam("Config.txt", "sigma_usd"));
			beta1 = stof(Utils::getParam("Config.txt", "beta1_usd"));
			beta2 = stof(Utils::getParam("Config.txt", "beta2_usd"));
			beta3 = stof(Utils::getParam("Config.txt", "beta3_usd"));
			beta4 = stof(Utils::getParam("Config.txt", "beta4_usd"));
			lamda1 = stof(Utils::getParam("Config.txt", "lamda1_usd"));
			lamda2 = stof(Utils::getParam("Config.txt", "lamda2_usd"));
		} else {
			alpha = stof(Utils::getParam("Config.txt", "alpha_eur"));
			sigma = stof(Utils::getParam("Config.txt", "sigma_usd"));
			beta1 = stof(Utils::getParam("Config.txt", "beta1_eur"));
			beta2 = stof(Utils::getParam("Config.txt", "beta2_eur"));
			beta3 = stof(Utils::getParam("Config.txt", "beta3_eur"));
			beta4 = stof(Utils::getParam("Config.txt", "beta4_eur"));
			lamda1 = stof(Utils::getParam("Config.txt", "lamda1_eur"));
			lamda2 = stof(Utils::getParam("Config.txt", "lamda2_eur"));

		}


		 beta1_i=beta1;
		 beta2_i=beta2;
		 beta3_i=beta3;
		 beta4_i=beta4;
		 lamda1_i=lamda1;
		 lamda2_i=lamda2;
		 if(boost::iequals("Monthly",Utils::getParam("Config.txt", "Reset"))){
            dt=1.0/12;
		 }
		 else if(boost::iequals("Daily",Utils::getParam("Config.txt", "Reset"))){
            dt=1.0/365;
		 }

		 beta1_dist=normal_distribution<double>(beta1,1);
		 beta2_dist=normal_distribution<double>(beta2,1);
		 beta3_dist=normal_distribution<double>(beta3,1);
		 beta4_dist=normal_distribution<double>(beta4,1);
		 lamda1_dist=normal_distribution<double>(lamda1,1);
		 lamda2_dist=normal_distribution<double>(lamda2,1);

		 std_dist=normal_distribution<double>(0,1);

		 Drift=stof(Utils::getParam("Config.txt", "Drift"));
		 Volatility=stof(Utils::getParam("Config.txt", "Volatility"));
		 r0=stof(Utils::getParam("Config.txt", "EUR/USD"));

		 std::ostringstream os;
		 os<<"---Initializing Curve--"<<endl;
		 os<<"Currency="<<currency<<endl;
		 os<<"Beta1="<<beta1<<endl;
		 os<<"Beta2="<<beta2<<endl;
		 os<<"Beta3="<<beta3<<endl;
		 os<<"Beta4="<<beta4<<endl;
		 os<<"lamda1="<<lamda1<<endl;
		 os<<"lamda2="<<lamda2<<endl;
		 os<<"Drift="<<Drift<<endl;
		 os<<"Volatility="<<Volatility<<endl;
		 os<<"EUR/USD="<<r0<<endl;
		// root.debug(os.str());
		 Utils::log(os.str());

     rolling();

	}

	void reset() {
		beta1_i = beta1;
		beta2_i = beta2;
		beta3_i = beta3;
		beta4_i = beta4;
		lamda1_i = lamda1;
		lamda2_i = lamda2;
		rolling();
	}

	void rolling(){

		beta1_i = alpha*(beta1-beta1_i)+sigma*sqrt(dt)*beta1_dist(generator);
		beta2_i = alpha*(beta2-beta2_i)+sigma*sqrt(dt)*beta2_dist(generator);
		beta3_i = alpha*(beta3-beta3_i)+sigma*sqrt(dt)*beta3_dist(generator);
		beta4_i = alpha*(beta4-beta4_i)+sigma*sqrt(dt)*beta4_dist(generator);
		lamda1_i = alpha*(lamda1-lamda1_i)+sigma*sqrt(dt)*lamda1_dist(generator);
		lamda2_i = alpha*(lamda2-lamda2_i)+sigma*sqrt(dt)*lamda2_dist(generator);


		//cout<<"Rolling"<<endl;
//				 cout<<"Beta1="<<beta1_i<<endl;
//				 cout<<"Beta2="<<beta2_i<<endl;
//				 cout<<"Beta3="<<beta3_i<<endl;
//				 cout<<"Beta4="<<beta4_i<<endl;
//				 cout<<"lamda1="<<lamda1_i<<endl;
//				 cout<<"lamda2="<<lamda2_i<<endl;
//


	}

	double  getYield(double ti){
		while(lamda1_i==0){
			lamda1_i=alpha*(lamda1-lamda1_i)+sigma*sqrt(dt)*lamda1_dist(generator);
		}
		while(lamda2_i==0){
			lamda2_i = alpha*(lamda2-lamda2_i)+sigma*sqrt(dt)*lamda2_dist(generator);
		}
		double param1=ti/lamda1_i;
		double param2=ti/lamda2_i;

      double value= beta1_i+beta2_i*(1-exp(-param1))/param1+beta3_i*((1-exp(-param1))/param1 - exp(-param1))+beta4_i*((1-exp(-param2))/param2 - exp(-param2));
       return abs(value);
	}


	double  getFxRate(float t){
		float dx=Volatility*sqrt(t)*std_dist(generator);
		return dx+r0;
	}

};


