/* ****************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#ifndef __MEDIA_PLAYEROBSERVERWORKER_HPP
#define __MEDIA_PLAYEROBSERVERWORKER_HPP

#include <thread>
#include <memory>
#include <mutex>
#include <media/MediaPlayer.h>
#include "MediaQueue.h"

namespace media {
typedef enum player_observer_command_e {
	PLAYER_OBSERVER_COMMAND_STARTED,
	PLAYER_OBSERVER_COMMAND_FINISHIED,
	PLAYER_OBSERVER_COMMAND_ERROR
} player_observer_command_t;

class PlayerObserverWorker
{
public:
	PlayerObserverWorker();
	~PlayerObserverWorker();

	static PlayerObserverWorker& getWorker();
	player_result_t startWorker();
	void stopWorker();
	MediaQueue& getQueue();

private:
	int entry();

private:
	static std::unique_ptr<PlayerObserverWorker> mWorker;
	static std::once_flag mOnceFlag;
	int mRefCnt;
	bool mIsRunning;
	std::thread mWorkerThread;
	MediaQueue mObserverQueue; // observer queue
	std::mutex mRefMtx;  // reference cnt mutex
};
} // namespace media

#endif