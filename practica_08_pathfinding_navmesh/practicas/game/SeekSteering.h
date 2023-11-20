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