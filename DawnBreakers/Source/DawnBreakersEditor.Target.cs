// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DawnBreakersEditorTarget : TargetRules
{
	public DawnBreakersEditorTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Editor;
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
	//	//OutExtraModuleNames.Add("DawnBreakers");
	//	OutExtraModuleNames.AddRange( new string[] { "DawnBreakersEditorExtend"} );
	//}
}
