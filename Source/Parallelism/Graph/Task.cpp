#include "Task.h"

#include "Parallelism/Scheduler/SchedulerModule.h"

Task::Task(std::shared_ptr<SchedulerModule>& scheduler, std::function<void()>&& callable) noexcept:
	scheduler_(scheduler),
	callable_(std::forward<std::function<void()>>(callable))
{

}

void Task::Execute(std::chrono::nanoseconds targetDuration) {
	
	scheduler_->AddTask(parameters_, [this]()
	{
		std::invoke(std::forward<std::function<void()>>(callable_));

		for (const auto& child : children_) {

			child->Execute();

		}

		scheduler_->Block();
	});

}