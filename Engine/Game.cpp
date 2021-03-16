/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek({15,15}),
	goal(rng,brd,snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameIsOver && isGameStarted)
	{

		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if (!(delta_loc == Location{ 0,1 }))
			{
				delta_loc = { 0,-1 };
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (!(delta_loc == Location{ 0,-1 }))
			{
				delta_loc = { 0,1 };
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (!(delta_loc == Location{ 1, 0 }))
			{
				delta_loc = { -1,0 };
			}
			
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (!(delta_loc == Location {-1, 0}))
			{
				delta_loc = { 1,0 };
			}
			
		}
		++snekMoveCounter;
		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;
			const Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) || snek.IsInTileExceptEnd(next) )
			{
				gameIsOver = true;
			}
			else
			{
				bool eating = next == goal.GetLocation();
				if (eating)
				{
					snek.Grow();
					snekMovePeriod -= 0.5f;
				}
				snek.MoveBy(delta_loc);
				if (eating)
				{
					goal.Respawn(rng, brd, snek);
				}
			}

		}
	}
}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		brd.SetBorderLocation(2, 2);
		snek.Draw(brd);
		goal.Draw(brd);
		brd.DrawBorder(Colors::White);

		if (isGridOn)
		{
			brd.DrawBoardPadding();
		}

		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(200, 200, gfx);
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isGameStarted = true;
		}
		else
		{
			SpriteCodex::DrawTitle(300, 200, gfx);
		}
	}
	
}