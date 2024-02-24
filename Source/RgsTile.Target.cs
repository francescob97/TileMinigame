// Copyright(c) Forge Reply. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RgsTileTarget : TargetRules
{
	public RgsTileTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("RgsTile");
	}
}
