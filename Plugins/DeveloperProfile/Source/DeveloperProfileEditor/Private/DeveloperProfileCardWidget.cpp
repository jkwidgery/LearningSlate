#include "DeveloperProfileCardWidget.h"

#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "DeveloperProfileStyle.h"
#include "Widgets/Notifications/SProgressBar.h"

void SDeveloperProfileCardWidget::Construct(const FArguments& Args)
{
    Asset = Args._DeveloperProfileAsset;

    OnPropertyChangedHandle = FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(
    this, &SDeveloperProfileCardWidget::OnObjectPropertyChanged);

    RebuildSkillsData();

    if (UTexture2D* Texture = Asset->Portrait.LoadSynchronous())
    {
        PortraitBrush.SetResourceObject(Texture);
    }

    ChildSlot
    .HAlign(HAlign_Center)
    .VAlign(VAlign_Center)
    [
        SNew(SScaleBox)
        .Stretch(EStretch::ScaleToFit)
        [
            SNew(SBox)
            .HeightOverride(500.0f)
            .WidthOverride(1000.0f)
            [
                SNew(SGridPanel)
                .FillColumn(0, 0.302f)
                .FillColumn(1, 0.349f)
                .FillColumn(2, 0.349f)
                .FillRow(0, 0.20f)
                .FillRow(1, 0.20f)
                .FillRow(2, 0.60f)
                +SGridPanel::Slot(0, 0)
                .RowSpan(2)
                [
                    BuildPortraitSection()
                ]
                +SGridPanel::Slot(1, 0)
                .ColumnSpan(2)
                [
                    BuildHeaderSection()
                ]
                +SGridPanel::Slot(1, 1)
                .ColumnSpan(2)
                [
                    BuildBioSection()
                ]
                +SGridPanel::Slot(0, 2)
                [
                    BuildContactSection()
                ]
                +SGridPanel::Slot(1, 2)
                [
                    BuildSkillsSection(ESkillType::Soft)
                ]
                +SGridPanel::Slot(2, 2)
                [
                    BuildSkillsSection(ESkillType::Hard)
                ]
            ]
        ]
    ];
}

SDeveloperProfileCardWidget::~SDeveloperProfileCardWidget()
{
    FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(OnPropertyChangedHandle);
}

FName SDeveloperProfileCardWidget::ThemeStyle(const TCHAR* Key) const
{
    const TCHAR* Prefix;
    switch (Asset->Theme)
    {
        case EProfileTheme::Pastel:     Prefix = TEXT("DeveloperProfile.Pastel.");     break;
        case EProfileTheme::TurtleRock:
        default:                        Prefix = TEXT("DeveloperProfile.TurtleRock."); break;
    }
    TCHAR Buf[128];
    FCString::Strcpy(Buf, Prefix);
    FCString::Strcat(Buf, Key);
    return FName(Buf);
}

FText SDeveloperProfileCardWidget::GetInitials() const
{
    TArray<FString> OutNames;
    FString Initials;
    Asset->DisplayName.ParseIntoArray(OutNames, TEXT(" "), true);
    for (const FString& Word : OutNames)
    {
        if (!Word.IsEmpty())
            Initials.AppendChar(Word[0]);
    }
    return FText::FromString(Initials);
}

void SDeveloperProfileCardWidget::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
    if (Object != Asset.Get())
        return;

    const FName PropName = PropertyChangedEvent.GetPropertyName();

    if (PropName == GET_MEMBER_NAME_CHECKED(UDeveloperProfileAsset, Portrait))
    {
        UTexture2D* Texture = Asset->Portrait.LoadSynchronous();
        PortraitBrush.SetResourceObject(Texture);
    }
    else if (PropName == GET_MEMBER_NAME_CHECKED(UDeveloperProfileAsset, Skills)
          || PropName == GET_MEMBER_NAME_CHECKED(FDeveloperSkill, SkillName)
          || PropName == GET_MEMBER_NAME_CHECKED(FDeveloperSkill, Proficiency)
          || PropName == GET_MEMBER_NAME_CHECKED(FDeveloperSkill, SkillType)
          || PropName == GET_MEMBER_NAME_CHECKED(UDeveloperProfileAsset, Theme))
    {
        RebuildSkillsData();
        if (SoftSkillsListView) SoftSkillsListView->RequestListRefresh();
        if (HardSkillsListView) HardSkillsListView->RequestListRefresh();
    }

    Invalidate(EInvalidateWidgetReason::Layout | EInvalidateWidgetReason::Paint);
}

