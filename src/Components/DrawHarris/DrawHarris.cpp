/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawHarris.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DrawHarris {

DrawHarris::DrawHarris(const std::string & name) :
		Base::Component(name)  {

}

DrawHarris::~DrawHarris() {
}

void DrawHarris::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_features", &in_features);
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	h_DrawCorners.setup(boost::bind(&DrawHarris::DrawCorners, this));
	registerHandler("DrawCorners", &h_DrawCorners);
	addDependency("DrawCorners", &in_features);
	addDependency("DrawCorners", &in_img);

}

bool DrawHarris::onInit() {

	return true;
}

bool DrawHarris::onFinish() {
	return true;
}

bool DrawHarris::onStop() {
	return true;
}

bool DrawHarris::onStart() {
	return true;
}

void DrawHarris::DrawCorners() {

    cv::Mat image = in_img.read().clone();
    Types::Features features = in_features.read();
    features.draw(image, cv::Scalar(0,255,0));
    out_img.write(image);
}



} //: namespace DrawHarris
} //: namespace Processors
