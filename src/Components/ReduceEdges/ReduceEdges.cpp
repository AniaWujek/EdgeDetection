/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "ReduceEdges.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>
#include <math.h>



namespace Processors {
namespace ReduceEdges {

ReduceEdges::ReduceEdges(const std::string & name) :
		Base::Component(name),
		diff("diff", 10.0, "range")  {

		diff.addConstraint("0");
		diff.addConstraint("10");
		registerProperty(diff);

}

ReduceEdges::~ReduceEdges() {
}

void ReduceEdges::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_edges", &in_edges);
	registerStream("out_lines", &out_lines);
	registerStream("out_linesDrawable", &out_linesDrawable);
	// Register handlers
	h_reduce.setup(boost::bind(&ReduceEdges::reduce, this));
	registerHandler("reduce", &h_reduce);
	addDependency("reduce", &in_edges);

}

bool ReduceEdges::onInit() {

	return true;
}

bool ReduceEdges::onFinish() {
	return true;
}

bool ReduceEdges::onStop() {
	return true;
}

bool ReduceEdges::onStart() {
	return true;
}

void ReduceEdges::reduce() {
    Types::Edges edges = in_edges.read();
    float px, py, kx, ky;
    Types::DrawableContainer c;

    std::vector<cv::Vec4i> lines;
    for(int i = 0; i < edges.edges.size(); ++i) {


        for(int j = 1; j < edges.edges[i].size(); ++j) {
            px = edges.edges[i][j-1].x;
            py = edges.edges[i][j-1].y;
            kx = edges.edges[i][j].x;
            ky = edges.edges[i][j].y;

            lines.push_back(cv::Vec4i(px, py, kx, ky));
        }
    }

    bool bpx = false;
    bool bpy = false;
    bool bkx = false;
    bool bky = false;

    std::vector<int> to_erase;


    for(int i = 0; i < lines.size()-1; ++i) {

        for(int j = i+1; j < lines.size(); ++j) {


                if(abs(lines[i][0] - lines[j][0]) < diff) bpx = true;
                if(abs(lines[i][1] - lines[j][1]) < diff) bpy = true;
                if(abs(lines[i][2] - lines[j][2]) < diff) bkx = true;
                if(abs(lines[i][3] - lines[j][3]) < diff) bky = true;

                if(j <= i) std::cout<<"\n\n\n\n allaaarrnjdsgndfk \n\n\n";

                if(bpx && bpy && bkx && bky) {


                        if(std::find(to_erase.begin(), to_erase.end(), j) == to_erase.end() &&
                            std::find(to_erase.begin(), to_erase.end(), i) == to_erase.end())
                            to_erase.push_back(j);
                        //std::cout<<"\n\nelemnt: "<<i<<"\n\n";

                }


            bpx = false;
            bpy = false;
            bkx = false;
            bky = false;


        }
    }

    std::sort(to_erase.begin(), to_erase.end(), std::greater<int>());
    for(int i = 0; i < to_erase.size(); ++i) {
        lines.erase(lines.begin()+to_erase[i]);
    }
    std::cout<<"\n\nsize erase: "<<to_erase.size()<<"\n\n";
    std::cout<<"\n\nsize lines: "<<lines.size()<<"\n\n";

    for(int i = 0; i < lines.size()-1; ++i) {
        if(abs(lines[i][2] - lines[i+1][0]) < 50 && abs(lines[i][3] - lines[i+1][1]) < 50) {
            lines[i][2] = lines[i+1][0];
            lines[i][3] = lines[i+1][1];
        }


    }

    for(int i = 0; i < lines.size(); ++i) {
        c.add(new Types::Line(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3])));
    }
    out_linesDrawable.write(c);
	out_lines.write(lines);

	std::cout<<"\nREDUCE\n";


}



} //: namespace ReduceEdges
} //: namespace Processors
