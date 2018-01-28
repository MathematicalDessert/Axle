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
	typedef std::function<void(void)> taskFunction;

	class TaskedWorkerClass
	{
		public:
			TaskedWorkerClass() {}
			virtual ~TaskedWorkerClass() {}

			virtual void preCall()
			{
				// Before the actual function is called
			}

			virtual void funcCall()
			{
				preCall();
				// Call the real function!
				postCall();
			}

			virtual void postCall()
			{
				// After the actual function is called
			}
		protected:
			
	};

	enum class TASK_PRIORITY
	{
		LOW, // Not that imporant
		MEDIUM,
		HIGH,
		CORE // Needs to be done first
	};

	enum class TASK_STATUS
	{
		WAITING,
		SUCCESS,
		YIELD,
		FAILED
	};

	enum class TASK_TYPE
	{
		OBJECT,
		FUNCTION
	};

	struct TASK
	{
		TASK_PRIORITY priority;
		TASK_STATUS result;
		TASK_TYPE type;

		union
		{
			// SIGH POINTERS.
			TaskedWorkerClass *taskClass;
			taskFunction *taskFunction;
		};
	};

	class Scheduler
	{
		public:
			static Scheduler& getSingleton(size_t thread_pool_size); // We only want ONE scheduler (and only in one thread)
		private:
			Scheduler(size_t thread_pool_size)
				: servicingThreads(0)
			{
				for (unsigned int i = 0; i < thread_pool_size; i++)
				{
					thread_pool.push_back(std::thread(&Scheduler::schedulerMainThread, this));
				}
			}

			~Scheduler()
			{
				thread_pool.clear();
				assert(servicingThreads == 0);
			}

			std::condition_variable new_task_scheduled;
			mutable std::mutex new_task_mutex;

			std::vector<std::thread> thread_pool;
			std::vector<TASK> pending_tasks;

			int servicingThreads;
			bool stopScheduler = false;
			bool stopSchedulerWhenEmpty = false;

			void schedulerMainThread();
	};
}