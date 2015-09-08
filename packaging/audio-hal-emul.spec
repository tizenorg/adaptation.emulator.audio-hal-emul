Name:       audio-hal-emul
Summary:    TIZEN Audio HAL for Emulator
Version:    0.1.5
Release:    0
Group:      System/Libraries
License:    Apache-2.0
URL:        http://tizen.org
Source0:    audio-hal-emul-%{version}.tar.gz
BuildRequires: pkgconfig(vconf)
BuildRequires: pkgconfig(alsa)
BuildRequires: pkgconfig(iniparser)
BuildRequires: pkgconfig(dlog)

%description
TIZEN Audio HAL for Emulator

%prep
%setup -q -n %{name}-%{version}

%build
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS ?“DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"

%autogen
%configure

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
cp LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}

%make_install

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-,root,root,-)
/usr/lib/libtizen-audio.so
/usr/share/license/%{name}
