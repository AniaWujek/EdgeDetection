/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef DRAWEDGES_HPP_
#define DRAWEDGES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Edges.hpp"
#include <opencv2/opencv.hpp>


namespace Processors {
namespace DrawEdges {

/*!
 * \class DrawEdges
 * \brief DrawEdges processor class.
 *
 *
 */
class DrawEdges: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	DrawEdges(const std::string & name = "DrawEdges");

	/*!
	 * Destructor
	 */
	virtual ~DrawEdges();

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
	Base::DataStreamIn<Types::Edges, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_edges;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_DrawContours;

	// Properties


	// Handlers
	void DrawContours();

};

} //: namespace DrawEdges
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("DrawEdges", Processors::DrawEdges::DrawEdges)

#endif /* DRAWEDGES_HPP_ */
