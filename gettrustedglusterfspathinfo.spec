Name:           gettrustedglusterfspathinfo
Version:        0.1
Release:        1%{?dist}
Summary:        Simple tool to access trusted.glusterfs.pathinfo xattr

License:        GPLv3
URL:            https://github.com/mattf/gettrustedglusterfspathinfo
Source0:        gettrustedglusterfspathinfo-0.1.tar.gz

BuildRequires:  /usr/include/attr/xattr.h

#Requires:       

%description
This is a simple tool for accessing pathinfo information of files in a
GlusterFS file system.


%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%make_install


%files
%doc COPYING README
%attr(4755,root,root) %{_bindir}/%{name}



%changelog
* Wed Aug 07 2013 <matt@redhat> - 0.1-1
- Initial release
