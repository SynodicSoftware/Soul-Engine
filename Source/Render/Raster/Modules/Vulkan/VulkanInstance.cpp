#include "VulkanInstance.h"

#include "Device/VulkanPhysicalDevice.h"
#include "Core/System/Compiler.h"
#include "Core/Utility/Exception/Exception.h"


VulkanInstance::VulkanInstance(const vk::ApplicationInfo& appInfo,
	nonstd::span<std::string> validationLayers,
	nonstd::span<std::string> requiredInstanceExtensions)
{

	std::vector<const char*> cValidationLayers;
	cValidationLayers.reserve(validationLayers.size());
	for (auto& layer : validationLayers) {

		cValidationLayers.push_back(layer.c_str());

	}

	std::vector<const char*> cInstanceExtensions;
	cInstanceExtensions.reserve(requiredInstanceExtensions.size());
	for (auto& extension : requiredInstanceExtensions) {

		cInstanceExtensions.push_back(extension.c_str());

	}

	vk::InstanceCreateInfo instanceCreationInfo;
	instanceCreationInfo.pApplicationInfo = &appInfo;
	instanceCreationInfo.enabledExtensionCount = static_cast<uint32>(cInstanceExtensions.size());
	instanceCreationInfo.ppEnabledExtensionNames = cInstanceExtensions.data();
	instanceCreationInfo.enabledLayerCount = static_cast<uint32>(cValidationLayers.size());
	instanceCreationInfo.ppEnabledLayerNames = cValidationLayers.data();

	instance_ = createInstance(instanceCreationInfo);

	dispatcher_ = vk::DispatchLoaderDynamic(instance_);

	if constexpr (Compiler::Debug()) {


		vk::DebugUtilsMessengerCreateInfoEXT messengerCreateInfo;
		messengerCreateInfo.flags = vk::DebugUtilsMessengerCreateFlagBitsEXT(0);
		messengerCreateInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
											  vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
		messengerCreateInfo.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
										  vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
										  vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
		messengerCreateInfo.pfnUserCallback = DebugCallback;
		messengerCreateInfo.pUserData = nullptr;

		debugMessenger_ =
			instance_.createDebugUtilsMessengerEXT(messengerCreateInfo, nullptr, dispatcher_);

	}

}

VulkanInstance::~VulkanInstance()
{

	if constexpr (Compiler::Debug()) {

		instance_.destroyDebugUtilsMessengerEXT(debugMessenger_, nullptr, dispatcher_);

	}

	instance_.destroy();
}

const vk::Instance& VulkanInstance::Handle()
{

	return instance_;

}

std::vector<VulkanPhysicalDevice> VulkanInstance::EnumeratePhysicalDevices()
{

	auto vkPhysicalDevices = instance_.enumeratePhysicalDevices();

	std::vector<VulkanPhysicalDevice> physicalDevices;

	for (auto& physicalDevice : vkPhysicalDevices) {

		physicalDevices.emplace_back(instance_, physicalDevice);

	}

	return physicalDevices;

}

VkBool32 VulkanInstance::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{

	throw NotImplemented();

}
