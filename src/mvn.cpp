#include "mvn.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>

using namespace boost::python;
using namespace std;

BOOST_PYTHON_MODULE(Mvn)
{
	class_<Mvn>("Mvn", init< vector<double>, vector<double> >())
		.def("pdf", &Mvn::pdf)
	;

}
