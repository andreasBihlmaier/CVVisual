#ifndef CVVISUAL_MATCH_SCENE
#define CVVISUAL_MATCH_SCENE

#include <vector>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "cvvmatch.hpp"
#include "cvvkeypoint.hpp"
#include "zoomableproxyobject.hpp"
#include "../zoomableimage.hpp"
#include "../zoomableimageoptpanel.hpp"
#include "../../dbg/dbg.hpp"

namespace cvv{ namespace qtutil{

/**
 * @brief this scene shows two (zoomable)images with keypoints and matches.
 */
class MatchScene:public QWidget{
Q_OBJECT
public:

	/**
	 * @brief the constructor
	 * @param imageLeft the left image
	 * @param imageRight the right iamge
	 * @param parent the parent Widget
	 */
	MatchScene(cv::Mat imageLeft,cv::Mat imageRight, QWidget* parent = nullptr);

	/**
	 * @brief returns a ZoomableOptPanel of the left Image
	 * @return a ZoomableOptPanel of the left Image
	 */
	std::unique_ptr<ZoomableOptPanel> getLeftMatInfoWidget()
		{TRACEPOINT;return util::make_unique<ZoomableOptPanel>(*leftImage_);}

	/**
	 * @brief returns a ZoomableOptPanel of the right Image
	 * @return a ZoomableOptPanel of the right Image
	 */
	std::unique_ptr<ZoomableOptPanel> getRightMatInfoWidget()
		{TRACEPOINT;return util::make_unique<ZoomableOptPanel>(*rightImage_);}


public slots:
	void addLeftKeypoint(CVVKeyPoint*);
	void addRightKeyPoint(CVVKeyPoint*);
	void addMatch(CVVMatch*);
	void adjustImages();

protected:
	 void resizeEvent(QResizeEvent * event);

private:
	QGraphicsView 		*graphicView_;
	QGraphicsScene 		*graphicScene_;

	qtutil::ZoomableImage 	*leftImage_;
	qtutil::ZoomableImage 	*rightImage_;

	ZoomableProxyObject	*leftImWidget_;
	ZoomableProxyObject	*rightImWidget_;

};
}}
#endif
