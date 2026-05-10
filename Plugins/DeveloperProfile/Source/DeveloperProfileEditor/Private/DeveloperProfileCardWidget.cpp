#include "DeveloperProfileCardWidget.h"

void SDeveloperProfileCardWidget::Construct(const FArguments& Args)
{
	Asset = Args._DeveloperProfileAsset;
	ChildSlot
	[
		SNew(SGridPanel)//portait
		+SGridPanel::Slot(0, 0)
		.RowSpan(2)
		[
			SNew(STextBlock).Text(FText::FromString("Portrait"))
			//SNew(SImage) //profile texture, or maybe initials?
			//.Image(this, Asset->Portrait)
		]
		+SGridPanel::Slot(1, 0)//name and title
		.ColumnSpan(2)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text_Lambda([this]() { return FText::FromString(Asset->DisplayName); })//developer name
				//TODO: Make size bigger during styling phase
			]
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text_Lambda([this]() { return FText::FromString(Asset->RoleTitle); })
			]
		]
		+SGridPanel::Slot(1, 1)//bio
		.ColumnSpan(2)
		[
			SNew(STextBlock)
			.Text_Lambda([this]() { return FText::FromString(Asset->Bio); })
		]
		+SGridPanel::Slot(0, 2)//contact info
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text_Lambda([this]() { return FText::FromString(Asset->ContactInfo.Email); })
			]
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text_Lambda([this]() { return FText::FromString(Asset->ContactInfo.LinkedIn); })
			]
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text_Lambda([this]() { return FText::FromString(Asset->ContactInfo.Phone); })
			]
		]
		+SGridPanel::Slot(1, 2)//soft skills
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)//Skills header
				.Text(FText::FromString("Soft Skills"))//TODO: Center this
			]
			//todo, for each skill, add a skill title + progress bar entry
		]
		+SGridPanel::Slot(2, 2)//hard skills
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SNew(STextBlock)//Skills header
				.Text(FText::FromString("Hard Skills"))//TODO: Center this
			]
			//todo, for each skill, add a skill title + progress bar entry
		]
	];
}
