#pragma once

class Character;

class SeekSteering
{
public:
  SeekSteering(Character* ref, const USVec2D& Target)
    :ref(ref)
    , Target(Target)
  {
  }


  //USVec2D Veldeseada;
  USVec2D Target;
  Character* ref;
  USVec2D GetStearing();
  void DrawDebug();

};


//class SeekSteering
//{
//private:
//  USVec2D mTargetPoint;
//  
//  Character* mChar;
//
//  USVec2D mDesVel;
//  USVec2D mAcc;
//
//public:
//  SeekSteering( USVec2D _TargetPoint, Character* _Char);
//  void DrawDebug();
//  
//  USVec2D GetSteering();
//};

