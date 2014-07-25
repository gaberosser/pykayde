/*
 * mvn.h
 *
 *  Created on: 16 May 2014
 *      Author: gabriel
 */

#ifndef MVN_H_
#define MVN_H_
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <assert.h>
#include "boost/python.hpp"

using namespace std;
using namespace boost::python;
const double PI = 3.141592653589793238463;

class Mvn {
	int ndim;
	double norm;
	vector<double> means;
	vector<double> stdevs;
public:
	Mvn(vector<double> means, vector<double> stdevs) {
		this->ndim = means.size();
		assert (stdevs.size() == this->ndim);
		this->means = means;
		this->stdevs = stdevs;
		this->norm = pow(2 * PI, -ndim * 0.5);
	}

	double pdf(vector<double> *x) {
		assert (x->size() == this->ndim);
		double a = 1.0;
		double b = 0.0;
		for (int i=0; i<ndim; ++i) {
			a *= stdevs[i];
//			b -= (x->at(i) - means[i]) * (x->at(i) - means[i]) / (2 * stdevs[i] * stdevs[i]);
            b -= pow(x->at(i) - means[i], 2) / (2 * pow(stdevs[i], 2));
		}
		return this->norm / a * exp(b);
	}
};



#endif /* MVN_H_ */
