#pragma once

class Character;

class AlignSteering
{
private:

  Character* ref;
  USVec2D Target;
  float TargetAngle;
  float angleDebug;
  float mRadiansToDegrees = 57.2957f;
  float AngleTargetVel;
  float MaxCharVel;

public:
  void DrawDebug();
  AlignSteering(Character* _Char, USVec2D _TargetPoint, float _TargetAngle);

  float GetSteering();

  template<typename T>
  constexpr const T& clamp(const T& value, const T& min, const T& max) {
    return (value < min) ? min : (max < value) ? max : value;
  }
};


