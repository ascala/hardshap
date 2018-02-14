#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <iostream>
#include <cmath>

#include <Vec2d.h>

class Segment {
public:
	Vec2d r;       // center of the segment
	Vec2d dir;     // half length
	double halflen;
	
	Segment();
	Segment(const Vec2d& center, const Vec2d& direction, const double half);
	Segment(const Vec2d& P0, const Vec2d& P1);
	Segment(Segment const &);

//	stream operators
	friend std::ostream& operator<<(std::ostream& pStr, const Segment& pS);
	friend std::istream& operator>>(std::istream pStr, Segment& pS);
	

// square distance between two segments
	double dist2( Segment const &);
	double dist2( Segment const &, double &u1, double &u2);
	
private:
};



#endif /*SEGMENT_H_*/
