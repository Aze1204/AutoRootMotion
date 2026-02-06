[English](README.md) | [简体中文](README.zh-Hans.md)

# AutoRootMotion

AutoRootMotion is an Unreal Engine editor plugin that helps you batch/automatically manage **Root Motion** settings for animation assets (`UAnimSequence`).

> UE Version: **5.7** (tested). Other versions: best-effort.  
> Latest: **v1.1.0**

---

## Features

- Content Browser context menu for batch processing `UAnimSequence`
- **Auto-detect** whether an animation likely needs Root Motion (pelvis translation + threshold to filter small stationary jitters)
- Force **Enable Root Motion** / **Disable Root Motion**
- **Thumbnail badge**: shows a small **RM** badge on the animation thumbnail when **Root Motion is enabled** (quick visual cue)
- **Menu icons** for better readability in context menu actions
- **Simplified Chinese (zh-Hans) localization** for UI texts (menu/tooltip/settings)
- Feedback via notifications and logs

---

## Installation

### Option (Recommended): Project Plugin

Copy this plugin folder to: `YourProject/Plugins/`

Restart the editor. For C++ projects, you may be prompted to compile.

Enable it in:

`Edit → Plugins → AutoRootMotion`

---

## Usage

1. Select one or multiple `UAnimSequence` assets in **Content Browser**
2. Right-click → **AutoRootMotion**

Menu actions:

- **Detect Root Motion Automatically**
  - Enables Root Motion when rules strongly suggest it
  - Does **not** blindly override your existing manual choice (force changes are done via the explicit Enable/Disable actions)
- **Enable Root Motion**
  - Force enable for selected assets
- **Disable Root Motion**
  - Force disable for selected assets

---

## Thumbnail Badge (v1.1.0)

When an animation asset has **Root Motion enabled**, AutoRootMotion draws a small **RM** badge on the **top-right** corner of the thumbnail.

This helps you quickly spot which assets are currently using Root Motion without opening them one-by-one.

> Note: Thumbnails may be cached by the editor. After batch operations, you may need to reselect assets or refresh thumbnails to see the latest badge state.

---

## Localization (Simplified Chinese)

AutoRootMotion ships with **zh-Hans** translations.

To enable:

1. `Edit → Editor Preferences → Region & Language`
2. Set **Editor Language** to **Simplified Chinese (zh-Hans)**
3. Restart the editor

> If you’re distributing the plugin, make sure the plugin package includes the localization resources under:
> `Plugins/AutoRootMotion/Content/Localization/AutoRootMotion/...`

---

## Auto Detection Rules (V1)

Goal: detect meaningful locomotion-like translation while filtering small stationary movements (reload/idle twist, etc).

- Samples pelvis (default bone name: `pelvis`) at animation start/end
- Computes translation delta
- If delta length > **Movement Threshold**, it's treated as meaningful motion

Notes:

- If your skeleton uses a different pelvis name (e.g. `Pelvis`, `hip`), update it in code (settings page planned).
- Threshold is project-dependent (10uu ≈ 10cm is a common starting point).

---

## Changelog

### v1.1.0
- Added **thumbnail RM badge** for assets with Root Motion enabled
- Added **context menu icons** for better UX
- Added **Simplified Chinese (zh-Hans) localization** for UI texts
- Minor fixes and UX improvements

### v1.0.0
- Initial release: context menu actions + V1 auto detection rules

---

## Roadmap

- Project Settings page: `Project Settings → Plugins → AutoRootMotion`
  - Enable Post Import
  - Movement Threshold
  - Pelvis Bone Name
- Post-import auto run (optional)
- Content browser tags (beyond thumbnail badge)
- Audit report export (CSV) / richer UI
- Undo/Redo support (Scoped transactions)

---

## Contributing

Issues and PRs are welcome. Please include:

- UE version
- Repro steps
- Sample assets (if possible)

---

## Contact

Have ideas or suggestions? Email:

**aze.unreal@outlook.com**