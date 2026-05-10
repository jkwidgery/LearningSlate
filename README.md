# Developer Profile Plugin

A custom Unreal Engine 5 editor plugin that displays developer profile data as a formatted card inside the editor. Built as a focused learning exercise in Slate UI, custom asset types, and editor toolkits.
_Note all relevant source code can be found in Plugins/DeveloperProfile_

---

## Overview

The plugin introduces a **Developer Profile** asset — a UObject containing a developer's name, role, bio, contact info, portrait, and a list of skills with proficiency ratings. Double-clicking the asset opens a custom editor with two panels: a live-rendered profile card and a standard details view. Every change made in the details panel is reflected on the card in real time.

Two visual themes are included — **Turtle Rock** (dark) and **Pastel** — and switching between them updates the entire card dynamically without reopening the asset.

---

## Features

- Custom asset type visible in the Content Browser with its own category and color
- Custom two-tab editor: profile card + details panel side by side
- Portrait image or auto-generated initials avatar (switches dynamically via `SWidgetSwitcher`)
- Soft and hard skills displayed as labeled progress bars, each styled per theme
- Contact info rows that collapse when their fields are empty
- Full live reactivity — editing any property updates the card immediately
- Two switchable themes with per-theme colors, row styles, and progress bar fills

---

## Implementation Notes

### Custom Asset & Content Browser Registration

`UDeveloperProfileAsset` is a plain `UObject` with `UPROPERTY` fields for all profile data. It appears in the Content Browser through `FDeveloperProfileAssetTypeActions`, which implements `IAssetTypeActions` and registers with `IAssetTools` on module startup. A paired `UDeveloperProfileAssetFactory` handles the right-click → create flow.

### Editor Toolkit & Tab Layout

Opening the asset invokes `FDeveloperProfileEditorToolkit`, which extends `FAssetEditorToolkit`. `RegisterTabSpawners` registers two named tabs: one that spawns `SDeveloperProfileCardWidget` with the asset passed via `SLATE_ARGUMENT`, and one that spawns a standard `IDetailsView` pointed at the same asset.

### Profile Card Widget

`SDeveloperProfileCardWidget` is an `SCompoundWidget`. The card layout is an `SGridPanel` (3 columns, 3 rows) inside an `SBox` with fixed dimensions, wrapped in an `SScaleBox` so it scales to fit the panel:

| Cell | Content |
|------|---------|
| (0, 0–1) | Portrait — `SWidgetSwitcher` between texture image and initials avatar |
| (1–2, 0) | Name + role title |
| (1–2, 1) | Bio with auto word wrap |
| (0, 2) | Contact info with conditional row visibility |
| (1, 2) | Soft skills list |
| (2, 2) | Hard skills list |

### Skills — SListView & Row Generation

Each skills column is backed by a `TArray<TSharedPtr<FDeveloperSkill>>`. `SListView` calls `OnGenerateRow` per item, producing an `SHorizontalBox` with the skill name and an `SProgressBar`. The bars use `FSlateRoundedBoxBrush` for both the background and fill, with the brush defined in the style set rather than hardcoded in the widget.

### Theming & Live Updates

All colors and widget styles are stored in a named `FSlateStyleSet` (`FDeveloperProfileStyle`), keyed by theme prefix (e.g. `DeveloperProfile.TurtleRock.Color.Primary`). A `ThemeStyle()` helper on the widget builds the correct key at paint time using a stack buffer — no heap allocation per frame.

Live reactivity is driven by `FCoreUObjectDelegates::OnObjectPropertyChanged`. The handler dispatches on property name:

- **Portrait** — reloads the texture into the brush
- **Skills / skill fields / Theme** — calls `RebuildSkillsData()`, which re-allocates `TSharedPtr` items to force `SListView`'s row cache to miss, causing `OnGenerateRow` to fire with the updated theme style, then calls `RequestListRefresh()`

All color bindings use `TAttribute<FSlateColor>` lambdas that re-evaluate on every paint pass, so a single `Invalidate(Layout | Paint)` is sufficient to repaint the entire card for any property change.

---

## Engine Version

Unreal Engine 5.7
