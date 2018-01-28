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

#include <AxleScheduler.h>

namespace Axle
{
	Scheduler &Scheduler::getSingleton(size_t thread_pool_size)
	{
		static Scheduler scheduler(thread_pool_size);
		return scheduler;
	}

	void Scheduler::schedulerMainThread()
	{
		std::unique_lock<std::mutex> lock(new_task_mutex);
		++servicingThreads;

		while (!stopScheduler && !(stopSchedulerWhenEmpty && pending_tasks.empty()))
		{
			try
			{
				while (!stopScheduler && !stopSchedulerWhenEmpty && pending_tasks.empty())
				{
					new_task_scheduled.wait(lock); // Just yield while we wait for a new task
				}

				if (stopScheduler)
				{
					break;
				}

				lock.unlock();
				// do task
				lock.lock();
			}
			catch (...)
			{
				--servicingThreads;
				// Need a way to tell func that error occured
				throw;
			}

		}

		--servicingThreads;
	}
}