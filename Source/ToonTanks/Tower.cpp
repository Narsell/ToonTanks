// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInRange()) {
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

bool ATower::IsInRange()
{
	if (!Tank) return false;
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return Distance <= FireRange;
}

void ATower::CheckFireCondition()
{
	if (!Tank) {
		return;
	}

	if (IsInRange() && Tank->bAlive) {
		Fire();
	}
}