void SDeveloperProfileCardWidget::RebuildSkillsData()
{
    SoftSkills.Empty();
    HardSkills.Empty();

    if (!Asset)
        return;

    for (const FDeveloperSkill& Skill : Asset->Skills)
    {
        TSharedPtr<FDeveloperSkill> SkillPtr = MakeShared<FDeveloperSkill>(Skill);
        if (Skill.SkillType == ESkillType::Soft)
            SoftSkills.Add(SkillPtr);
        else
            HardSkills.Add(SkillPtr);
    }
}

TSharedRef<ITableRow> SDeveloperProfileCardWidget::OnGenerateSkillRow(TSharedPtr<FDeveloperSkill> Skill, const TSharedRef<STableViewBase>& OwnerTable)
{
    return SNew(STableRow<TSharedPtr<FDeveloperSkill>>, OwnerTable)
        .Style(&FDeveloperProfileStyle::Get().GetWidgetStyle<FTableRowStyle>(ThemeStyle(TEXT("TableRow.Skills"))))
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(0.f, 0.f, 8.f, 0.f)
            [
                SNew(STextBlock)
                .Text(FText::FromString(Skill->SkillName))
                .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Secondary"))
                .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                    return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.TextSecondary")));
                }))
            ]
            +SHorizontalBox::Slot()
            .FillWidth(1.0f)
            .Padding(0.f, 2.f, 0.f, 5.f)
            .VAlign(VAlign_Center)
            [
                SNew(SBox)
                .HeightOverride(20.f)
                [
                    SNew(SProgressBar)
                    .Percent(Skill->Proficiency / 100.0f)
                    .Style(&FDeveloperProfileStyle::Get().GetWidgetStyle<FProgressBarStyle>(
                        Skill->SkillType == ESkillType::Soft
                            ? ThemeStyle(TEXT("ProgressBar.Soft"))
                            : ThemeStyle(TEXT("ProgressBar.Hard"))))
                ]
            ]
        ];
}

TSharedRef<SWidget> SDeveloperProfileCardWidget::BuildPortraitSection()
{
    return SNew(SBorder)
        .BorderImage(FDeveloperProfileStyle::Get().GetBrush("DeveloperProfile.Brush.Solid"))
        .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
            return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.SectionBg.Portrait")));
        }))
        [
            SNew(SWidgetSwitcher)
            .WidgetIndex_Lambda([this](){ return Asset->Portrait.IsValid() ? 0 : 1; })
            +SWidgetSwitcher::Slot()
            [
                SNew(SScaleBox)
                .Stretch(EStretch::ScaleToFit)
                [
                    SNew(SImage)
                    .Image(&PortraitBrush)
                ]
            ]
            +SWidgetSwitcher::Slot()
            [
                SNew(SBorder)
                .HAlign(HAlign_Center)
                .VAlign(VAlign_Center)
                .Padding(2.f)
                .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                    return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.Primary")));
                }))
                [
                    SNew(STextBlock)
                    .TransformPolicy(ETextTransformPolicy::ToUpper)
                    .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Initials"))
                    .Text_Lambda([this](){ return GetInitials(); })
                ]
            ]
        ];
}

TSharedRef<SWidget> SDeveloperProfileCardWidget::BuildHeaderSection()
{
    return SNew(SBorder)
        .BorderImage(FDeveloperProfileStyle::Get().GetBrush("DeveloperProfile.Brush.Solid"))
        .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
            return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.SectionBg.Accent")));
        }))
        .Padding(8.f)
        [
            SNew(SVerticalBox)
            +SVerticalBox::Slot()
            .AutoHeight()
            .HAlign(HAlign_Center)
            [
                SNew(STextBlock)
                .Text_Lambda([this]() { return FText::FromString(Asset->DisplayName); })
                .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Header"))
                .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                    return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.TextPrimary")));
                }))
            ]
            +SVerticalBox::Slot()
            .AutoHeight()
            .HAlign(HAlign_Center)
            [
                SNew(STextBlock)
                .Text_Lambda([this]() { return FText::FromString(Asset->RoleTitle); })
                .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Title"))
                .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                    return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.Primary")));
                }))
            ]
        ];
}

TSharedRef<SWidget> SDeveloperProfileCardWidget::BuildBioSection()
{
    return SNew(SBorder)
        .BorderImage(FDeveloperProfileStyle::Get().GetBrush("DeveloperProfile.Brush.Solid"))
        .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
            return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.SectionBg.Base")));
        }))
        .Padding(8.f)
        .VAlign(VAlign_Center)
        [
            SNew(STextBlock)
            .Text_Lambda([this]() { return FText::FromString(Asset->Bio); })
            .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Default"))
            .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.TextSecondary")));
            }))
            .AutoWrapText(true)
        ];
}

