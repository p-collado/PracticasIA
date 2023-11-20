#pragma once

class Character;

class AlignSteering
{
private:

  Character* ref;
  USVec2D Target;
  float TargetAngle;


public:
  void DrawDebug();
  AlignSteering(Character* _Char, USVec2D _TargetPoint, float _TargetAngle);

  float GetSteering();
};

