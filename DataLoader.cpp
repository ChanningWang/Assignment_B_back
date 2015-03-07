#include "CounterParty.cpp"
#include <string>
#include "Curve.cpp"

using namespace std;
class DataLoader {

public:


	int CounterParty_Number;
	int Forex_Number;
	int Swap_Number;


	vector<double> cva_vector;
	vector<CounterParty> cp_vector;
	vector<Forex> fx_vector;
	vector<Swap> swap_vector;

	DataLoader() {

		CounterParty_Number = stoi(
				Utils::getParam("Config.txt", "CounterParty_Number"));
		Forex_Number = stoi(Utils::getParam("Config.txt", "Forex_Number"));
		Swap_Number = stoi(Utils::getParam("Config.txt", "Swap_Number"));

	}

	void loadCounterParty() {
		string line;

		std::ifstream fileStream("CounterParty.txt");
		std::vector<string> strs;
		CounterParty cp;

		while (getline(fileStream, line, '\n')) {
			trim(line);
			boost::split(strs, line, boost::is_any_of(","));
			cp = CounterParty(strs[0], strs[2]);
			cp_vector.push_back(cp);
		}

	}

	void loadFX() {
		string line;

		std::ifstream fileStream("FX.txt");
		std::vector<string> strs;
		Forex fx;

		while (getline(fileStream, line, '\n')) {
			trim(line);
			boost::split(strs, line, boost::is_any_of(","));
			fx = Forex(strs[0], strs[1],strs[2]);
			fx_vector.push_back(fx);
		}

	}
	void loadSwap() {
		string line;

		std::ifstream fileStream("Swap.txt");
		std::vector<string> strs;
		Swap swap;

		while (getline(fileStream, line, '\n')) {
			trim(line);
			boost::split(strs, line, boost::is_any_of(","));
			swap = Swap(strs[0], strs[1],strs[2],strs[3],strs[4],strs[5]);
			swap_vector.push_back(swap);
		}

	}

	void loadMapping() {

		string line;

				std::ifstream fileStream("DealMap.txt");
				std::vector<string> strs;

				while (getline(fileStream, line, '\n')) {
					trim(line);
					boost::split(strs, line, boost::is_any_of(","));
					if(boost::iequals(strs[2], "F")){
						cp_vector[stoi(strs[0])].fxs.push_back(fx_vector[stoi(strs[1])]);
                       //cout<<fx_vector[stoi(strs[1])];
					}else if(boost::iequals(strs[2], "S")){
					   cp_vector[stoi(strs[0])].swaps.push_back(swap_vector[stoi(strs[1])]);
					   //cout<<swap_vector[stoi(strs[1])];
					}

				}
	}

	void loadAll() {
		this->loadCounterParty();
		this->loadFX();
		this->loadSwap();
		this->loadMapping();
	}

//	int main() {
//
//		//	Bank citi;
//		//	citi.createCounterParties("CounterParty.txt");
//		//	citi.createFX("FX.txt");
//		//	citi.createSwap("Swap.txt");
//		//	citi.createMapping("DealMap.txt");
//
//	//	Curve curve('U');
//	//	cout<<curve.getYield(0.5)<<endl;
//		//cout<<"hello"<<endl;
//
//		Simulate simulator;
//		simulator.loadCounterParty();
//		for(int i=0;i<simulator.CounterParty_Number;i++){
//			cout<<((CounterParty)simulator.cp_vector[i]).id<<","<<((CounterParty)simulator.cp_vector[i]).hazard_rate<<endl;
//		}
//
//	}

};
