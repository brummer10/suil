/* Suil, an LV2 plugin UI hosting library.
 * Copyright 2011 David Robillard <d@drobilla.net>
 *
 * Suil is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Suil is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SUIL_INTERNAL_H
#define SUIL_INTERNAL_H

#include <assert.h>
#include <stdlib.h>

#include <dlfcn.h>

#include "suil/suil.h"

#define SUIL_ERRORF(fmt, ...) fprintf(stderr, "error: %s: " fmt, \
                                      __func__, __VA_ARGS__)

struct _SuilUI {
	char* uri;
	char* type_uri;
	char* bundle_path;
	char* binary_path;
};

typedef struct _SuilUI* SuilUI;

struct _SuilUIs {
	char*   plugin_uri;
	SuilUI* uis;
	size_t  n_uis;
};
	
struct _SuilInstance {
	void*                   lib_handle;
	const LV2UI_Descriptor* descriptor;
	LV2UI_Handle            handle;
	LV2UI_Widget            widget;
};

typedef void (*SuilVoidFunc)();

/** dlsym wrapper to return a function pointer (without annoying warning) */
static inline SuilVoidFunc
suil_dlfunc(void* handle, const char* symbol)
{
	typedef SuilVoidFunc (*VoidFuncGetter)(void*, const char*);
	VoidFuncGetter dlfunc = (VoidFuncGetter)dlsym;
	return dlfunc(handle, symbol);
}

#endif  // SUIL_INTERNAL_H
