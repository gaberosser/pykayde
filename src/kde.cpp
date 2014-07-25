/*
 * vbkde.cpp
 *
 *  Created on: 16 May 2014
 *      Author: gabriel
 */

#include "kde.h"
using namespace boost::python;
using namespace std;

real_2d_array vector_2d_to_array(vector<vector<double> > x) {
	// TODO: can probably just use setcontent directly on vector?
	unsigned int rows = x.size();
	unsigned int cols = x[0].size();
	real_2d_array res;
	res.setlength(rows, cols);
	double arr[rows*cols];
	for (unsigned int i=0; i<rows; ++i) {
		for (unsigned int j=0; j<cols; ++j) {
			arr[j + i*cols] = x[i][j];
		}
	}
	res.setcontent(rows, cols, arr);
	return res;
}

double st_dev(vector<double> v, bool ub=true) {
	double k = ub ? v.size() - 1 : v.size();
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
	return sqrt((sq_sum - sum * sum / double(v.size())) / k);
}

FixedBandwidthKde::FixedBandwidthKde(vector<vector <double> > data) {
	this->num_pdf_calls = 0;
	this->ndim = data[0].size();
	this->data = data;
}

FixedBandwidthKde::FixedBandwidthKde(vector<vector <double> > data, vector<double> bdwidths) {
	this->ndim = data[0].size();
	this->data = data;
	this->set_bandwidths(bdwidths);
	this->set_mvns();
}

FixedBandwidthKde::FixedBandwidthKde(vector<vector <double> > data, double bdwidth) {
	this->ndim = data.size();
	this->data = data;
	this->set_bandwidths(bdwidth);
	this->set_mvns();
}

void FixedBandwidthKde::set_bandwidths(double bdwidth) {
	this->bandwidths = vector<vector<double> >(ndata(), vector<double>(ndim, bdwidth));
	this->set_mvns();
}

void FixedBandwidthKde::set_bandwidths(vector<double> bdwidths) {
	this->bandwidths = vector<vector<double> >(ndata(), bdwidths);
	this->set_mvns();
}

void FixedBandwidthKde::set_mvns() {
	this->mvns = vector<Mvn>();
	for (int i=0; i<ndata(); ++i) {
		this->mvns.push_back(Mvn(data[i], this->bandwidths[i]));
	}
}

double FixedBandwidthKde::pdf(vector <double> x, bool normed) {
//	if (x.size() != ndim) {
//		throw exception("Input vector has wrong size");
//	}
	double res = 0;

	for (int i=0; i<ndata(); ++i) {
		res += mvns[i].pdf(&x);
		this->num_pdf_calls += 1;
	}
	if (normed) {
		res /= double(ndata());
	}
	return res;
}

vector<double> FixedBandwidthKde::pdf(vector <vector<double> > X, bool normed) {
	int nt = X.size();
	vector<double> res;
	for (int i=0; i<nt; ++i) {
		res.push_back(this->pdf(X.at(i), normed));
	}
	return res;
}

double FixedBandwidthKde::foo(vector <double> x) {
    double res = 0.0;
    for (int i=0; i<25000000; ++i) {
        res += exp(-(rand() % 50));
    }
    return res;
}

VariableBandwidthKde::VariableBandwidthKde(vector<vector <double> > data) : FixedBandwidthKde(data) {

}

void VariableBandwidthKde::set_bandwidths(int nn) {
	this->bandwidths = vector<vector<double> >(ndata(), vector<double>(ndim, 0.0));
	// normalise data according to stdev
	vector<double> stds(3, 0.0);
	for (int i=0; i<ndim; ++i) {

		vector<double> this_vec;
		for (int j=0; j<ndim; ++j) {
			this_vec.push_back(data[j][i]);
		}
		stds[i] = st_dev(this_vec);
	}

	// get bandwidths using nearest neighbours
	real_2d_array xy = vector_2d_to_array(data);
	kdtree kd;
	kdtreebuild(xy, this->ndim, 0, 2, kd);

	// iterate over each source and find NN distance
	for (int i=0; i<this->ndata(); ++i) {
		real_1d_array pt, z;
		pt.setcontent(this->ndim, &(this->data[i][0]));
		kdtreequeryknn(kd, pt, nn, false);
		kdtreequeryresultsdistances(kd, z);

	}
}

BOOST_PYTHON_MODULE(Kde)
{
	class_<FixedBandwidthKde>("FixedBandwidthKde", init< vector< vector<double> > >())
	    .def("foo", &FixedBandwidthKde::foo)
		.def("pdf", static_cast< double (FixedBandwidthKde::*)(vector<double>, bool) >(&FixedBandwidthKde::pdf))
		.def("pdf", static_cast< vector<double> (FixedBandwidthKde::*)(vector< vector<double> >, bool) >(&FixedBandwidthKde::pdf))
        .def("set_bandwidths", static_cast< void (FixedBandwidthKde::*)(double) >(&FixedBandwidthKde::set_bandwidths))
        .def("set_bandwidths", static_cast< void (FixedBandwidthKde::*)(vector<double>) >(&FixedBandwidthKde::set_bandwidths))
		.def_readonly("ndim", &FixedBandwidthKde::ndim)
		.def_readonly("num_pdf_calls", &FixedBandwidthKde::num_pdf_calls)
	;

//	class_<VariableBandwidthKde>("VariableBandwidthKde", init< vector<double>, vector<double> >())
//		.def("pdf", &VariableBandwidthKde::pdf)
//	;

}

