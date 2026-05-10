#pragma once
#include "DeveloperProfileAsset.h"

class SDeveloperProfileCardWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDeveloperProfileCardWidget)
		{}
		SLATE_ARGUMENT(UDeveloperProfileAsset*, DeveloperProfileAsset)
	SLATE_END_ARGS()

	void Construct(const FArguments& Args);

	~SDeveloperProfileCardWidget();

private:
	TObjectPtr<UDeveloperProfileAsset> Asset;

	FSlateBrush PortraitBrush;

	TArray<TSharedPtr<FDeveloperSkill>> SoftSkills;
	TArray<TSharedPtr<FDeveloperSkill>> HardSkills;

	TSharedPtr<SListView<TSharedPtr<FDeveloperSkill>>> SoftSkillsListView;
	TSharedPtr<SListView<TSharedPtr<FDeveloperSkill>>> HardSkillsListView;

	FDelegateHandle OnPropertyChangedHandle;
	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);

	void RebuildSkillsData();
	TSharedRef<ITableRow> OnGenerateSkillRow(TSharedPtr<FDeveloperSkill> Skill, const TSharedRef<STableViewBase>& OwnerTable);

	//helper functions
	TSharedRef<SWidget> BuildPortraitSection();
	TSharedRef<SWidget> BuildHeaderSection();
	TSharedRef<SWidget> BuildBioSection();
	TSharedRef<SWidget> BuildContactSection();
	TSharedRef<SWidget> BuildSkillsSection(ESkillType SkillType);

	FText GetInitials() const;
	FName ThemeStyle(const TCHAR* Key) const;
	
};
