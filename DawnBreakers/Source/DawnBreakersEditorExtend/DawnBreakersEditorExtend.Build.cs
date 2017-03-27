namespace UnrealBuildTool.Rules
{
	public class DawnBreakersEditorExtend : ModuleRules
	{
		public DawnBreakersEditorExtend( TargetInfo Target )
		{

			/*
			PublicIncludePaths.AddRange(
					new string[] 
					{
						"DawnBreakersEditorExtend/Public",
					}
				);
				
			PrivateIncludePaths.AddRange(
					new string[] 
					{
						"DawnBreakersEditorExtend/Private",
					}
				);
			*/


			PublicDependencyModuleNames.AddRange(
					new string[]
					{
						"DawnBreakers",
					}
				);

			PrivateDependencyModuleNames.AddRange(
					new string[]
					{
						"UnrealEd",
                        "Core",
                        "CoreUObject",
                        "Engine",
                        "PropertyEditor",
                        "Slate",
                        "SlateCore",
                        "InputCore"
                    }
				);

			DynamicallyLoadedModuleNames.AddRange(
					new string[]
					{
						// ... add any modules that your module loads dynamically here ...
					}
				);
		}
	}
}
