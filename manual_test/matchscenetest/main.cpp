#include <iostream>

#include <QApplication>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "../../src/qtutil/matchscene.hpp"

int main(int argc, char** argv)
{
	QApplication a(argc, argv);

	if(argc != 3)
	{
		std::cerr << "Only execute this test with filenames of two images as arguments! \n";
		return -1;
	}
	auto src 	= cv::imread(argv[1]);
	auto train 	= cv::imread(argv[2]);
	std::vector<cv::KeyPoint> key1;
	std::vector<cv::KeyPoint> key2;
	std::vector<cv::DMatch> match;
	cvv::qtutil::MatchScene *matchscene = new cvv::qtutil::MatchScene{src,train,key1, key2,match};
	matchscene->setWindowTitle("MatchScene Test");
	matchscene->show();
	return a.exec();
	
}