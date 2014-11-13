/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawEdges.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DrawEdges {

DrawEdges::DrawEdges(const std::string & name) :
		Base::Component(name)  {

}

DrawEdges::~DrawEdges() {
}

void DrawEdges::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_edges", &in_edges);
	registerStream("out_img", &out_img);
	// Register handlers
	h_DrawContours.setup(boost::bind(&DrawEdges::DrawContours, this));
	registerHandler("DrawContours", &h_DrawContours);
	addDependency("DrawContours", &in_img);
	addDependency("DrawContours", &in_edges);

}

bool DrawEdges::onInit() {

	return true;
}

bool DrawEdges::onFinish() {
	return true;
}

bool DrawEdges::onStop() {
	return true;
}

bool DrawEdges::onStart() {
	return true;
}

void DrawEdges::DrawContours() {
    Types::Edges edges = Types::Edges(in_edges.read());
    cv::Mat image = in_img.read().clone();
    edges.draw(image, cv::Scalar(0,255,0));
    out_img.write(image);
}



} //: namespace DrawEdges
} //: namespace Processors
