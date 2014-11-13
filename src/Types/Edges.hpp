/*
 * Circles.hpp
 *
 *  Created on: 20-05-2011
 *      Author: x
 */

#ifndef EDGES_HPP_
#define EDGES_HPP_

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "Types/Drawable.hpp"
#include "Types/Edges.hpp"

namespace Types {

class Edges : public Drawable
{
public:
    Edges() {}
    virtual ~Edges() {}

    std::vector< std::vector<cv::Point> > edges;
    std::vector<cv::Vec4i> hierarchy;

	virtual void draw(cv::Mat& image, cv::Scalar color, int offsetX = 0, int offsetY = 0) 
	{
        for (unsigned int i = 0; i < edges.size(); ++i)
		{
            cv::drawContours(image, edges, i, color, 1, 8, hierarchy, 0, cv::Point() );
		}
	}

	virtual Drawable * clone()
	{
        return new Edges(*this);
	}
};

}

#endif /* EDGES_HPP_ */
