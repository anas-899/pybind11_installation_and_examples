/*cppimport
<%
setup_pybind11(cfg)
%>
*/
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

double my_func(int x, float y, double z) {
	return (float)x*y*z;
}

PYBIND11_MODULE(vectorizefunction, m) {
	m.def("vectorized_func", py::vectorize(my_func));
}