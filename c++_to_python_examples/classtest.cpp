/*cppimport
<%
setup_pybind11(cfg)
%>
*/

#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

class Pet {
public:
	Pet(const std::string& name) : name(name) { }
	void setName(const std::string& name_) { name = name_; }
	const std::string& getName() const { return name; }

private:
	std::string name;
};

PYBIND11_MODULE(classtest, m) {
	py::class_<Pet> pet_class(m, "Pet");
	pet_class
		.def(py::init<std::string>())
		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName, py::return_value_policy::copy);
	//.def_readonly("name", &Pet::name);
	//.def_readwrite("name", &Pet::name);
}