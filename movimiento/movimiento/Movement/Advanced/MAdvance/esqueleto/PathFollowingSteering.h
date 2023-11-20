#pragma once

class Character;


class PathFollowingSteering
{
public:

  PathFollowingSteering(Character* charac);
  Character* ref;
  USVec2D Acceleration;
  USVec2D LookAheadPoint;
  USVec2D Target;
  int NextPoint;
  USVec2D Velocity;
  USVec2D ClosestPoint;


public:

  USVec2D GetNextPointToGo(Character* character);
  USVec2D GetSteering(USVec2D target);
  virtual void DrawDebug();

};

