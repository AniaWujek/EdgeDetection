/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef DRAWCORNERS_HPP_
#define DRAWCORNERS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace DrawCorners {

/*!
 * \class DrawCorners
 * \brief DrawCorners processor class.
 *
 *
 */
class DrawCorners: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawCorners(const std::string & name = "DrawCorners");

	/*!
	 * Destructor
	 */
	virtual ~DrawCorners();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<cv::Mat> in_img;
	Base::DataStreamIn< std::vector<cv::Point2f> > in_corners;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_DrawDetectedCorners;

	// Properties


	// Handlers
	void DrawDetectedCorners();

};

} //: namespace DrawCorners
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawCorners", Processors::DrawCorners::DrawCorners)

#endif /* DRAWCORNERS_HPP_ */
