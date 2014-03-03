#ifndef CVVISUAL_DUAL_FILTER_VIEW_HPP
#define CVVISUAL_DUAL_FILTER_VIEW_HPP

//STD
#include <string>
#include <unordered_map>
//OpenCV
//QT
#include <QString>
#include <QWidget>
//CVV
#include "../qtutil/matinfowidget.hpp"
#include "../qtutil/zoomableimage.hpp"
#include "filter_view.hpp"

namespace cvv {namespace view {

/**
* @brief Enum class for possible types of difference Filters used by
*		applyDiffFilter
*/
enum class DiffFilterType
{
	HUE = 0,
	SATURATION = 1,
	VALUE = 2,
	LUMINANCE=VALUE,
	GRAYSCALE = 3
};

/**
* Original and resulting image are the two images passed with debug call.
* Filtered image refers to an image created by applying a chosen filter to
* both of these images.
*
* @brief Filterview showing original, filtered and result image
*/
class DualFilterView: public FilterView
{
Q_OBJECT
	private:
		std::array<cv::Mat, 2> rawImages_; //< Original and resulting image
		
		std::array<cvv::qtutil::ZoomableImage, 3> zoomImages_;
			//< Original, filtered and resulting image
		
		/**
		* @brief Converts vector of size two to array
		*/
		std::array<cv::Mat, 2> convertToArray(const std::vector<cv::Mat>&) const;

	public:
		/**
		* Default view is DiffFilter grayscale.
		* @brief Constructs View showing original image, default filtered image and
		*		result image.
		* @param images The original and resulting images as passed by the debug call
		* @param parent The Widget that is to be the parent of the view
		*/
		DualFilterView(std::array<cv::Mat, 2> images, QWidget* parent = nullptr);
		
		/**
		* Default view is DiffFilter grayscale.
		* @brief Constructs View showing original image, default filtered image and
		*		result image.
		* @param images The original and resulting images as passed by the debug call.
		*		The vector must contain exactly two images.
		* @param parent The Widget that is to be the parent of the view
		*/
		DualFilterView(const std::vector<cv::Mat>& images, QWidget* parent = nullptr);
};



}} //namespaces

#endif
