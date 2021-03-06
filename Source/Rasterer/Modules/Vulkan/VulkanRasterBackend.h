#pragma once

#include "Rasterer/RasterModule.h"

#include "VulkanSwapChain.h"

#include <vulkan/vulkan.hpp>
#include <glm/vec2.hpp>


class SchedulerModule;
class WindowModule;
class VulkanDevice;
class VulkanSwapChain;


class VulkanRasterBackend final : public RasterModule {

public:

	VulkanRasterBackend(std::shared_ptr<SchedulerModule>&,
		std::shared_ptr<WindowModule>&);
	~VulkanRasterBackend() override;

	VulkanRasterBackend(const VulkanRasterBackend &) = delete;
	VulkanRasterBackend(VulkanRasterBackend &&) noexcept = default;

	VulkanRasterBackend& operator=(const VulkanRasterBackend &) = delete;
	VulkanRasterBackend& operator=(VulkanRasterBackend &&) noexcept = default;

	void Render() override;

	uint RegisterSurface(std::any, glm::uvec2) override;
	void UpdateSurface(uint, glm::uvec2) override;
	void RemoveSurface(uint) override;

	void Draw() override;
	void DrawIndirect() override;
	void UpdateBuffer() override;
	void UpdateTexture() override;
	void CopyBuffer() override;
	void CopyTexture() override;


	vk::Instance& GetInstance();


private:

	//TODO: replace the uint id with Entity maybe?

	static uint surfaceCounter;

	std::unordered_map<uint, vk::SurfaceKHR> surfaces_;
	std::unordered_map<uint, std::unique_ptr<VulkanSwapChain>> swapChains_;

	std::vector<char const*> requiredInstanceExtensions_;
	std::vector<const char*> validationLayers_;

	vk::Instance instance_;
	std::vector<std::shared_ptr<VulkanDevice>> devices_;

	//Dynamic dispatcher for extensions
	vk::DispatchLoaderDynamic dispatcher_;

	//Debug state 
	//TODO: Should be conditionally included when the class is only debug mode.

	static VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);

	vk::DebugUtilsMessengerEXT debugMessenger_;
	vk::DebugReportCallbackEXT callback_;

};