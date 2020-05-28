/*cppimport
<%
setup_pybind11(cfg)
%>
*/

#include <pybind11/pybind11.h>
#include <pybind11/embed.h> //scoped_interpreter
#include <string>
#include <iostream>

namespace py = pybind11;
using namespace pybind11::literals; // to bring in the `_a` literal

PYBIND11_EMBEDDED_MODULE(fast_calc, m) {
	// `m` is a `py::module` which is used to bind functions and classes
	m.def("add", [](int i, int j) {
		return i + j;
	});
}

int main() {
	//https://github.com/pybind/pybind11/blob/master/tests/test_pytypes.cpp
	py::scoped_interpreter guard{};

	// types
	auto d1 = py::dict(py::arg("x") = 1, py::arg("y") = 2);
	//auto d1 = py::dict("x"_a = 1, "y"_a = 2); 
	py::print(d1); //{'x': 1, 'y': 2}

	auto args = py::make_tuple("1", "and", "2", "values");
	py::print("*args", *args); //*args 1 and 2 values

	std::string value1 = "first";
	std::string value2 = "second";
	py::list list;
	list.append(value1);
	list.append(value2);
	py::print("Entry at position 0:", list[0]); //Entry at position 0: first
	list[0] = py::str("overwritten");
	py::print("after overwrite first item in list:", list[0]); //after overwrite first item in list : overwritten
	py::print("list_contain_second:", list.contains("second")); // list_contain_second : True

	// modules
	py::object os = py::module::import("os");
	py::object makedirs = os.attr("makedirs");
	makedirs("d:/created_from_cplusplus_by_python_os");

	auto fast_calc = py::module::import("fast_calc");
	auto result = fast_calc.attr("add")(1, 2).cast<int>();
	py::print("fast_calc resul: ", result); //fast_calc resul:  3

	py::exec(R"(
        kwargs = dict(name="World", number=42)
        message = "Hello, {name}! The answer is {number}".format(**kwargs)
        print(message)
    )"); //Hello, World!The answer is 42

	//py::object scipy = py::module::import("scipy");
	//py::print("version of scipy", scipy.attr("__version__"));
}