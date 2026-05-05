# COPR SCM builds inject %commit and %shortcommit automatically.
# For local builds: rpmbuild --define "commit <fullhash>" --define "shortcommit <7charhash>"
%global commit      %{?commit}%{!?commit:0000000000000000000000000000000000000000}
%global shortcommit %(c=%{commit}; echo ${c:0:7})

Name:           vermouth
Version:        1.6.3
Release:        0^git%{shortcommit}%{?dist}
Summary:        A game and app launcher for Linux - native, Windows, and retro
License:        MIT
URL:            https://github.com/dekomote/vermouth
Source0:        %{url}/archive/%{commit}/%{name}-%{shortcommit}.tar.gz

BuildRequires:  cmake >= 3.20
BuildRequires:  extra-cmake-modules
BuildRequires:  git

%if 0%{?suse_version}
BuildRequires:  gcc-c++
BuildRequires:  qt6-base-devel
BuildRequires:  qt6-declarative-devel
BuildRequires:  kf6-kirigami-devel
BuildRequires:  kf6-kcoreaddons-devel
BuildRequires:  kf6-ki18n-devel
BuildRequires:  kf6-qqc2-desktop-style-devel
BuildRequires:  icoutils
BuildRequires:  SDL2-devel
%else
BuildRequires:  qt6-qtbase-devel
BuildRequires:  qt6-qtdeclarative-devel
BuildRequires:  qt6-qtquickcontrols2-devel
BuildRequires:  kf6-kirigami-devel
BuildRequires:  kf6-kcoreaddons-devel
BuildRequires:  kf6-ki18n-devel
BuildRequires:  kf6-qqc2-desktop-style
BuildRequires:  icoutils
BuildRequires:  SDL2-devel
%endif

%if 0%{?suse_version}
Requires:       libQt6Core6
Requires:       libQt6Gui6
Requires:       libQt6Network6
Requires:       libQt6DBus6
Requires:       libQt6Widgets6
Requires:       libQt6Qml6
Requires:       libQt6Quick6
Requires:       libQt6QuickControls2-6
Requires:       kf6-kirigami
%else
Requires:       qt6-qtbase
Requires:       qt6-qtdeclarative
Requires:       qt6-qtquickcontrols2
Requires:       kf6-kirigami
%endif
Recommends:     icoutils
Recommends:     SDL2

%description
Vermouth is a KDE-first game and application launcher. Run native Linux apps
and games, Windows titles through Proton or Wine, and retro games via your
RomM library with RetroArch - all from one place.

This package tracks the development branch and may be unstable.

%prep
%autosetup -n %{name}-%{commit}

%build
%cmake
%cmake_build

%install
%cmake_install

%files
%license LICENSE
%{_bindir}/vermouth
%{_datadir}/applications/com.dekomote.vermouth.desktop
%{_datadir}/icons/hicolor/scalable/apps/com.dekomote.vermouth.svg
%{_datadir}/metainfo/com.dekomote.vermouth.metainfo.xml
%{_datadir}/locale/*/LC_MESSAGES/vermouth.mo

%changelog
* Tue May 05 2026 Dejan Noveski <deko@duck.com> - 0^git
- Git snapshot package
