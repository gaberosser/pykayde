#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <vector>

using namespace boost::python;
using namespace std;

BOOST_PYTHON_MODULE(CppVector)
{
    class_<vector<double> >("VectorDouble1D")
        .def(vector_indexing_suite<vector<double> >() )
    ;

    class_<vector< vector<double> > >("VectorDouble2D")
        .def(vector_indexing_suite<vector< vector<double> > >() )
    ;
}
