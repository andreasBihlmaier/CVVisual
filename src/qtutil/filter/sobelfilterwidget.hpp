#ifndef CVVISUAL_SOBELFILTERWIDGET_HPP
#define CVVISUAL_SOBELFILTERWIDGET_HPP

#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>

#include"../filterfunctionwidget.hpp"
#include "grayfilterwidget.hpp"

namespace cvv { namespace qtutil{
/**
 * @brief Represents the opencv sobel filter.
 */
class SobelFilterWidget: public FilterFunctionWidget<1,1>
{
public:
	/**
	 * @brief The input type.
	 */
	using InputArray  = typename FilterFunctionWidget<1,1>::InputArray;

	/**
	 * @brief The output type.
	 */
	using OutputArray = typename FilterFunctionWidget<1,1>::OutputArray;

	/**
	 * @brief Constructor
	 */
	SobelFilterWidget(QWidget* parent = nullptr);

	/**
	 * @brief virtual destructor.
	 */
	virtual ~SobelFilterWidget() override
	{
		TRACEPOINT;
	}

	/**
	 * @brief Applys the filter to in and saves the result in out.
	 * @param in The input images.
	 * @param out The output images.
	 */
	virtual void applyFilter(InputArray in,OutputArray out) const override;

	/**
	 * @brief Checks whether input can be progressed by the applyFilter function.
	 * @param in The input images.
	 * @return bool = true: the filter can be executed.
	 *		bool = false: the filter cant be executed (e.g. images have wrong depth)
	 *		QString = message for the user (e.g. why the filter can't be progressed.)
	 */
	virtual std::pair<bool, QString> checkInput(InputArray in) const override;
private:
	/**
	 * @brief Selection for parameter dx.
	 */
	QSpinBox* dx_;
	/**
	 * @brief Selection for parameter dy.
	 */
	QSpinBox* dy_;
	/**
	 * @brief Selection for parameter ksize.
	 */
	QComboBox* ksize_;
	/**
	 * @brief Selection for parameter borderType.
	 */
	QComboBox* borderType_;
	/**
	 * @brief Wheather a gray filter should be applied first.
	 */
	QCheckBox* gray_;

	/**
	 * @brief a gray filter.
	 */
	GrayFilterWidget* grayFilter_;
};

}}

#endif // SOBELFILTERWIDGET_HPP
