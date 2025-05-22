// ftpd is a server implementation based on the following:
// - RFC  959 (https://tools.ietf.org/html/rfc959)
// - RFC 3659 (https://tools.ietf.org/html/rfc3659)
// - suggested implementation details from https://cr.yp.to/ftp/filesystem.html
// - Deflate transmission mode for FTP
//   (https://tools.ietf.org/html/draft-preston-ftpext-deflate-04)
//
// Copyright (C) 2024 Michael Theall
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "platform.h"

extern char const *const g_dearImGuiVersion;
extern char const *const g_dearImGuiCopyright;
extern char const *const g_mitLicense;

#ifdef __3DS__
extern char const *const g_libctruVersion;
extern char const *const g_citro3dVersion;
extern char const *const g_citro3dCopyright;
#endif

#ifdef __SWITCH__
extern char const *const g_libnxVersion;
extern char const *const g_deko3dVersion;
extern char const *const g_zstdVersion;
extern char const *const g_libnxCopyright;
extern char const *const g_deko3dCopyright;
extern char const *const g_zstdCopyright;
extern char const *const g_libnxLicense;
extern char const *const g_zstdLicense;
#endif

#if !defined(__NDS__)
extern char const *const g_zlibLicense;
#endif

#if !defined(__NDS__) && !defined(__3DS__) && !defined(__SWITCH__)
extern char const *const g_glfwVersion;
extern char const *const g_glfwCopyright;
#else
extern char const *const g_globVersion;
extern char const *const g_globCopyright;
extern char const *const g_globLicense;

extern char const *const g_collateVersion;
extern char const *const g_collateCopyright;
extern char const *const g_collateLicense;
#endif
