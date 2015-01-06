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
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


namespace Processors {
namespace FindEdges {


class FindEdgesTransMode {
public:
	static int fromStr(const std::string & s)
	{
		if (s == "CV_RETR_EXTERNAL")
			return CV_RETR_EXTERNAL;
		else if (s == "CV_RETR_LIST")
			return CV_RETR_LIST;
		else if (s == "CV_RETR_CCOMP")
			return CV_RETR_CCOMP;
		else if (s == "CV_RETR_TREE")
			return CV_RETR_TREE;
		else
			return CV_RETR_EXTERNAL;
	}

	static std::string toStr(int t)
	{
		switch (t)
		{
			case CV_RETR_EXTERNAL:
				return "CV_RETR_EXTERNAL";
			case CV_RETR_LIST:
				return "CV_RETR_LIST";
			case CV_RETR_CCOMP:
				return "CV_RETR_CCOMP";
			case CV_RETR_TREE:
				return "CV_RETR_TREE";
			default:
				return "CV_RETR_EXTERNAL";
		}
	}
};

class FindEdgesTransMethod {
public:
	static int fromStr(const std::string & s)
	{
		if (s == "CV_CHAIN_APPROX_NONE")
			return CV_CHAIN_APPROX_NONE;
		else if (s == "CV_CHAIN_APPROX_SIMPLE")
			return CV_CHAIN_APPROX_SIMPLE;
		else if (s == "CV_CHAIN_APPROX_TC89_L1")
			return CV_CHAIN_APPROX_TC89_L1;
		else if (s == "CV_CHAIN_APPROX_TC89_KCOS")
			return CV_CHAIN_APPROX_TC89_KCOS;
		else
			return CV_CHAIN_APPROX_NONE;
	}

	static std::string toStr(int t)
	{
		switch (t)
		{
			case CV_CHAIN_APPROX_NONE:
				return "CV_CHAIN_APPROX_NONE";
			case CV_CHAIN_APPROX_SIMPLE:
				return "CV_CHAIN_APPROX_SIMPLE";
			case CV_CHAIN_APPROX_TC89_L1:
				return "CV_CHAIN_APPROX_TC89_L1";
			case CV_CHAIN_APPROX_TC89_KCOS:
				return "CV_CHAIN_APPROX_TC89_KCOS";
			default:
				return "CV_CHAIN_APPROX_NONE";
		}
	}
};


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
	Base::Property<int, FindEdgesTransMethod> method;
	Base::Property<int, FindEdgesTransMode> mode;
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
