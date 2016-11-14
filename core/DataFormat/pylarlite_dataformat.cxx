#include <boost/python.hpp>
using namespace boost::python;

//class name defs
#include "storage_manager.h"
using namespace larlite;

BOOST_PYTHON_MODULE(larlite)
{
    class_<storage_manager>("storage_manager")
        .def("set_data_to_read", &storage_manager::set_data_to_read)
        .def("set_data_to_write", &storage_manager::set_data_to_write)
        .def("set_io_mode", &storage_manager::set_io_mode)
        .def("add_in_filename", &storage_manager::add_in_filename)
        .def("set_in_rootdir", &storage_manager::set_in_rootdir)
        .def("set_out_rootdir", &storage_manager::set_out_rootdir)
        .def("set_rootdir", &storage_manager::set_rootdir)
        .def("set_out_filename", &storage_manager::set_out_filename)
        .def("enable_event_alignment", &storage_manager::enable_event_alignment)
        .def("io_mode", &storage_manager::io_mode)
        .def("input_filename", &storage_manager::input_filename)
        .def("output_filename", &storage_manager::output_filename)
        .def("status", &storage_manager::status)
        .def("reset", &storage_manager::reset)
        .def("open", &storage_manager::open)
        .def("is_open", &storage_manager::is_open)
        .def("is_ready_io", &storage_manager::is_ready_io)
        .def("next_event", &storage_manager::next_event)
        .def("go_to", &storage_manager::go_to)
        .def("close", &storage_manager::close)
        .def("set_id", &storage_manager::set_id)
        .def("event_id", &storage_manager::event_id)
        .def("run_id", &storage_manager::run_id)
        .def("subrun_id", &storage_manager::subrun_id)
    ;
}
