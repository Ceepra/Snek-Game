#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension,c);
}



int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x>=x && loc.x<width+x &&
		loc.y >= y && loc.y < height+y;
}

void Board::DrawBorder(Color c)
{
	if (x>0 && y>0)
	{
		gfx.DrawRectDim(x * dimension - wall, y * dimension - wall, wall, dimension * height + wall, c);
		gfx.DrawRectDim(x * dimension - wall, y * dimension - wall, dimension * width + wall, wall, c);

	}
	if (x< dimension * width && y< dimension * height)
	{
		gfx.DrawRectDim((x + width) * dimension, y * dimension - wall, wall, dimension * height + 2*wall, c);
		gfx.DrawRectDim(x * dimension - wall, (y + height) * dimension, dimension * width + 2*wall, wall, c);
	}
}



void Board::SetBorderLocation(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
}

void Board::DrawBoardPadding()
{
	for (int i = x * dimension; i < (width+x)*dimension; i += dimension)
	{
		gfx.DrawRectDim(i,y * dimension - wall ,1,height*dimension + wall, Colors::White);
	}
	for (int i = y * dimension; i < (height+y) * dimension; i += dimension)
	{
		gfx.DrawRectDim(x * dimension - wall, i, width*dimension+wall,1,Colors::White );
	}
}
