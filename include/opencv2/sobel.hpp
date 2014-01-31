#ifndef CVVISUAL_DEBUG_SOBEL_HPP
#define CVVISUAL_DEBUG_SOBEL_HPP

#include <string>

#include "opencv2/core/core.hpp"

#include "call_meta_data.hpp"
#include "debug_mode.hpp"

namespace cvv {


namespace impl {
	//implementation outside API
	void debugSobel(cv::InputArray original, cv::InputArray result, const CallMetaData& data, 
			const char* description, const char* view);
} // namespace impl

#ifdef CVVISUAL_DEBUGMODE
static inline void debugSobel(cv::InputArray original, cv::InputArray result,
		impl::CallMetaData metaData = impl::CallMetaData(), const char* description = nullptr,
		const char* view = nullptr)
{
	if(debugMode()) {
		impl::debugSobel(original, result, metaData, description, view);
	}
}
#else
static inline void debugSobel(cv::InputArray, cv::InputArray,
		impl::CallMetaData = impl::CallMetaData(), const char* = nullptr,
		const char* = nullptr) {}
#endif

/*
static inline void debugSobel(cv::InputArray original, cv::InputArray result,
		impl::CallMetaData metaData, ::std::string description,
		::std::string view = "") {
	debugSobel(original, result, metaData, description.c_str(), view.c_str());
}
*/

} // namespace cvv


#endif
