#include "stdafx.h"
#include "character.h"
#include "ArriveSteering.h"


USVec2D ArriveSteering::GetSteering()
{
  float arrive_radius = ref->GetParams().arrive_radius;
  float dest_radius = ref->GetParams().dest_radius;
  USVec2D Veldeseada = Target - ref->GetLoc();
  float length = Veldeseada.Length();
  Veldeseada.Norm();
  Veldeseada *= ref->GetParams().max_velocity * (length / arrive_radius);
  USVec2D AceleracionNecesaria = Veldeseada - ref->GetLinearVelocity();
  AceleracionNecesaria.Norm();
  return USVec2D((AceleracionNecesaria * ref->GetParams().max_acceleration));
}

void ArriveSteering::DrawDebug()
{
  MOAIGfxDevice::Get().SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);
  MOAIDraw::DrawEllipseOutline(Target.mX, Target.mY, ref->GetParams().arrive_radius, ref->GetParams().arrive_radius, 10);
}

//ArriveSteering::ArriveSteering(USVec2D _TargetPoint, Character* _Char):mTargetPoint(_TargetPoint), mChar(_Char)
//{
//}
//
//
//void ArriveSteering::DrawDebug()
//{
//  MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
//
//  gfxDevice.SetPenColor(0.5f, 0.5f, 0.f, 0.2f);
//  MOAIDraw::DrawEllipseFill(mChar->GetParams().targetPosition.mX, mChar->GetParams().targetPosition.mY, mChar->GetParams().arrive_radius, mChar->GetParams().arrive_radius, 100);
//}
//
//USVec2D ArriveSteering::GetSteering()
//{
// 
//  USVec2D direction = mChar->GetParams().targetPosition - mChar->GetLoc();
//  const float distance = direction.Length();
//
//  direction.Norm();
//  direction *= mChar->GetParams().max_velocity * (distance / mChar->GetParams().arrive_radius);
//
//  USVec2D Acc = direction - mChar->GetLinearVelocity();
//  Acc.Norm();
//  Acc *= mChar->GetParams().max_acceleration;
//
//  return Acc;
//}