TSharedRef<SWidget> SDeveloperProfileCardWidget::BuildContactSection()
{
    const float LabelWidth = 90.f;

    auto MakeContactRow = [&](const FString& Label, TAttribute<FText> Value)
    {
        return SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SNew(SBox)
                .WidthOverride(LabelWidth)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(Label))
                    .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Default"))
                    .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                        return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.Primary")));
                    }))
                ]
            ]
            +SHorizontalBox::Slot()
            .FillWidth(1.0f)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(Value)
                .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Secondary"))
                .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                    return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.TextSecondary")));
                }))
            ];
    };

    TSharedRef<SVerticalBox> ContactBox = SNew(SVerticalBox)
        +SVerticalBox::Slot()
        .AutoHeight()
        .HAlign(HAlign_Center)
        .Padding(0.f, 0.f, 0.f, 6.f)
        [
            SNew(STextBlock)
            .Text(FText::FromString("Contact Info"))
            .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Default"))
            .TransformPolicy(ETextTransformPolicy::ToUpper)
            .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.PrimaryLight")));
            }))
        ];

    ContactBox->AddSlot()
    .AutoHeight()
    .Padding(0.f, 2.f)
    [
        SNew(SBox)
        .Visibility_Lambda([this]() { return Asset->ContactInfo.Email.IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible; })
        [
            MakeContactRow("Email:", TAttribute<FText>::CreateLambda([this](){ return FText::FromString(Asset->ContactInfo.Email); }))
        ]
    ];

    ContactBox->AddSlot()
    .AutoHeight()
    .Padding(0.f, 2.f)
    [
        SNew(SBox)
        .Visibility_Lambda([this]() { return Asset->ContactInfo.LinkedIn.IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible; })
        [
            MakeContactRow("LinkedIn:", TAttribute<FText>::CreateLambda([this](){ return FText::FromString(Asset->ContactInfo.LinkedIn); }))
        ]
    ];

    ContactBox->AddSlot()
    .AutoHeight()
    .Padding(0.f, 2.f)
    [
        SNew(SBox)
        .Visibility_Lambda([this]() { return Asset->ContactInfo.Phone.IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible; })
        [
            MakeContactRow("Phone:", TAttribute<FText>::CreateLambda([this](){ return FText::FromString(Asset->ContactInfo.Phone); }))
        ]
    ];

    return SNew(SBorder)
        .BorderImage(FDeveloperProfileStyle::Get().GetBrush("DeveloperProfile.Brush.Solid"))
        .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
            return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.SectionBg.Accent")));
        }))
        .Padding(8.f)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            ContactBox
        ];
}

TSharedRef<SWidget> SDeveloperProfileCardWidget::BuildSkillsSection(ESkillType SkillType)
{
    TArray<TSharedPtr<FDeveloperSkill>>& SkillsArray = SkillType == ESkillType::Soft ? SoftSkills : HardSkills;

    TSharedPtr<SListView<TSharedPtr<FDeveloperSkill>>> ListView;

    SAssignNew(ListView, SListView<TSharedPtr<FDeveloperSkill>>)
        .ListItemsSource(&SkillsArray)
        .OnGenerateRow(this, &SDeveloperProfileCardWidget::OnGenerateSkillRow)
        .SelectionMode(ESelectionMode::None)
        .ListViewStyle(&FDeveloperProfileStyle::Get().GetWidgetStyle<FTableViewStyle>("DeveloperProfile.TableView.Transparent"));

    if (SkillType == ESkillType::Soft)
        SoftSkillsListView = ListView;
    else
        HardSkillsListView = ListView;

    TSharedRef<SVerticalBox> SkillsBox = SNew(SVerticalBox)
        +SVerticalBox::Slot()
        .AutoHeight()
        .Padding(0.f, 5.f, 0.f, 5.f)
        .HAlign(HAlign_Center)
        [
            SNew(STextBlock)
            .Text(SkillType == ESkillType::Soft
                ? FText::FromString("Soft Skills")
                : FText::FromString("Hard Skills"))
            .Font(FDeveloperProfileStyle::Get().GetFontStyle("DeveloperProfile.Font.Title"))
            .ColorAndOpacity(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
                return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.Primary")));
            }))
        ]
        +SVerticalBox::Slot()
        .FillHeight(1.0f)
        .Padding(0.f, 5.f, 0.f, 0.f)
        [
            ListView.ToSharedRef()
        ];

    return SNew(SBorder)
        .BorderImage(FDeveloperProfileStyle::Get().GetBrush("DeveloperProfile.Brush.Solid"))
        .BorderBackgroundColor(TAttribute<FSlateColor>::CreateLambda([this]() -> FSlateColor {
            return FDeveloperProfileStyle::Get().GetColor(ThemeStyle(TEXT("Color.SectionBg.Skills")));
        }))
        .Padding(8.f)
        [
            SkillsBox
        ];
}
