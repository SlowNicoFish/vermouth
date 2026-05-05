[![Build AppImage](https://github.com/dekomote/vermouth/actions/workflows/build-appimage.yml/badge.svg)](https://github.com/dekomote/vermouth/actions/workflows/build-appimage.yml)
[![Build DEB](https://github.com/dekomote/vermouth/actions/workflows/build-deb.yml/badge.svg)](https://github.com/dekomote/vermouth/actions/workflows/build-deb.yml)
[![Build RPM](https://github.com/dekomote/vermouth/actions/workflows/build-rpm.yml/badge.svg)](https://github.com/dekomote/vermouth/actions/workflows/build-rpm.yml)
[![Build Flatpak](https://github.com/dekomote/vermouth/actions/workflows/build-flatpak.yml/badge.svg)](https://github.com/dekomote/vermouth/actions/workflows/build-flatpak.yml)
[![Build Arch Package](https://github.com/dekomote/vermouth/actions/workflows/build-arch.yml/badge.svg)](https://github.com/dekomote/vermouth/actions/workflows/build-arch.yml)
[![Discord](https://img.shields.io/badge/Discord-Join%20Server-5865F2?logo=discord&logoColor=white)](https://discord.gg/RmppukhVYq)


<p align="center">
  <img src="assets/com.dekomote.vermouth.svg" width="128" height="128" alt="Vermouth logo">
</p>

<h1 align="center">Vermouth</h1>

<p align="center">A game and app launcher for Linux - native, Windows, and retro.<br>
KDE-first, lightweight, no frills.</p>

<p align="center">
  <img src="assets/screen1.png?t=1.41" alt="Vermouth screenshot" width="400">
  <img src="assets/screen2.png?t=1.5" alt="Vermouth screenshot" width="400"><br>
  <img src="assets/screen3.png?t=1.3" alt="Vermouth screenshot" width="400">
  <img src="assets/screen4.png?t=1.3" alt="Vermouth screenshot" width="400"><br>
  <img src="assets/screen6.png?t=1.5" alt="Vermouth screenshot" width="800"><br>
  <img src="assets/screen7.png?t=1.5" alt="Vermouth screenshot" width="400">
</p>

## What it does

Vermouth is a KDE-first launcher with four modes:

- **Windows games** - run `.exe` files with Proton or Wine, with umu-launcher support for full Steam Runtime compatibility
- **Native apps** - launch Linux binaries, `.desktop` entries, and AppImages directly
- **Steam games** - import your installed Steam library with one click and launch games directly via Steam
- **Retro games** - browse and launch your [RomM](https://github.com/rommapp/romm) library via RetroArch, with platform filtering, cover art, and ROM downloads; or add ROM files directly to your library

It works like Lutris, Heroic, or Bottles, but lighter and KDE-first - less buttons, checks and knobs, just the bare necessities.

- Searches for Proton versions from your Steam installation automatically, including GE-Proton
- Download the latest GE-Proton with one click if you don't have Steam
- Custom Proton builds go in `~/.local/share/vermouth/protons`
- Wine works too - point it at the binary and set a prefix folder
- Extracts icons from `.exe` files automatically (requires `icoutils`)
- Launch options with `%command%` placeholder, same as Steam (e.g. `mangohud %command%`, `GAMEID=12345 %command%`)
- Run a separate `.exe` inside an existing prefix (useful for installers and config tools)
- Run common Wine utilities - winecfg, regedit, winetricks
- Create start menu entries and desktop shortcuts that work without opening Vermouth
- Prevent the system from sleeping while a game is running
- Toggle HDR per-session on KDE - sets the required Proton environment variables automatically
- Big screen / Big Picture mode with full gamepad navigation
- SteamGridDB integration for icons, grid art, hero images, and logos
- Import your Steam library and launch games via Steam in one click
- Add ROM files directly to your library and launch them via RetroArch, independent of RomM
- RomM integration - see notes below.


### umu-launcher support

Vermouth supports [umu-launcher](https://github.com/Open-Wine-Components/umu-launcher), which runs Proton through the full Steam Runtime (pressure-vessel). This significantly improves game compatibility - especially for games with video cutscenes, media codecs, or anti-cheat. It is strongly recommended.

If `umu-run` is found in your `PATH` or configured in Settings, Vermouth will use it automatically for all Proton launches. You can also download it directly from Settings → umu-launcher.


### SteamGridDB support

Vermouth supports [SteamGridDB](https://www.steamgriddb.com) for fetching icons, grid and hero images and logos. You need an API key which you can get by registering an account with them and getting your API key [here](https://www.steamgriddb.com/profile/preferences/api)


### Steam support

Vermouth can import your installed Steam library in one click. Go to **Add → Import from Steam**, select the games you want, and they will appear in your library. Launching them opens Steam directly to that game. Art is fetched from your local Steam cache automatically; any missing artwork is downloaded from SteamGridDB if you have an API key configured.

Steam is detected from all standard install locations, including native and Flatpak installs.


### RetroArch support

ROMs can be added to your library directly — no RomM required. Click **Add App/Game**, select **RetroArch** as the runtime, pick the ROM file and platform, and it will appear in your library alongside your other games.

Vermouth auto-detects RetroArch cores for each platform. You can override the core per entry from the right-click menu → **Change Core**.


### RomM support

Vermouth integrates with [RomM](https://github.com/rommapp/romm), a self-hosted retro game library manager. Point Vermouth at your RomM server URL and API key in Settings, and the RomM tab will let you browse platforms and ROMs, download them locally, and launch them with RetroArch.

ROMs are launched via RetroArch. Vermouth will auto-detect whether RetroArch is installed natively or as a Flatpak. You can assign a RetroArch core per platform in Settings, or override it per game from the right-click menu. Cores must be installed separately in RetroArch before use.

## Installing


### Fedora and Nobara

Vermouth is available on [COPR](https://copr.fedorainfracloud.org/coprs/dekomote/Vermouth/):

```bash
sudo dnf copr enable dekomote/Vermouth
sudo dnf install vermouth
```

### Bazzite

```bash
sudo dnf5 copr enable dekomote/Vermouth
sudo rpm-ostree -y install vermouth
```

Also, you can download the latest package from the [releases page](https://github.com/dekomote/vermouth/releases/latest).

```bash
sudo dnf install ./vermouth-*.rpm
```

### OpenSUSE Tumbleweed

Install via COPR:

```bash
sudo zypper addrepo https://copr.fedorainfracloud.org/coprs/dekomote/Vermouth/repo/opensuse-tumbleweed/dekomote-Vermouth-opensuse-tumbleweed.repo
sudo zypper install vermouth
```

Or install the RPM from the [releases page](https://github.com/dekomote/vermouth/releases/latest):

```bash
sudo zypper install ./vermouth-opensuse-*.rpm
```

### Ubuntu / Debian

Requires Ubuntu 25.04 / Debian Trixie or newer (Qt 6.8+ and KF6 are required).
Download the latest deb package from the [releases page](https://github.com/dekomote/vermouth/releases/latest).

```bash
sudo apt install ./vermouth-*.deb
```

### Arch Linux / CachyOS

Install from the [AUR](https://aur.archlinux.org/packages/vermouth):

```bash
yay -S vermouth
```

Or install the package from the [releases page](https://github.com/dekomote/vermouth/releases/latest):

```bash
sudo pacman -U vermouth-*-arch.pkg.tar.zst
```

Or build from the included PKGBUILD:

```bash
cd packaging && makepkg -si
```

### Flatpak

Download the latest flatpak package from the [releases page](https://github.com/dekomote/vermouth/releases/latest).

```bash
flatpak install ./vermouth-*.flatpak
```

See [FLATPAK NOTES](#flatpak-notes) for filesystem permissions required to access your games and Steam installation.

### AppImage

Download `Vermouth-*.AppImage` from the [releases page](https://github.com/dekomote/vermouth/releases/latest), make it executable and run it:

```bash
chmod +x Vermouth-*.AppImage
./Vermouth-*.AppImage
```

---

For icon extraction from .exe files, install `icoutils` (provides `wrestool` and `icotool`).


## Building from source

You need Qt 6.8+, KDE Frameworks 6, and CMake.

**Fedora:**
```bash
sudo dnf install cmake gcc-c++ extra-cmake-modules qt6-qtbase-devel qt6-qtdeclarative-devel \
  qt6-qtquickcontrols2-devel kf6-kirigami-devel kf6-kcoreaddons-devel kf6-ki18n-devel \
  kf6-qqc2-desktop-style icoutils
```

**Ubuntu / Debian:**
```bash
sudo apt install build-essential cmake extra-cmake-modules qt6-base-dev qt6-declarative-dev \
  qt6-tools-dev-tools libkirigami-dev libkf6coreaddons-dev libkf6i18n-dev \
  libkf6qqc2desktopstyle-dev icoutils
```

**Arch Linux:**
```bash
sudo pacman -S --needed base-devel cmake ninja extra-cmake-modules qt6-base qt6-declarative \
  kirigami ki18n kcoreaddons qqc2-desktop-style icoutils
```

Then inside the root folder of the project:

```bash
cmake -B build
cmake --build build
./build/bin/vermouth
```

## Bug reporting and feature requests

Please use the [issue tracker](https://github.com/dekomote/vermouth/issues) for bug reports and feature requests.

## How to use it

**Windows / native games:** Click **Add App/Game**, browse for the `.exe` or binary, choose a runtime (Proton, Wine, or native), and launch from the grid. Optional fields can be omitted - the name and icon are inferred automatically (requires `icoutils` for `.exe` icons), and the prefix is set based on the game name.

The **Launch Options** field wraps the command with tools like `mangohud`, `gamescope`, or `gamemoderun`. Use `%command%` as the placeholder - if omitted, options are prepended automatically. You can also set environment variables here, e.g. `GAMEID=12345 %command%` to pass a Steam App ID to umu-launcher.

**Steam games:** Click **Add → Import from Steam**. Vermouth scans your Steam library, shows all installed games, and lets you select which ones to import. Already-imported games are greyed out. Art is resolved from your local Steam cache and any gaps are filled from SteamGridDB automatically.

**RetroArch games:** Click **Add App/Game**, select **RetroArch** as the runtime, choose the ROM file and platform. Vermouth will pick the right core automatically or prompt you to select one.

**Retro games via RomM:** Configure your RomM server URL and API key in Settings. Switch to the **RomM** tab, pick a platform from the toolbar, and double-click a ROM to download and launch it. Cores can be assigned per platform in Settings or overridden per game via right-click.

In **Settings** you can:
- Configure [umu-launcher](#umu-launcher-support) for better game compatibility
- Set the default prefix folder and extra Proton scan paths
- Set your RomM server URL, API key, and ROM cache directory
- Configure RetroArch cores per platform

## FLATPAK NOTES

When running Vermouth as a Flatpak, it is sandboxed and cannot access your filesystem by default. You need to grant it access to the folder(s) containing your games using [Flatseal](https://flathub.org/apps/com.github.tchx84.Flatseal) or your desktop environment's application permissions settings. Add the relevant paths under **Filesystem** permissions.

To detect Proton versions from your Steam installation, add `~/.steam:ro` and `~/.local/share/Steam:ro`.

To create desktop shortcuts for your games, add `xdg-desktop` to filesystem permissions.

## How it works

Games are stored in `~/.config/vermouth/apps.json`. When umu-launcher is available, Proton is launched through it with `PROTONPATH` and `STEAM_COMPAT_DATA_PATH` set. Without umu, Vermouth calls the `proton run` script directly, the same way Steam does. Wine games get `WINEPREFIX` set and the binary called directly.

## Contributing

Contributions are welcome. Please open a pull request on [GitHub](https://github.com/dekomote/vermouth).

### Code

Build from source (see [Building from source](#building-from-source)), make your changes, and open a pull request. Keep changes focused - one feature or fix per PR.

### Translations

Vermouth uses the KDE i18n system (gettext `.po` files). To add or update a translation:

1. Create a folder `po/<language_code>/` (e.g. `po/fr/` for French, `po/pt_BR/` for Brazilian Portuguese).
2. Copy `po/vermouth.pot` into it as `vermouth.po` (e.g. `po/fr/vermouth.po`).
3. Fill in the `msgstr` fields with your translations.
4. Open a pull request with your new folder.

To update an existing translation after new strings have been added:

```bash
sh po/Messages.sh       # regenerate vermouth.pot from source
sh po/update-po.sh      # merge new strings into all .po files
```

Then fill in any new empty `msgstr ""` entries in your `.po` file.

## AI Disclaimer

The code has been developed, reviewed and tested by a human. However, development included assistance of AI tools, so keep that in mind.
