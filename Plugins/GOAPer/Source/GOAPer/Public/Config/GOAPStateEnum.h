#pragma once
#include "GOAPer.h"

UENUM()
enum class EGOAPStateEnum : uint8
{
	HasWeapon,
	IsAmmoAvailable,
	HasAmmo,
	IsWeaponAvailable,
	HasTarget,
	IsTargetAlive,
	IsFullHealth,
	IsInValidCoverZone,
	IsInCover,
};