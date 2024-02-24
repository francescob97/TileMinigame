// Copyright(c) Forge Reply. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class RgsTileEditorTarget : TargetRules
{
	public RgsTileEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("RgsTile");
	}
}
