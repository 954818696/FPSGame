// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DawnBreakersTarget : TargetRules
{
	public DawnBreakersTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Game;
        ExtraModuleNames.Add("DawnBreakersEditorExtend");

    }

	//
	// TargetRules interface.
	//

	//public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.Add("DawnBreakers");
		
	//	if (UEBuildConfiguration.bBuildEditor)
 //       {
 //           OutExtraModuleNames.Add("DawnBreakersEditorExtend");
 //       }
	//}
}
