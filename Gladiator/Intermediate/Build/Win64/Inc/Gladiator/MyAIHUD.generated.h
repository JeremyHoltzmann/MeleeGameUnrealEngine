// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

#ifdef GLADIATOR_MyAIHUD_generated_h
#error "MyAIHUD.generated.h already included, missing '#pragma once' in MyAIHUD.h"
#endif
#define GLADIATOR_MyAIHUD_generated_h

#define AMyAIHUD_EVENTPARMS
#define AMyAIHUD_RPC_WRAPPERS
#define AMyAIHUD_CALLBACK_WRAPPERS
#define AMyAIHUD_INCLASS \
	private: \
	static void StaticRegisterNativesAMyAIHUD(); \
	friend GLADIATOR_API class UClass* Z_Construct_UClass_AMyAIHUD(); \
	public: \
	DECLARE_CLASS(AMyAIHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, Gladiator, NO_API) \
	/** Standard constructor, called after all reflected properties have been initialized */    NO_API AMyAIHUD(const class FPostConstructInitializeProperties& PCIP); \
	DECLARE_SERIALIZER(AMyAIHUD) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#undef UCLASS_CURRENT_FILE_NAME
#define UCLASS_CURRENT_FILE_NAME AMyAIHUD


#undef UCLASS
#undef UINTERFACE
#if UE_BUILD_DOCS
#define UCLASS(...)
#else
#define UCLASS(...) \
AMyAIHUD_EVENTPARMS
#endif


#undef GENERATED_UCLASS_BODY
#undef GENERATED_IINTERFACE_BODY
#define GENERATED_UCLASS_BODY() \
public: \
	AMyAIHUD_RPC_WRAPPERS \
	AMyAIHUD_CALLBACK_WRAPPERS \
	AMyAIHUD_INCLASS \
public:

