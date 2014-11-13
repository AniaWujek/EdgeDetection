/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "DrawSomeEdges.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace DrawSomeEdges {

DrawSomeEdges::DrawSomeEdges(const std::string & name) :
        Base::Component(name),
        edgeNumber("edgeNumber", 3)
{
    registerProperty(edgeNumber);
}

DrawSomeEdges::~DrawSomeEdges() {
}

void DrawSomeEdges::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_edges", &in_edges);
	registerStream("out_img", &out_img);
	// Register handlers
    h_DrawContours.setup(boost::bind(&DrawSomeEdges::DrawContours, this));
	registerHandler("DrawContours", &h_DrawContours);
	addDependency("DrawContours", &in_img);
	addDependency("DrawContours", &in_edges);

}

bool DrawSomeEdges::onInit() {

	return true;
}

bool DrawSomeEdges::onFinish() {
	return true;
}

bool DrawSomeEdges::onStop() {
	return true;
}

bool DrawSomeEdges::onStart() {
	return true;
}

void DrawSomeEdges::DrawContours() {
    Types::Edges edges = Types::Edges(in_edges.read());
    cv::Mat image = in_img.read().clone();
    cv::Mat image_out = cv::Mat::zeros(image.size(), CV_8UC3);
    for (unsigned int i = 0; i < edgeNumber; ++i)
    {
        cv::drawContours(image_out, edges.edges, i, cv::Scalar(255,255,255), 1, 8, edges.hierarchy, 0, cv::Point() );
    }
    out_img.write(image_out);
}



} //: namespace DrawSomeEdges
} //: namespace Processors
