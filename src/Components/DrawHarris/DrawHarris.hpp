/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef DRAWHARRIS_HPP_
#define DRAWHARRIS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Features.hpp"
#include <opencv2/opencv.hpp>


namespace Processors {
namespace DrawHarris {

/*!
 * \class DrawHarris
 * \brief DrawHarris processor class.
 *
 *
 */
class DrawHarris: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawHarris(const std::string & name = "DrawHarris");

	/*!
	 * Destructor
	 */
	virtual ~DrawHarris();

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
	Base::DataStreamIn<Types::Features> in_features;
	Base::DataStreamIn<cv::Mat> in_img;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_DrawCorners;

	// Properties


	// Handlers
	void DrawCorners();

};

} //: namespace DrawHarris
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawHarris", Processors::DrawHarris::DrawHarris)

#endif /* DRAWHARRIS_HPP_ */
