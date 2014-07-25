/*
 * vbkde.h
 *
 *  Created on: 16 May 2014
 *      Author: gabriel
 */

#ifndef VBKDE_H_
#define VBKDE_H_
#include "string.h"
#include <cmath>
#include <iostream>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <vector>
#include <exception>
#include "boost/python.hpp"

#include "mvn.h"
#include "alglibmisc.h"
using namespace alglib;
using namespace std;

class FixedBandwidthKde {
public:
    int num_pdf_calls;
	vector<vector <double> > data;
	vector<vector <double> > bandwidths;
	vector<Mvn> mvns;
	int ndim;
	bool normed;
	FixedBandwidthKde(vector<vector <double> > data);
	FixedBandwidthKde(vector<vector <double> > data, vector <double> bdwidths);
	FixedBandwidthKde(vector<vector <double> > data, double bdwidth);
	void set_mvns(); // TODO move to private
	int ndata() { return data.size(); }
	double pdf(vector <double> x, bool normed);
	vector<double> pdf(vector< vector<double> > X, bool normed);
	void set_bandwidths(double bdwidth);
	void set_bandwidths(vector<double> bdwidths);
	double foo(vector <double> x);
};

class VariableBandwidthKde: public FixedBandwidthKde {
public:
	VariableBandwidthKde(vector<vector <double> > data);
	VariableBandwidthKde(vector<vector <double> > data, int nn);
	void set_bandwidths(int nn);
};



#endif /* VBKDE_H_ */
