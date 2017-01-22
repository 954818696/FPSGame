// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"

/**
 * 
 */


DAWNBREAKERS_API DECLARE_LOG_CATEGORY_EXTERN(GameDebugInfo, Log, All);
DAWNBREAKERS_API DECLARE_LOG_CATEGORY_EXTERN(GameDebugError, Error, All);
DAWNBREAKERS_API DECLARE_LOG_CATEGORY_EXTERN(GameDebugWarning, Warning, All);


#define DAWNBREAKERS_LOG_INFO(formatStr, ...) UE_LOG(GameDebugInfo, Log, TEXT(formatStr), ##__VA_ARGS__)
#define DAWNBREAKERS_LOG_ERROR(formatStr, ...) UE_LOG(GameDebugError, Error, TEXT(formatStr), ##__VA_ARGS__)
#define DAWNBREAKERS_LOG_WARNING(formatStr, ...) UE_LOG(GameDebugWarning, Warning, TEXT(formatStr), ##__VA_ARGS__)

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

