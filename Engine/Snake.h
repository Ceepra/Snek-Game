#pragma once
#include "Board.h"

class Snake
{

private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(int s);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:

	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColors[5] = { Color(0,255,0), Color(0,205,0) ,Color(0,155,0) ,Color(0,105,0) ,Color(0,55,0) };
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;

};


