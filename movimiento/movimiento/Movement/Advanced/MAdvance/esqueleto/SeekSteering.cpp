#include "stdafx.h"
#include "character.h"
#include "SeekSteering.h"

USVec2D SeekSteering::GetStearing()
{
  USVec2D Veldeseada = Target - ref->GetLoc();
  Veldeseada.Norm();
  Veldeseada *= ref->GetParams().max_velocity;
  USVec2D AceleracionNecesaria = Veldeseada - ref->GetLinearVelocity();
  AceleracionNecesaria.Norm();
  return USVec2D((AceleracionNecesaria * ref->GetParams().max_acceleration));
}

void SeekSteering::DrawDebug()
{
  MOAIGfxDevice::Get().SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
  MOAIDraw::DrawLine(ref->GetLoc(), USVec3D(ref->GetLoc() + ref->Accel));
  MOAIGfxDevice::Get().SetPenColor(1.0f, 0.0f, 0.0f, 0.5f);
  MOAIDraw::DrawLine(ref->GetLoc(), USVec3D(ref->GetLoc() + ref->Vel));
  MOAIGfxDevice::Get().SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
  MOAIDraw::DrawEllipseOutline(ref->GetLoc().mX, ref->GetLoc().mY, 20.f, 20.f, 20);
}



//SeekSteering::SeekSteering(USVec2D _TargetPoint, Character* _Char)
//{
//  mTargetPoint = _TargetPoint;
//  mChar = _Char;
//}
//
//void SeekSteering::DrawDebug()
//{
//  //MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
//  //gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 0.5f);
//  //MOAIDraw::DrawLine(mChar->GetLoc(), USVec3D(mChar->GetLoc() + mChar->mLinearVelocity));
//  //gfxDevice.SetPenColor(0.0f, 1.0f, 1.0f, 0.5f);
//  //MOAIDraw::DrawLine(mChar->GetLoc(), USVec3D( mChar->GetLoc() + mChar->mAcc));
//}
//
//
//USVec2D SeekSteering::GetSteering()
//{
//  mDesVel = mTargetPoint - mChar->GetLoc();
//  mDesVel.Norm();
//  mDesVel *= mChar->GetParams().max_velocity;
//  mAcc = mDesVel - mChar->GetLinearVelocity();
//  mAcc.Norm();
//  mAcc *= mChar->GetParams().max_acceleration;
//
//  return mAcc;
//}
