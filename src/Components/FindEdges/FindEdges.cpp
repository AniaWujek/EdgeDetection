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
#include <time.h>

namespace Processors {
namespace FindEdges {

FindEdges::FindEdges(const std::string & name) :
		Base::Component(name) ,
        lowerThreshold("histeresis.lowerThreshold", 50, "range"),
        higherThreshold("histeresis.higherThreshold", 150, "range"),
        kernelSize("kernelSize", 3),
        mode("mode", CV_RETR_EXTERNAL, "combo"),
        method("method", CV_CHAIN_APPROX_NONE, "combo") {

    lowerThreshold.addConstraint("0");
    lowerThreshold.addConstraint("100");
    higherThreshold.addConstraint("0");
    higherThreshold.addConstraint("300");

    mode.setToolTip("MODE");
    mode.addConstraint("CV_RETR_EXTERNAL");
    mode.addConstraint("CV_RETR_LIST");
    mode.addConstraint("CV_RETR_CCOMP");
    mode.addConstraint("CV_RETR_TREE");

    method.setToolTip("METHOD");
    method.addConstraint("CV_CHAIN_APPROX_NONE");
    method.addConstraint("CV_CHAIN_APPROX_SIMPLE");
    method.addConstraint("CV_CHAIN_APPROX_TC89_L1");
    method.addConstraint("CV_CHAIN_APPROX_TC89_KCOS");

    registerProperty(lowerThreshold);
    registerProperty(higherThreshold);
    registerProperty(kernelSize);
    registerProperty(mode);
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
bool printed = false;
void FindEdges::FindContours() {

    cv::Mat image = in_img.read();
    cv::Mat out_image;

    Types::Edges e;

    out_image.create(image.size(), CV_8U);
    Canny(image, out_image, lowerThreshold, higherThreshold, kernelSize);
    findContours( out_image, e.edges, e.hierarchy, mode, method, cv::Point(0, 0) );
    out_edges.write(e);

    std::cout<<"\nfind edges\n";




}



} //: namespace FindEdges
} //: namespace Processors
