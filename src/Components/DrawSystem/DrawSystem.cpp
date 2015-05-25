/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawSystem.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

namespace Processors {
namespace DrawSystem {

DrawSystem::DrawSystem(const std::string & name) :
		Base::Component(name)  {

}

DrawSystem::~DrawSystem() {
}

void DrawSystem::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_csystem", &in_csystem);
	registerStream("in_impoints", &in_impoints);
	registerStream("out_img", &out_img);
	// Register handlers
	h_drawSys.setup(boost::bind(&DrawSystem::drawSys, this));
	registerHandler("drawSys", &h_drawSys);
	addDependency("drawSys", &in_img);
	addDependency("drawSys", &in_csystem);
	addDependency("drawSys", &in_impoints);

}

bool DrawSystem::onInit() {

	return true;
}

bool DrawSystem::onFinish() {
	return true;
}

bool DrawSystem::onStop() {
	return true;
}

bool DrawSystem::onStart() {
	return true;
}

void DrawSystem::drawSys() {

    cv::Mat image = in_img.read().clone();
    std::vector<cv::Point2f> impoints = in_impoints.read();
    Types::DrawableContainer csystem = in_csystem.read();
    //csystem.draw(image, cv::Scalar(0,255,0));

    for(int i = 0; i < csystem.size(); ++i) {
        Types::Line * line = dynamic_cast <Types::Line *> (csystem.get(i));
        //line->draw(image, cv::Scalar(0,255,0));
        cv::line(image, line->getP1(), line->getP2(), line->getCol(), 13);
        if(i == 0)
            cv::putText(image, "X", line->getP2(), cv::FONT_HERSHEY_SIMPLEX, 3.5, line->getCol(), 7, 8, false);
        if(i == 1)
            cv::putText(image, "Y", line->getP2(), cv::FONT_HERSHEY_SIMPLEX, 3.5, line->getCol(), 7, 8, false);
        if(i == 2)
            cv::putText(image, "Z", line->getP2(), cv::FONT_HERSHEY_SIMPLEX, 3.5, line->getCol(), 7, 8, false);
    }


    for(int i = 0; i < impoints.size(); ++i) {
        circle(image, impoints[i], 15, cv::Scalar(0, 255, 0), -1, 8, 0);
    }


   out_img.write(image);
}



} //: namespace DrawSystem
} //: namespace Processors
