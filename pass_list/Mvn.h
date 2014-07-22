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
#include "boost/python.hpp"
#include "boost/python/stl_iterator.hpp"

using namespace std;
using namespace boost::python;
const double PI = 3.141592653589793238463;

template<typename T> vector<T> list_to_vector(list list)
{
	int n = extract<int>(list.attr("__len__")());
	vector<T> vec(n);
	std::copy(stl_input_iterator<T>(list), stl_input_iterator<T>(), vec.begin());
	return vec;
}

class Mvn {
	int ndim;
	vector<double> means;
	vector<double> stdevs;
public:
	Mvn(vector<double> means, vector<double> stdevs) {
		this->ndim = means.size();
		this->means = means;
		this->stdevs = stdevs;
	}

	Mvn(list means, list stdevs) {
		this->ndim = extract<int>(means.attr("__len__")());
//		this->means = vector<double>(this->ndim);
//		this->stdevs = vector<double>(this->ndim);
//		std::copy(stl_input_iterator<T>(list), stl_input_iterator<T>(), vec.begin());
		this->means = list_to_vector<double>(means);
		this->stdevs = list_to_vector<double>(stdevs);

		}

	double pdf(vector<double> x) {
		double a = 1.0;
		double b = 0.0;
		for (int i=0; i<ndim; ++i) {
			a *= stdevs[i];
			b -= (x[i] - means[i]) * (x[i] - means[i]) / (2 * stdevs[i] * stdevs[i]);
		}
		double res = pow(2 * PI, -ndim * 0.5) / a * exp(b);
		return res;
	}
};



#endif /* MVN_H_ */
