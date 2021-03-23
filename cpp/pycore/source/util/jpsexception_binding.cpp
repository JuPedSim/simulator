#include "jpsexception_binding.hpp"

#include "util/jpsexception.hpp"

void bind_jpsexception(pybind11::module_ & m)
{
    pybind11::register_exception<JPSException>(m, "JPSException");
    pybind11::register_exception<JPSGeometryException>(m, "JPSGeometryException");
}
