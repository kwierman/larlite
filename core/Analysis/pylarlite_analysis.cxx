#include <boost/python.hpp>
using namespace boost::python;

//class name defs
#include "ana_base.h"
#include "ana_processor.h"
using namespace larlite;

BOOST_PYTHON_MODULE(larlite)
{
    class_<ana_base>("ana_base")
        .def("initialize", &ana_base::initialize)
        .def("begin_run", &ana_base::begin_run)
        .def("begin_subrun", &ana_base::begin_subrun)
        .def("analyze", &ana_base::analyze)
        .def("finalize", &ana_base::finalize)
        .def("set_output_file", &ana_base::set_output_file)
    ;
    class_<ana_processor>("ana_processor")
        .def("set_verbosity", &ana_processor::set_verbosity)
        .def("add_input_file", &ana_processor::add_input_file)
        .def("set_input_rootdir", &ana_processor::set_input_rootdir)
        .def("set_output_rootdir", &ana_processor::set_output_rootdir)
        .def("set_rootdir", &ana_processor::set_rootdir)
        .def("set_output_file", &ana_processor::set_output_file)
        .def("set_ana_output_file", &ana_processor::set_ana_output_file)
        .def("set_io_mode", &ana_processor::set_io_mode)
        .def("set_data_to_read", &ana_processor::set_data_to_read)
        .def("set_data_to_write", &ana_processor::set_data_to_write)
        .def("enable_event_alignment", &ana_processor::enable_event_alignment)
        .def("get_ana_status", &ana_processor::get_ana_status)
        .def("run", &ana_processor::run)
        .def("process_event", &ana_processor::process_event)
        .def("add_process", &ana_processor::add_process)
        .def("get_process", &ana_processor::get_process)
        .def("get_process_status", &ana_processor::get_process_status)
        .def("enable_filter", &ana_processor::enable_filter)
        .def("process_event", &ana_processor::process_event)
        .def("reset", &ana_processor::reset)
    ;
}
