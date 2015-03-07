
#include "Deal.cpp"



class Forex:public Deal{
public:
	string id;
	int nominal;
	int position;

	Forex(){
		this->id="";
		       this->nominal=0;
		       this->position=0;
	}
	Forex(string id,string nominal,string position){
       this->id=id;
       this->nominal=stoi(nominal);
       this->position=stoi(position);
	}

	  friend ostream &operator<<( ostream &output,
	                                         const Forex &D )
	        {
	           //output << "Timestamp : " << D.timestamp << " Price : " << D.price <<" Unit : " << D.units<<endl;
		      output << "F: "<<D.id << "," << D.nominal <<"," << D.position<<endl;
	           return output;
	        }

};
