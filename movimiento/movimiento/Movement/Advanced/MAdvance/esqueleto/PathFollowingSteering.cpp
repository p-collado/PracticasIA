#include "stdafx.h"
#include "PathFollowingSteering.h"
#include "character.h"
#include "SeekSteering.h"
#include "path.h"

PathFollowingSteering::PathFollowingSteering(Character* character)
{
  ref = character;
	Velocity = USVec2D(0.0f, 0.0f);
	Acceleration = USVec2D(0.0f, 0.0f);
	ClosestPoint = USVec2D(0.0f, 0.0f);
	LookAheadPoint = USVec2D(0.0f, 0.0f);
	NextPoint = 1;
}

USVec2D PathFollowingSteering::GetNextPointToGo(Character* character)
{

	if (character == nullptr)
	{
		return USVec2D();
	}
		
	Path path = character->GetPath();

	const int numberOfPointsInPath = path.PointList.size();

	if (numberOfPointsInPath > 1)
	{
		const int firstNearIndex = 0;
		float distanceToCharacter = 0.0f;
		float bestDistance = 100000.0f;
		float dotProduct = 0.0f;

		USVec3D characterLocation = character->GetLoc();
		USVec2D bestPoint = USVec2D(0.0f, 0.0f);
		USVec2D segment = USVec2D(0.0f, 0.0f);
		USVec2D normalizedSegment = USVec2D(0.0f, 0.0f);
		USVec2D distanceFromPointToCharacter = USVec2D(0.0f, 0.0f);
		USVec2D nextSegment = USVec2D(0.0f, 0.0f);
		float remainder = 0.0f;

		for (int i = 0; i < numberOfPointsInPath - 1; ++i)
		{
			segment = path.PointList.at(i + 1) - path.PointList.at(i);
			normalizedSegment = segment;
			normalizedSegment.NormSafe();
			distanceFromPointToCharacter = characterLocation - path.PointList.at(i);
			dotProduct = normalizedSegment.Dot(distanceFromPointToCharacter);
			dotProduct /= segment.Length();
			dotProduct >= 1.0f ? ClosestPoint = path.PointList.at(i + 1) : 
			dotProduct <= 0.0f ? ClosestPoint = path.PointList.at(i) : 
			ClosestPoint = path.PointList.at(i) + segment * dotProduct;
			distanceToCharacter = (ClosestPoint - character->GetLoc()).LengthSquared();

			if (distanceToCharacter < bestDistance)
			{
				bestDistance = distanceToCharacter;
				bestPoint = ClosestPoint;
				NextPoint = i + 1;
			}
		}

		ClosestPoint = bestPoint;
		segment = path.PointList.at(NextPoint) - path.PointList.at(NextPoint - 1);
		normalizedSegment = segment;
		normalizedSegment.NormSafe();

		// Look ahead point
		remainder = character->GetParams().look_ahead - (path.PointList.at(NextPoint) - ClosestPoint).Length();

		if (remainder > 0.0f)
		{
			int previousTargetPointInPath = NextPoint;

			if (NextPoint < (numberOfPointsInPath - 1))
			{
				for (; previousTargetPointInPath < numberOfPointsInPath - 1; ++previousTargetPointInPath)
				{
					const float aux = remainder - (path.PointList.at(previousTargetPointInPath + 1) - path.PointList.at(previousTargetPointInPath)).Length();

					if (aux <= 0.0f) 
					{
						break;
					}

					remainder -= aux;
					++previousTargetPointInPath;
				}

				if (path.PointList.size() > previousTargetPointInPath + 1)
				{
					nextSegment = path.PointList.at(previousTargetPointInPath + 1) - path.PointList.at(previousTargetPointInPath);
				}
			}
			else
			{
				nextSegment = path.PointList.at(NextPoint) - path.PointList.at(NextPoint - 1);
			}

			USVec2D normalizedNextSegment = nextSegment;
			normalizedNextSegment.NormSafe();

			LookAheadPoint = path.PointList.at(previousTargetPointInPath) + normalizedNextSegment * remainder;
		}
		else
		{
			LookAheadPoint = ClosestPoint + normalizedSegment * character->GetParams().look_ahead;
		}

		return LookAheadPoint;
	}
	else 
	{
		return path.PointList.at(0);
	}

	return character->GetLoc();
}

USVec2D PathFollowingSteering::GetSteering(USVec2D target)
{
  ref->Seek->Target = GetNextPointToGo(ref);
  return ref->Seek->GetStearing();
}

void PathFollowingSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	// Look ahead point
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.f, 1.0f);
	MOAIDraw::DrawEllipseFill(LookAheadPoint.mX, LookAheadPoint.mY, 5, 5, 500);

	// Closest point
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 1.0f);
	MOAIDraw::DrawEllipseFill(ClosestPoint.mX, ClosestPoint.mY, 5, 5, 500);

	// Next point
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 1.0f);
	MOAIDraw::DrawEllipseFill(ref->GetPath().PointList.at(NextPoint).mX, ref->GetPath().PointList.at(NextPoint).mY, 5, 5, 500);

	const int numberOfPointsInPath = ref->GetPath().PointList.size();

	if (numberOfPointsInPath > 0)
	{
		// Outline each point in path
		gfxDevice.SetPenColor(0.7f, 0.6f, 0.0f, 1.0f);

		for (int i = 0; i < numberOfPointsInPath; ++i)
		{
			MOAIDraw::DrawEllipseOutline(ref->GetPath().PointList.at(i).mX, ref->GetPath().PointList.at(i).mY, 10, 10, 500);
		}

		// Line between points
		gfxDevice.SetPenColor(0.7f, 0.0f, 0.6f, 1.0f);

		for (int i = 0; i < numberOfPointsInPath - 1; ++i)
		{
			MOAIDraw::DrawLine(ref->GetPath().PointList.at(i), ref->GetPath().PointList.at(i + 1));
		}
	}
}
