#include "DeveloperProfileStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateTypes.h"
#include "Brushes/SlateRoundedBoxBrush.h"
TSharedPtr<FSlateStyleSet> FDeveloperProfileStyle::StyleInstance = nullptr;


void FDeveloperProfileStyle::Initialize()
{
	if (StyleInstance.IsValid())
		return;

	StyleInstance = Create();
	FSlateStyleRegistry::RegisterSlateStyle(Get());
}

const ISlateStyle& FDeveloperProfileStyle::Get()
{
	return *StyleInstance;
}

void FDeveloperProfileStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(Get());
	StyleInstance.Reset();
}

FName FDeveloperProfileStyle::GetStyleSetName()
{
	return FName("Developer Profile Style");
}

TSharedRef<FSlateStyleSet> FDeveloperProfileStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShared<FSlateStyleSet>(GetStyleSetName());

	// TurtleRock theme
	Style->Set("DeveloperProfile.TurtleRock.Color.SectionBg.Accent",   FLinearColor(0.18f,  0.22f,  0.11f,  1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.SectionBg.Base",     FLinearColor(0.08f,  0.08f,  0.08f,  1.f));
	{
		const FLinearColor SkillsBg(0.04f, 0.06f, 0.02f, 1.f);
		const FSlateBrush  SkillsBgBrush = FSlateColorBrush(SkillsBg);

		Style->Set("DeveloperProfile.TurtleRock.Color.SectionBg.Skills", SkillsBg);
		
		FTableRowStyle RowStyle;
		RowStyle
			.SetEvenRowBackgroundBrush(SkillsBgBrush)
			.SetOddRowBackgroundBrush(SkillsBgBrush)
			.SetEvenRowBackgroundHoveredBrush(SkillsBgBrush)
			.SetOddRowBackgroundHoveredBrush(SkillsBgBrush)
			.SetActiveBrush(SkillsBgBrush)
			.SetActiveHighlightedBrush(SkillsBgBrush)
			.SetInactiveBrush(SkillsBgBrush)
			.SetInactiveHighlightedBrush(SkillsBgBrush)
			.SetSelectorFocusedBrush(SkillsBgBrush);
		Style->Set("DeveloperProfile.TurtleRock.TableRow.Skills", RowStyle);
	}
	Style->Set("DeveloperProfile.TurtleRock.Color.SectionBg.Portrait", FLinearColor(0.0f,   0.0f,   0.0f,   1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.Primary",        FLinearColor(0.541f, 0.604f, 0.357f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.PrimaryDark",    FLinearColor(0.361f, 0.408f, 0.251f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.PrimaryLight",   FLinearColor(0.722f, 0.780f, 0.541f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.Background",     FLinearColor(0.059f, 0.059f, 0.059f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.Surface",        FLinearColor(0.118f, 0.118f, 0.118f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.TextPrimary",    FLinearColor(0.941f, 0.941f, 0.941f, 1.f));
	Style->Set("DeveloperProfile.TurtleRock.Color.TextSecondary",  FLinearColor(0.604f, 0.604f, 0.604f, 1.f));
	{
		const float BarRadius = 6.f;
		const FLinearColor BarBg(0.118f, 0.118f, 0.118f, 1.f);
		auto MakeBar = [&](FLinearColor Fill)
		{
			FProgressBarStyle S;
			S.BackgroundImage = FSlateRoundedBoxBrush(BarBg, BarRadius);
			S.FillImage       = FSlateRoundedBoxBrush(Fill, BarRadius);
			return S;
		};
		Style->Set("DeveloperProfile.TurtleRock.ProgressBar.Soft", MakeBar(FLinearColor(0.722f, 0.780f, 0.541f, 1.f)));
		Style->Set("DeveloperProfile.TurtleRock.ProgressBar.Hard", MakeBar(FLinearColor(0.361f, 0.408f, 0.251f, 1.f)));
	}

	// Pastel theme
	Style->Set("DeveloperProfile.Pastel.Color.SectionBg.Accent",   FLinearColor(0.82f, 0.77f, 0.92f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.SectionBg.Base",     FLinearColor(0.94f, 0.92f, 0.97f, 1.f));
	{
		const FLinearColor SkillsBg(0.78f, 0.89f, 0.95f, 1.f);
		const FSlateBrush  SkillsBgBrush = FSlateColorBrush(SkillsBg);

		Style->Set("DeveloperProfile.Pastel.Color.SectionBg.Skills", SkillsBg);

		FTableRowStyle RowStyle;
		RowStyle
			.SetEvenRowBackgroundBrush(SkillsBgBrush)
			.SetOddRowBackgroundBrush(SkillsBgBrush)
			.SetEvenRowBackgroundHoveredBrush(SkillsBgBrush)
			.SetOddRowBackgroundHoveredBrush(SkillsBgBrush)
			.SetActiveBrush(SkillsBgBrush)
			.SetActiveHighlightedBrush(SkillsBgBrush)
			.SetInactiveBrush(SkillsBgBrush)
			.SetInactiveHighlightedBrush(SkillsBgBrush)
			.SetSelectorFocusedBrush(SkillsBgBrush);
		Style->Set("DeveloperProfile.Pastel.TableRow.Skills", RowStyle);
	}
	Style->Set("DeveloperProfile.Pastel.Color.SectionBg.Portrait", FLinearColor(0.96f, 0.87f, 0.90f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.Primary",        FLinearColor(0.28f, 0.16f, 0.48f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.PrimaryDark",    FLinearColor(0.18f, 0.10f, 0.32f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.PrimaryLight",   FLinearColor(0.40f, 0.26f, 0.62f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.Background",     FLinearColor(0.95f, 0.94f, 0.98f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.Surface",        FLinearColor(0.88f, 0.86f, 0.94f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.TextPrimary",    FLinearColor(0.06f, 0.04f, 0.10f, 1.f));
	Style->Set("DeveloperProfile.Pastel.Color.TextSecondary",  FLinearColor(0.22f, 0.18f, 0.30f, 1.f));
	{
		const float BarRadius = 6.f;
		const FLinearColor BarBg(0.38f, 0.56f, 0.94f, 1.f);
		auto MakeBar = [&](FLinearColor Fill)
		{
			FProgressBarStyle S;
			S.BackgroundImage = FSlateRoundedBoxBrush(BarBg, BarRadius);
			S.FillImage       = FSlateRoundedBoxBrush(Fill, BarRadius);
			return S;
		};
		Style->Set("DeveloperProfile.Pastel.ProgressBar.Soft", MakeBar(FLinearColor(0.72f, 0.60f, 0.88f, 1.f)));
		Style->Set("DeveloperProfile.Pastel.ProgressBar.Hard", MakeBar(FLinearColor(0.50f, 0.35f, 0.72f, 1.f)));
	}

	// Fonts (shared across themes)
	Style->Set("DeveloperProfile.Font.Header",    FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 30, "Bold"));
	Style->Set("DeveloperProfile.Font.Title",     FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 20, "Bold"));
	Style->Set("DeveloperProfile.Font.Default",   FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 15, "Regular"));
	Style->Set("DeveloperProfile.Font.Secondary", FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 12, "Regular"));
	Style->Set("DeveloperProfile.Font.Tertiary",  FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 10, "Regular"));
	Style->Set("DeveloperProfile.Font.Initials",  FSlateFontInfo(FAppStyle::GetFontStyle("NormalFont").CompositeFont, 50, "Italic"));

	// Shared styles
	{
		FTableViewStyle TransparentStyle;
		TransparentStyle.SetBackgroundBrush(FSlateColorBrush(FLinearColor::Transparent));
		Style->Set("DeveloperProfile.TableView.Transparent", TransparentStyle);
	}
	Style->Set("DeveloperProfile.Brush.Solid", new FSlateColorBrush(FLinearColor::White));
	return Style;
}
