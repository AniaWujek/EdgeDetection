/*!
 * \file
 * \brief 
 * \author Anna Wujek
 */

#ifndef FINDEDGES_HPP_
#define FINDEDGES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Edges.hpp"
#include <opencv2/opencv.hpp>


namespace Processors {
namespace FindEdges {

/*!
 * \class FindEdges
 * \brief FindEdges processor class.
 *
 * 
 */
class FindEdges: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	FindEdges(const std::string & name = "FindEdges");

	/*!
	 * Destructor
	 */
	virtual ~FindEdges();

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

	// Output data streams
	Base::DataStreamOut<Types::Edges> out_edges;

	// Handlers
    Base::EventHandler2 h_FindContours;

	// Properties
	Base::Property<std::string> method;
    Base::Property<int> lowerThreshold;
    Base::Property<int> higherThreshold;
    Base::Property<int> kernelSize;

	
	// Handlers
    void FindContours();

};

} //: namespace FindEdges
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("FindEdges", Processors::FindEdges::FindEdges)

#endif /* FINDEDGES_HPP_ */
