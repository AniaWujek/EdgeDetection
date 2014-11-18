/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef DRAWLINES_HPP_
#define DRAWLINES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>
#include "Types/DrawableContainer.hpp"


namespace Processors {
namespace DrawLines {

/*!
 * \class DrawLines
 * \brief DrawLines processor class.
 *
 *
 */
class DrawLines: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawLines(const std::string & name = "DrawLines");

	/*!
	 * Destructor
	 */
	virtual ~DrawLines();

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
	Base::DataStreamIn<Types::DrawableContainer> in_lines;
	Base::DataStreamIn<cv::Mat> in_img;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_DrawHoughLines;

	// Properties


	// Handlers
	void DrawHoughLines();

};

} //: namespace DrawLines
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawLines", Processors::DrawLines::DrawLines)

#endif /* DRAWLINES_HPP_ */
