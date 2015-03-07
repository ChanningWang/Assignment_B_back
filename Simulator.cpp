#include "DataLoader.cpp"



class Simulator {
public:

	float recovery_rate;
	float flat_rate;
	float initialExchangeRate;
	int CounterParty_Number;
	int Forex_Number;
	int Swap_Number;
	string Reset;
	int Path;
	float Simulation_Horizon;

	float STEP = 0;
	float dt = 0;

	vector<float> cva;
	Curve curve_u;
	Curve curve_e;
	vector<double> curve_u_vector;
	vector<double> curve_e_vector;

	Simulator() {

		recovery_rate = stof(Utils::getParam("Config.txt", "recovery_rate"));
		flat_rate = stof(Utils::getParam("Config.txt", "flat_rate"));
		initialExchangeRate = stof(Utils::getParam("Config.txt", "EUR/USD"));
		CounterParty_Number = stoi(
				Utils::getParam("Config.txt", "CounterParty_Number"));
		Forex_Number = stoi(Utils::getParam("Config.txt", "Forex_Number"));
		Swap_Number = stoi(Utils::getParam("Config.txt", "Swap_Number"));
		Reset = Utils::getParam("Config.txt", "Reset");
		Path = stoi(Utils::getParam("Config.txt", "Path"));
		Simulation_Horizon = stof(
				Utils::getParam("Config.txt", "Simulation_Horizon"));

		cva.resize(CounterParty_Number);

		if (boost::iequals(Reset, "Monthly")) {
			STEP = Simulation_Horizon * 12;
			dt = 1.0 / 12;
		} else if (boost::iequals(Reset, "Daily")) {
			STEP = Simulation_Horizon * 365;
			dt = 1.0 / 365;
		}

		curve_u=Curve('U');
		curve_e=Curve('E');

		curve_u_vector.resize(STEP);
		curve_e_vector.resize(STEP);

		 std::ostringstream os;
		os << "---Initializing Simulator--" << endl;
		os << "recovery_rate=" << recovery_rate << endl;
		os << "flat_rate=" << flat_rate << endl;
		os << "initialExchangeRate=" << initialExchangeRate << endl;
		os << "CounterParty_Number=" << CounterParty_Number << endl;
		os << "Forex_Number=" << Forex_Number << endl;
		os << "Swap_Number=" << Swap_Number << endl;
		os << "Reset=" << Reset << endl;
		os << "Path=" << Path << endl;
		os << "Simulation_Horizon=" << Simulation_Horizon << endl;

		Utils::log(os.str());



	}


	double calCVA(vector<CounterParty> & cp_vector){
		double bank_cva=0;
		double cva_value=0;
		for(int i=1;i<=cp_vector.size();i++){
			cva_value=cvaForCounterParty(cp_vector[i-1]);
			cva.push_back(cva_value);
			bank_cva+=cva_value;
		}
		return bank_cva/cp_vector.size();

	}

	double cvaForCounterParty(CounterParty cp){
		vector<double> netting_step;
		vector<double> default_step;
		double cva=0;
		double value=0;

		for(int st=1;st<=STEP;st++){
			value=nettingFromStep(st, cp);
			//cout<<"step-"<<st<<" ="<<value<<endl;
			 std::ostringstream os;
			 os<<"CounterParty ID="<<cp.id<<"  :  netting set="<<value<<" at step="<<st<<endl;
			 Utils::log(os.str());
			netting_step.push_back(value);
		}
		for(int st=0;st<=STEP;st++){
			default_step.push_back(exp(-1.0*dt*st*cp.hazard_rate));
		}
		for(int st=1;st<=STEP;st++){
			 cva+=(default_step[st-1]-default_step[st])*netting_step[st-1]*pow(1+flat_rate,-st*dt);
	     }

		return cva*(1-recovery_rate);
	}

	double nettingFromStep(int st, CounterParty cp){
		double netting_path=0;
         for(int path=1;path<=Path;path++){
        	 curve_e.reset();
        	 curve_u.reset();

			for (int st = 1; st <= STEP; st++) {
				curve_e.rolling();
				curve_u.rolling();
				curve_e_vector[st - 1] = curve_e.getYield(st * dt);
				//cout<<curve_e_vector[st - 1]<<",";
				curve_u_vector[st - 1] = curve_u.getYield(st * dt);
			}
			//cout<<endl;
              netting_path+=(nettingFromStepAndPath(st,path,cp));
         }
         return netting_path/Path;

	}

	double nettingFromStepAndPath(int st,int path, CounterParty cp) {
		double value=0;

           for(int j=0;j<cp.fxs.size();j++){
        	   //cout<<"FX"<<j<<"="<<fxValue(st,cp.fxs[j])<<endl;
              value+=(fxValue(st,cp.fxs[j]));
           }
           for(int j=0;j<cp.swaps.size();j++){
        	  // cout<<"Swap"<<j<<"="<<swapValue(st,cp.swaps[j])<<endl;
              value+=(swapValue(st,cp.swaps[j]));
            }

		return value;
	}

	double fxValue(int st, Forex fx) {

		double value =fx.position*(curve_u.getFxRate(st*dt)-initialExchangeRate)*fx.nominal;
		return value;
	}

	double swapValue(int st, Swap swap) {
       double value=0;
       double fixed_part=0;

       if(swap.currency=='U'){
    	   for(int m=st+1;m<=min(STEP,swap.tenor/dt);m++){
    		  // cout<<"m="<<m<<", "<<curve_u_vector[m-1]<<endl;
    		   fixed_part+=1.0*swap.fixed_leg*pow(1+curve_u_vector[m-1],-(m*dt));
    	   }
    	   fixed_part+=1.0*pow(1+curve_u_vector[STEP-1],-st*STEP);
    	  // value=(fixed_part-1.0)*swap.notional*pow(1+curve_u_vector[st-1],st*dt);

       }else{
    	   for(int m=st+1;m<=min(STEP,swap.tenor/dt);m++){
    	      		   fixed_part+=1.0*swap.fixed_leg*pow(1+curve_e_vector[m-1],-(m*dt));
    	      	   }
    	      	   fixed_part+=1.0*pow(1+curve_e_vector[STEP-1],-st*STEP);
       }

       value=swap.position*(fixed_part-1.0)*swap.notional*pow(1+curve_u_vector[st-1],st*dt);
	   return value;
	}






};
