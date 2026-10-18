# Changelog

## [1.2.1] - 2026-10-17

### Fixed
- **Face Appearance Management Capability Gate (Skyrim SE 1.5.97 / RaceMenu 0.4.16)**:
  - Fixed face whitening and over-illumination loops caused by reading unmodulated BASE tint list on runtimes without RaceMenu Overlay v2 (`overlayTintMasks`).
  - Gated all face tint rebaking, private face texture creation, delayed rebake polling, and tint list reassertions behind `MakeupApi::FaceManagementEnabled()`, which couples `[Compat] bManageFaceAppearance` with `OverlayApi::Available()`.
  - Replaced dynamic runtime pointer checks (`HasOverlayList`) with static capability discovery (`OverlayApi::Available()`), ensuring consistent behavior across race switches and character editor sessions.
  - Fully gated `MakeupApi::ReassertSkinTone` and `MakeupApi::NoteHeartbeat` in `WorldWatch` heartbeat loop when face appearance management is disabled.
  - Decoupled `LookFaceTint::Apply` from tint rebake gates so looks that provide exported `FR_*.dds` head textures properly restore their textures on head rebuilds.
  - Preserved `g_rebakeOwed` debt in `RunOwedFaceRebake` if evaluated while the gate is closed.
- **Makeup UI Availability Feedback**:
  - Display explicit disabled explanation in `OverlaysUI` when face management is disabled or when running on unsupported legacy RaceMenu versions, rather than silently discarding edits.
- **Head Dismemberment Sweep Overdraw (Skyrim SE / High Poly Head)**:
  - Fixed face overexposure/whitening artifact where `BipedPost::RestoreHeadPartPartitions` swept slot 130 (`BP_HEAD`), erroneously unhiding suppressed underlying facial partitions (e.g. on High Poly Head or custom meshes) during post-load settle ladder sweeps.
  - Restricted head partition restoration strictly to hair (131/141), circlet (142), and ears (143) to prevent double-rendered facial meshes.

### Build & Tooling
- Added `NOMINMAX` compile definitions to eliminate Windows SDK macro collisions with `std::min`/`std::max`.
- Added unit test `FaceManagementGateTests` (`tests/test_facemanagementgate.cpp`) covering all decision matrix states.
