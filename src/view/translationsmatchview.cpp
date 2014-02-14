
#include <QHBoxLayout>

#include "../qtutil/accordion.hpp"
#include "../qtutil/matchview/matchscene.hpp"
#include "../qtutil/matchview/singlecolorpen.hpp"
#include "../qtutil/matchview/cvvkeypoint.hpp"
#include "../qtutil/matchview/cvvmatch.hpp"
#include "../qtutil/matchview/singlecolorpen.hpp"
#include "../qtutil/matchview/singlecolorkeypointpen.hpp"
#include "../util/util.hpp"

#include "translationsmatchview.hpp"

namespace cvv{ namespace view{

TranslationMatchView::TranslationMatchView(std::vector<cv::KeyPoint> leftKeyPoints,std::vector<cv::KeyPoint> rightKeyPoints,
		std::vector<cv::DMatch> matches,cv::Mat leftIm,cv::Mat rightIm,QWidget *parent):
	MatchView{parent}
{
	auto layout	= util::make_unique<QHBoxLayout>();
	auto accor	= util::make_unique< qtutil::Accordion>();
	auto matchscene	= util::make_unique<qtutil::MatchScene>(leftIm,rightIm);
	auto matchpen	= util::make_unique<qtutil::SingleColorPen>();
	auto keypen	= util::make_unique<qtutil::SingleColorKeyPen>();

	qtutil::MatchScene *matchscene_ptr=matchscene.get();
	qtutil::SingleColorPen *matchpen_ptr=matchpen.get();
	qtutil::SingleColorKeyPen *keypen_ptr=keypen.get();
	accor->setMinimumWidth(250);
	accor->setMaximumWidth(250);


	accor->insert("Match Color",std::move(matchpen));
	accor->insert("KeyPoint Color",std::move(keypen));
	accor->insert("Left Image ",std::move(matchscene_ptr->getLeftMatInfoWidget()));
	accor->insert("Right Image ",std::move(matchscene_ptr->getRightMatInfoWidget()));

	layout->addWidget(accor.release());
	layout->addWidget(matchscene.release());
	setLayout(layout.release());

	std::vector<qtutil::CVVKeyPoint*> leftKeys;
	std::vector<qtutil::CVVKeyPoint*> leftinvisibleKeys;
	std::vector<qtutil::CVVKeyPoint*> rightKeys;
	std::vector<qtutil::CVVKeyPoint*> rightinvisibleKeys;

	for(auto& keypoint:leftKeyPoints)
	{
		auto key = util::make_unique<qtutil::CVVKeyPoint>(keypoint);
		connect(keypen_ptr,SIGNAL(settingsChanged(const KeyPointPen&)),key.get(),SLOT(updatePen(const KeyPointPen&)));
		matchscene_ptr->addLeftKeypoint(key.get());
		leftKeys.push_back(key.release());

		auto keyinvisible = util::make_unique<qtutil::CVVKeyPoint>(keypoint);
		keyinvisible->setShow(false);
		matchscene_ptr->addRightKeyPoint(keyinvisible.get());
		rightinvisibleKeys.push_back(keyinvisible.release());
	}
	for(auto& keypoint:rightKeyPoints)
	{
		auto key = util::make_unique<qtutil::CVVKeyPoint>(keypoint);
		connect(keypen_ptr,SIGNAL(settingsChanged(const KeyPointPen&)),key.get(),SLOT(updatePen(const KeyPointPen&)));
		matchscene_ptr->addRightKeyPoint(key.get());
		rightKeys.push_back(key.release());

		auto keyinvisible = util::make_unique<qtutil::CVVKeyPoint>(keypoint);
		keyinvisible->setShow(false);
		matchscene_ptr->addLeftKeypoint(keyinvisible.get());
		leftinvisibleKeys.push_back(keyinvisible.release());
	}
	for(auto& match:matches)
	{
		auto cvmatchleft = util::make_unique<qtutil::CVVMatch>(leftKeys.at(match.queryIdx),leftinvisibleKeys.at(match.trainIdx),match.distance);
		connect(matchpen_ptr,SIGNAL(settingsChanged(const MatchPen&)),cvmatchleft.get(),SLOT(updatePen(const MatchPen&)));
		matchscene_ptr->addMatch(cvmatchleft.release());

		auto cvmatchright = util::make_unique<qtutil::CVVMatch>(rightKeys.at(match.queryIdx),rightinvisibleKeys.at(match.trainIdx),match.distance);
		connect(matchpen_ptr,SIGNAL(settingsChanged(const MatchPen&)),cvmatchright.get(),SLOT(updatePen(const MatchPen&)));
		matchscene_ptr->addMatch(cvmatchright.release());
	}
}

}}