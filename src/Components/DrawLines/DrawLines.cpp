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

    cv::Mat image_out = cv::Mat::zeros(image.size(), CV_8UC3);
    image_out.setTo(cv::Scalar(255,255,255));
    for(int i = 0; i < lines.size(); ++i) {
        Types::Line * line = dynamic_cast <Types::Line *> (lines.get(i));

        cv::line(image_out, line->getP1(), line->getP2(), cv::Scalar(255,0,0), 15);

    }





    //lines.draw(image_out, cv::Scalar(255,0,255));
    //cv::cvtColor(image_out, image_out, CV_BGR2GRAY);
    out_img.write(image_out);
}



} //: namespace DrawLines
} //: namespace Processors
