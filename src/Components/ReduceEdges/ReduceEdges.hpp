/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef REDUCEEDGES_HPP_
#define REDUCEEDGES_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>
#include "Types/Edges.hpp"

#include "Types/DrawableContainer.hpp"
#include "Types/Line.hpp"


namespace Processors {
namespace ReduceEdges {

/*!
 * \class ReduceEdges
 * \brief ReduceEdges processor class.
 *
 *
 */
class ReduceEdges: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ReduceEdges(const std::string & name = "ReduceEdges");

	/*!
	 * Destructor
	 */
	virtual ~ReduceEdges();

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
	Base::DataStreamIn<Types::Edges> in_edges;

	// Output data streams
	Base::DataStreamOut <Types::DrawableContainer> out_linesDrawable;
	Base::DataStreamOut < vector<cv::Vec4i> > out_lines;

	// Handlers
	Base::EventHandler2 h_reduce;

	// Properties
    Base::Property<float> diff;

	// Handlers
	void reduce();

};

} //: namespace ReduceEdges
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ReduceEdges", Processors::ReduceEdges::ReduceEdges)

#endif /* REDUCEEDGES_HPP_ */
