#include "Forex.cpp"



class Swap: public Deal{

public:
	string id;
	int notional;
	float fixed_leg;
	int tenor;
	char currency;

	Swap(){
		id="";
		notional=0;
		fixed_leg=0;
		tenor=0;
		currency='F';

	}

	Swap(string id, string currency, string notional,string fl,string tenor,string position){
      this->id=id;
      this->currency=currency.at(0);
      this->notional=stoi(notional);
      this->fixed_leg=stof(fl);
      this->tenor=stoi(tenor);
      this->position=stoi(position);
	}

	  friend ostream &operator<<( ostream &output,
	                                         const Swap &D )
	        {
	           //output << "Timestamp : " << D.timestamp << " Price : " << D.price <<" Unit : " << D.units<<endl;
		  output << "S: "<<D.id << "," <<D.currency<<","<< D.notional << ","<< D.fixed_leg << "," <<D.tenor<<","<< D.position<<endl;
	           return output;
	        }

};
