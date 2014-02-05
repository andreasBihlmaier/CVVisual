#ifndef CVVISUAL_DEBUG_DMATCH_HPP
#define CVVISUAL_DEBUG_DMATCH_HPP

#include <string>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"

#include "call_meta_data.hpp"
#include "debug_mode.hpp"

namespace cvv {


namespace impl {
	void debugDMatch(
		cv::InputArray img1, std::vector<cv::KeyPoint> keypoints1,
		cv::InputArray img2, std::vector<cv::KeyPoint> keypoints2,
		std::vector<cv::DMatch> matches, const CallMetaData& data,
		const char* description, const char* view);
} // namespace impl

#ifdef CVVISUAL_DEBUGMODE
static inline void debugDMatch(
		cv::InputArray img1, std::vector<cv::KeyPoint> keypoints1,
		cv::InputArray img2, std::vector<cv::KeyPoint> keypoints2,
		std::vector<cv::DMatch> matches, const impl::CallMetaData& data,
		const char* description = nullptr, const char* view = nullptr)
{
	if(debugMode()) {
		impl::debugDMatch(img1, std::move(keypoints1), img2, std::move(keypoints2),
				std::move(matches), data, description, view);
	}
}
#else
static inline void debugDMatch(
		cv::InputArray, std::vector<cv::KeyPoint>, cv::InputArray, std::vector<cv::KeyPoint>,
		std::vector<cv::DMatch>, const impl::CallMetaData&, const char* = nullptr,
		const char*w = nullptr);
#endif

/*
static inline void debugDMatch(cv::InputArray original, cv::InputArray result,
		impl::CallMetaData metaData, ::std::string description,
		::std::string view = "") {
	debugDMatch(original, result, metaData, description.c_str(), view.c_str());
}
*/

} // namespace cvv


#endif
