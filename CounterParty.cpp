
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "Swap.cpp"


using namespace std;


class CounterParty{

public:

	string id;
	float hazard_rate;
	//int position; //1 represents long, -1 represents short to the counterparty
	vector<Swap> swaps;
	vector<Forex> fxs;

	CounterParty(){
       this->id="";
       this->hazard_rate=0;
	}

	CounterParty(string id){
	       this->id=id;
	       this->hazard_rate=0;
		}

	CounterParty(string id,string rate){
       this->id=id;
       this->hazard_rate=stof(rate);
	}


	friend ostream &operator<<(ostream &output, const CounterParty &D) {
		//output << "Timestamp : " << D.timestamp << " Price : " << D.price <<" Unit : " << D.units<<endl;
		output << "CounterParty: "<<D.id << "," << D.hazard_rate << D.fxs.size()<<","<< D.swaps.size()<<endl;
		for (int j = 0; j < D.fxs.size(); j++) {
			output << D.fxs[j];
		}
		for (int j = 0; j < D.swaps.size(); j++) {
			output << D.swaps[j] ;
		}

		return output;
	}










};
