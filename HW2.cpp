#include <iostream>
#include "Simulator.cpp"
//#include "Curve.cpp"
using namespace std;

int main() {

	//	Bank citi;
	//	citi.createCounterParties("CounterParty.txt");
	//	citi.createFX("FX.txt");
	//	citi.createSwap("Swap.txt");
	//	citi.createMapping("DealMap.txt");

//	Curve curve('U');
//	curve.rolling();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.rolling();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.rolling();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.reset();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.rolling();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.rolling();
//	cout<<curve.getYield(0.5)<<endl;
//	cout<<curve.getYield(1.7)<<endl;
//	curve.reset();
//		cout<<curve.getYield(0.5)<<endl;
//		cout<<curve.getYield(1.7)<<endl;
//	cout<<curve.getFxRate(1.5)<<endl;
//	cout<<curve.getFxRate(0.8)<<endl;
//	cout<<curve.getFxRate(3.4)<<endl;

//	cout<<"-----"<<endl;
//	Curve curve1('E');
//		cout<<curve1.getYield(0.5)<<endl;
//		cout<<curve1.getYield(1.7)<<endl;
//		curve1.rolling();
//			cout<<curve1.getYield(0.5)<<endl;
//			cout<<curve1.getYield(1.7)<<endl;
//			curve1.rolling();
//						cout<<curve1.getYield(0.5)<<endl;
//						cout<<curve1.getYield(1.7)<<endl;
//		cout<<curve1.getFxRate(1.5)<<endl;
//		cout<<curve1.getFxRate(0.8)<<endl;
//		cout<<curve1.getFxRate(3.4)<<endl;


//	DataLoader loader;
//			loader.loadCounterParty();
//			loader.loadFX();
//			loader.loadSwap();
//			loader.loadMapping();
//			CounterParty cp;
//
//
//
//			for (int i = 0; i < loader.CounterParty_Number; i++) {
//				cout<<loader.cp_vector[i];
//			}


	DataLoader loader;
	loader.loadAll();
	CounterParty cp1=loader.cp_vector[18];
	CounterParty cp2=loader.cp_vector[19];
//	cout<<cp1<<endl;
//	cout<<cp2<<endl;
	//cout<<"Test"<<cp2<<endl;

	Simulator simul;
//	for(int i=0;i<loader.cp_vector.size();i++){
//		cout<<simul.cvaForCounterParty(loader.cp_vector[i])<<endl;
//	}
	cout<<"Final CVA="<<simul.calCVA(loader.cp_vector);
	//cout<<simul.cvaForCounterParty(cp2)<<endl;
//	cout<<simul.cvaForCounterParty(cp2)<<endl;

	//cout<<simul.calCVA(loader.cp_vector)<<endl;
	//cout<<simul.calCVA(loader.cp_vector)<<endl;





return 0;

}
