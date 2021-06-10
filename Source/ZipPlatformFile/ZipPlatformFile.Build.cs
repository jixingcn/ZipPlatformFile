using UnrealBuildTool;

public class ZipPlatformFile : ModuleRules
{
	public ZipPlatformFile(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			});
	}
}
