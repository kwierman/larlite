#include <boost/python.hpp>
using namespace boost::python;

//class name defs
#include "FrameworkConstants.h"
#include "larlite_base.h"
#include "messenger.h"
using namespace larlite;

BOOST_PYTHON_MODULE(larlite)
{
    class_<larlite_base>("larlite_base")
        .def("set_verbosity", &larlite_base::set_verbosity)
        .def("get_verbosity", &larlite_base::get_verbosity)
        .def("class_name", &larlite_base::class_name)
    ;

    class_<Message, boost::noncopyable>("Message", no_init);

    enum_<msg::Level>("Level")
    .value("kDEBUG",msg::kDEBUG)
    .value("kINFO",msg::kINFO)
    .value("kNORMAL", msg::kNORMAL)
    .value("kWARNING", msg::kWARNING)
    .value("kERROR", msg::kERROR)
    .value("kMSG_TYPE_MAX", msg::kMSG_TYPE_MAX);
}
