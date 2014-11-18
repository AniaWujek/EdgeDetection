/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawLines.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DrawLines {

DrawLines::DrawLines(const std::string & name) :
		Base::Component(name)  {

}

DrawLines::~DrawLines() {
}

void DrawLines::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_lines", &in_lines);
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	h_DrawHoughLines.setup(boost::bind(&DrawLines::DrawHoughLines, this));
	registerHandler("DrawHoughLines", &h_DrawHoughLines);
	addDependency("DrawHoughLines", &in_lines);
	addDependency("DrawHoughLines", &in_img);

}

bool DrawLines::onInit() {

	return true;
}

bool DrawLines::onFinish() {
	return true;
}

bool DrawLines::onStop() {
	return true;
}

bool DrawLines::onStart() {
	return true;
}

void DrawLines::DrawHoughLines() {
    cv::Mat image = in_img.read().clone();
    Types::DrawableContainer lines = in_lines.read();
    lines.draw(image, cv::Scalar(0,255,0));
    out_img.write(image);
}



} //: namespace DrawLines
} //: namespace Processors
