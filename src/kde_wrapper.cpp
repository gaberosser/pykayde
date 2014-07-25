#include "boost/numpy.hpp"
#include <vector>
#include <iostream>
#include "kde.h"

namespace bp = boost::python;
namespace bn = boost::numpy;
using namespace std;

std::vector<double> myfunc(int n) {
    return vector<double>(n);
}

bn::ndarray mywrapper(int n) {
    std::vector<double> v = myfunc(n);
    Py_intptr_t shape[1] = { v.size() };
    cout << shape << endl;
    bn::ndarray result = bn::zeros(1, shape, bn::dtype::get_builtin<double>());
    std::copy(v.begin(), v.end(), reinterpret_cast<double*>(result.get_data()));
    return result;
}

int mylen(bn::ndarray arr) {
    for (int i=0; i<arr.get_nd(); ++i) {
        cout << arr.shape(i) << endl;
    }
    return arr.shape(0);
}

FixedBandwidthKde init_kde(bn::ndarray data, bn::ndarray bdwidth) {
    vector< vector<double> > vdata(data.shape(0), vector<double>(data.shape(1), 0.0));
    vector<double> vb;
    assert (bdwidth.shape(0) == data.shape(1));
}

BOOST_PYTHON_MODULE(KdeWrapper) {
    bn::initialize();
    bp::def("myfunc", mywrapper);
    bp::def("mylen", mylen);
}