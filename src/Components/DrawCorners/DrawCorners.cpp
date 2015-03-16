/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawCorners.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>
#include <stdio.h>
#include <stdlib.h>


namespace Processors {
namespace DrawCorners {

DrawCorners::DrawCorners(const std::string & name) :
		Base::Component(name)  {

}

DrawCorners::~DrawCorners() {
}

void DrawCorners::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_corners", &in_corners);
	registerStream("out_img", &out_img);
	// Register handlers
	h_DrawDetectedCorners.setup(boost::bind(&DrawCorners::DrawDetectedCorners, this));
	registerHandler("DrawDetectedCorners", &h_DrawDetectedCorners);
	addDependency("DrawDetectedCorners", &in_corners);
	addDependency("DrawDetectedCorners", &in_img);

}

bool DrawCorners::onInit() {

	return true;
}

bool DrawCorners::onFinish() {
	return true;
}

bool DrawCorners::onStop() {
	return true;
}

bool DrawCorners::onStart() {
	return true;
}

void DrawCorners::DrawDetectedCorners() {

    std::vector<cv::Point2f> corners = in_corners.read();
    cv::Mat image = in_img.read().clone();



    for(int i = 0; i < corners.size(); ++i) {
        circle(image, corners[i], 3, cv::Scalar(0, 255, 0), -1, 8, 0);

        if(i == 0) putText(image, "0", corners[i], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 4);
        else if(i == 1) putText(image, "1", corners[i], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 4);
        else if(i == 2) putText(image, "2", corners[i], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 4);
        else if(i == 3) putText(image, "3", corners[i], cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 255, 0), 4);
    }

    out_img.write(image);

}



} //: namespace DrawCorners
} //: namespace Processors
