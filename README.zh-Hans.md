[English](README.md) | [简体中文](README.zh-Hans.md)

# AutoRootMotion

AutoRootMotion 是一个 Unreal Engine 编辑器插件，用于批量/自动管理动画资源（`UAnimSequence`）的**根运动（Root Motion）**设置。

> UE 版本：**5.7**（已测试）  
> 最新版本：**v1.1.0**

---

## 功能特性

- Content Browser 右键菜单：批量处理 `UAnimSequence`
- **自动检测**动画是否可能需要根运动（骨盆位移 + 阈值过滤小幅抖动）
- 强制 **启用根运动** / **禁用根运动**
- **缩略图角标提示**：动画资产勾选了根运动时，缩略图右上角显示 **RM** 角标（快速识别）
- 右键菜单项带 **小图标**（更易读）
- **简体中文（zh-Hans）本地化**：菜单/提示文本支持中文
- 通过通知（Notification）与日志提供执行反馈

---

## 安装

### 方案（推荐）：项目插件（Project Plugin）

将整个插件目录复制到：

`YourProject/Plugins/AutoRootMotion/`

重启编辑器。若是 C++ 项目，可能会提示编译。

在此处启用插件：

`Edit → Plugins → AutoRootMotion`

---

## 使用方法

1. 在 **Content Browser** 中选中一个或多个 `UAnimSequence`
2. 右键 → **AutoRootMotion**

菜单功能：

- **自动检测根运动**
  - 当规则强烈建议时启用根运动
  - 不会盲目覆盖你的手动选择（强制修改请用显式的“启用/禁用”操作）
- **启用根运动**
  - 对所选动画强制启用
- **禁用根运动**
  - 对所选动画强制禁用

---

## 缩略图角标（v1.1.0）

当某个动画资产**启用了根运动**时，AutoRootMotion 会在缩略图右上角绘制一个 **RM** 角标，帮助你不打开资产也能快速确认状态。

> 注：缩略图可能存在缓存。批量修改后如未立即更新，可尝试重新选中资源/刷新 Content Browser。

---

## 简体中文本地化（zh-Hans）

插件已内置简体中文翻译。

启用方式：

1. `Edit → Editor Preferences → Region & Language`
2. 将 **Editor Language** 设置为 **Simplified Chinese (zh-Hans)**
3. 重启编辑器

分发给他人时，请确保插件包中包含本地化资源目录，例如：

`Plugins/AutoRootMotion/Content/Localization/AutoRootMotion/zh-Hans/AutoRootMotion.locres`

并在 `.uplugin` 中配置 `LocalizationTargets`（已配置则忽略）。

---

## 自动检测规则（V1）

目标：检测“有意义的位移移动”（更像移动/位移驱动的动画），并过滤站立小幅抖动（换弹/Idle 扭动等）。

- 采样骨盆（默认骨骼名：`pelvis`）在动画起点/终点的位置
- 计算位移差（Translation Delta）
- 若位移长度 > **Movement Threshold**，则认为存在有意义的移动

说明：

- 不同骨架骨盆命名不同（如 `Pelvis`、`hip`），目前需在代码中调整（后续会做设置页）
- 阈值和项目单位相关（10uu ≈ 10cm 是常见起点）

---

## 更新日志

### v1.1.0
- 新增：**缩略图 RM 角标**（启用根运动的动画会显示角标）
- 新增：右键菜单项 **小图标**，提升可读性
- 新增：**简体中文（zh-Hans）本地化**
- 若干小修复与体验优化

### v1.0.0
- 首发版本：右键菜单批处理 + V1 自动检测规则

---

## 规划路线图

- 设置页：`Project Settings → Plugins → AutoRootMotion`
  - 导入后自动处理（Post Import）
  - Movement Threshold
  - Pelvis Bone Name
- 可选：导入后自动运行
- Content Browser 标签/更丰富的提示（在角标之外）
- 审计报告导出（CSV）/更丰富 UI
- Undo/Redo 支持（Scoped Transactions）

---

## 贡献

欢迎提 Issue / PR，请尽量提供：

- UE 版本
- 复现步骤
- 可能的话附带示例资源

---

## 联系方式

有想法或建议？邮件联系：

**aze.unreal@outlook.com**