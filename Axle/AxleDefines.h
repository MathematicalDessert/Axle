/*
 * Copyright 2017 Pkamara
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN // We don't need all windows bloat
#	include <Windows.h>
#endif

#include <map>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <sstream>
#include <shared_mutex>
#include <cassert>

#ifdef AXLE_USE_BOOST
#	ifdef AXLE_MTTHREAD
#		include <boost/thread>
#	endif
#	include <boost/regex.hpp>
#else
#	ifdef AXLE_MTTHREAD
#		include <thread>
#	endif
#	include <regex>
#endif

namespace Axle // Most Axle things should go under this namespace
{
	/* 
		ServerMode

		MODE_HTTP - Server only handles HTTP requests
		MODE_HTTPS - Server only handles HTTPS requests
		MODE_MIXED - Server accepts both HTTP and HTTPS (REQUIRES MULTI-THREADING)
	*/
	enum class ServerMode
	{
		MODE_HTTP, // Only HTTP
		MODE_HTTPS, // Only accept HTTPS
#ifdef AXLE_MTTHREAD
		/* 
		 * Mixed mode should only be active if Multi-Threading is active
		 * would be a massive pain and would be slow to do both HTTP and
		 * HTTPS in one thread.
		 *
		 * ~ Pkamara
		 */
		MODE_MIXED // Mixed both HTTP/HTTPS
#endif
	};

	enum class SocketType
	{
		TYPE_HTTP,
		TYPE_HTTPS
	};
}