#include "final_show.hpp"

#include "data_controller.hpp"

namespace cvv { namespace impl {

void finalShow() {
	impl::dataController().lastCall();
}

}} // namespaces cvv::impl