/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "FindEdges.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace FindEdges {

FindEdges::FindEdges(const std::string & name) :
		Base::Component(name) , 
        lowerThreshold("histeresis.lowerThreshold", 50, "range"),
        higherThreshold("histeresis.higherThreshold", 150, "range"),
        kernelSize("kernelSize", 3),
		method("method", std::string("CV_RETR_EXTERNAL")) {

    lowerThreshold.addConstraint("0");
    lowerThreshold.addConstraint("100");
    higherThreshold.addConstraint("0");
    higherThreshold.addConstraint("300");

    registerProperty(lowerThreshold);
    registerProperty(higherThreshold);
    registerProperty(kernelSize);
	registerProperty(method);

}

FindEdges::~FindEdges() {
}

void FindEdges::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_edges", &out_edges);
	// Register handlers
    h_FindContours.setup(boost::bind(&FindEdges::FindContours, this));
    registerHandler("FindContours", &h_FindContours);
    addDependency("FindContours", &in_img);

}

bool FindEdges::onInit() {

	return true;
}

bool FindEdges::onFinish() {
	return true;
}

bool FindEdges::onStop() {
	return true;
}

bool FindEdges::onStart() {
	return true;
}

void FindEdges::FindContours() {

    cv::Mat image = in_img.read();
    cv::Mat out_image;

    Types::Edges e;

    out_image.create(image.size(), CV_8U);
    Canny(image, out_image, lowerThreshold, higherThreshold, kernelSize);
    findContours( out_image, e.edges, e.hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    out_edges.write(e);


}



} //: namespace FindEdges
} //: namespace Processors
