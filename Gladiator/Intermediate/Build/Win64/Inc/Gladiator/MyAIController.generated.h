// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

#ifdef GLADIATOR_MyAIController_generated_h
#error "MyAIController.generated.h already included, missing '#pragma once' in MyAIController.h"
#endif
#define GLADIATOR_MyAIController_generated_h

#define AMyAIController_EVENTPARMS
#define AMyAIController_RPC_WRAPPERS
#define AMyAIController_CALLBACK_WRAPPERS
#define AMyAIController_INCLASS \
	private: \
	static void StaticRegisterNativesAMyAIController(); \
	friend GLADIATOR_API class UClass* Z_Construct_UClass_AMyAIController(); \
	public: \
	DECLARE_CLASS(AMyAIController, AAIController, COMPILED_IN_FLAGS(0), 0, Gladiator, NO_API) \
	/** Standard constructor, called after all reflected properties have been initialized */    NO_API AMyAIController(const class FPostConstructInitializeProperties& PCIP); \
	DECLARE_SERIALIZER(AMyAIController) \
	/** Indicates whether the class is compiled into the engine */    enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#undef UCLASS_CURRENT_FILE_NAME
#define UCLASS_CURRENT_FILE_NAME AMyAIController


#undef UCLASS
#undef UINTERFACE
#if UE_BUILD_DOCS
#define UCLASS(...)
#else
#define UCLASS(...) \
AMyAIController_EVENTPARMS
#endif


#undef GENERATED_UCLASS_BODY
#undef GENERATED_IINTERFACE_BODY
#define GENERATED_UCLASS_BODY() \
public: \
	AMyAIController_RPC_WRAPPERS \
	AMyAIController_CALLBACK_WRAPPERS \
	AMyAIController_INCLASS \
public:

