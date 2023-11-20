#pragma once

class Character;


class ArriveSteering
{
public:
  ArriveSteering(Character* ref, USVec2D Target)
    :ref(ref)
    , Target(Target)
  {

  }
  USVec2D Target;
  Character* ref;
  USVec2D GetSteering();
  void DrawDebug();
};


//class ArriveSteering
//{
//private:
//  Character* mChar;
//  USVec2D mTargetPoint;
//public:
//  void DrawDebug();
//  ArriveSteering(USVec2D _TargetPoint, Character* _Char);
//
//  USVec2D GetSteering();
//};

