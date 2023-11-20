#pragma once
struct Edge
{
public:

	USVec2D Start;
	USVec2D End;

	float SquaredLegnth() { return (End.mX - Start.mX) * (End.mX - Start.mX) + (End.mY - Start.mY) * (End.mY - Start.mY); }
};

