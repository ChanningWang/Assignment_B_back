#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <boost/algorithm/string.hpp>

//#include <boost/algorithm/string.hpp>
//#include "boost/random.hpp"
//#include "boost/generator_iterator.hpp"
#include <random>


using namespace std;
using namespace boost::algorithm;



class Utils{

public:

	static string getParam(string file, string key) {
		std::ifstream fileStream(file);
		string line;
		std::vector<string> strs;
		while (getline(fileStream, line, '\n')) {
			if (boost::algorithm::contains(line, key)) {
				boost::split(strs, line, boost::is_any_of("="));
				trim(strs[1]);
				return strs[1];

			}
		}
		return "";
	}

	static void log(string info){
            cout<<info<<endl;
            std::fstream fs("log.out", ios::out | ios::app | ios::binary);
		    fs << info;
		    fs.close();

	}


};
