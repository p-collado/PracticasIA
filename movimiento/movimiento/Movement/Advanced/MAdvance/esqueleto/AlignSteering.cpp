#include "stdafx.h"
#include "AlignSteering.h"
#include "character.h"

void AlignSteering::DrawDebug()
{
  MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

  float length = 100;

  float angle = 0;

  USVec3D axisVex = USVec3D(3, -2, 0);
  USVec3D target = Target - ref->GetLoc();

  angle = ACos(axisVex.Dot(target) / (axisVex.Length() * target.Length()));

  //float radians = angle * PI / 180;

  float newX = ref->GetLoc().mX + Cos(angle) * length;
  float newY = ref->GetLoc().mY + Sin(angle) * length;

  gfxDevice.SetPenColor(1.f, 0.f, 0.f, 1.f);
  MOAIDraw::DrawLine(ref->GetLoc(), USVec3D(newX, newY, 0));
}

AlignSteering::AlignSteering(Character* _Char, USVec2D _TargetPoint, float _TargetAngle)
  :ref(_Char)
  ,Target(_TargetPoint)
  ,TargetAngle(_TargetAngle)
{
}

float AlignSteering::GetSteering()
{  

  float angle = 0;

  USVec3D axisVex = USVec3D(1, 0, 0);
  USVec3D target = target - ref->GetLoc();

  angle = ACos(axisVex.Dot(target) / (axisVex.Length() * target.Length())) * 180 / PI;

  float DesiredAngle = angle - ref->GetRot();
  DesiredAngle = (int(DesiredAngle) % 360 + 360) % 360;

  if (DesiredAngle > 180)
  {
    DesiredAngle = DesiredAngle - 360;
  }

  if (DesiredAngle < -180)
  {
    DesiredAngle = DesiredAngle + 360;
  }

  DesiredAngle *= ref->GetParams().max_angular_velocity;
  float AngularAcc = DesiredAngle - ref->GetAngularVelocity();
  AngularAcc *= ref->GetParams().max_angular_acceleration;

  return AngularAcc;
}