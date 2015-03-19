/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>
#include "Types/DrawableContainer.hpp"
#include "Types/Line.hpp"


namespace Processors {
namespace DrawSystem {

/*!
 * \class DrawSystem
 * \brief DrawSystem processor class.
 *
 *
 */
class DrawSystem: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawSystem(const std::string & name = "DrawSystem");

	/*!
	 * Destructor
	 */
	virtual ~DrawSystem();

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
	Base::DataStreamIn<cv::Mat, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_img;
	Base::DataStreamIn<Types::DrawableContainer, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_csystem;
	Base::DataStreamIn<std::vector<cv::Point2f> , Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_impoints;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_drawSys;

	// Properties


	// Handlers
	void drawSys();

};

} //: namespace DrawSystem
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawSystem", Processors::DrawSystem::DrawSystem)

#endif /* DRAWSYSTEM_HPP_ */
