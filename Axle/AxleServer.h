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

#include <AxleDefines.h>

namespace Axle
{
	struct ServerConfig
	{
		ServerMode mode;
		unsigned int port;
#ifdef AXLE_MTTHREAD
		size_t thread_pool_size;
#endif
	};

	class Server
	{
		public:
			Server(ServerConfig config) 
				: configuration(config) 
			{
				
			}

			~Server() {}
		private:
			ServerConfig configuration;
	};
}