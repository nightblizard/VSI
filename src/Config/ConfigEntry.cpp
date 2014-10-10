#include "ConfigEntry.h"

namespace Config
{
	template <>
	std::string ConfigEntry::To<std::string>() const
	{
		return mValue;
	}

	template <>
	std::uint64_t ConfigEntry::To<std::uint64_t>() const
	{
		return std::stoull(mValue);
	}

	template <>
	std::uint32_t ConfigEntry::To<std::uint32_t>() const
	{
		return std::stoul(mValue);
	}

	template <>
	std::uint16_t ConfigEntry::To<std::uint16_t>() const
	{
		return static_cast<std::uint16_t>(std::stoul(mValue));
	}

	template <>
	std::uint8_t ConfigEntry::To<std::uint8_t>() const
	{
		return static_cast<std::uint8_t>(std::stoul(mValue));
	}

	template <>
	std::int64_t ConfigEntry::To<std::int64_t>() const
	{
		return std::stoll(mValue);
	}

	template <>
	std::int32_t ConfigEntry::To<std::int32_t>() const
	{
		return std::stol(mValue);
	}

	template <>
	std::int16_t ConfigEntry::To<std::int16_t>() const
	{
		return static_cast<std::int16_t>(std::stoul(mValue));
	}

	template <>
	std::int8_t ConfigEntry::To<std::int8_t>() const
	{
		return static_cast<std::int8_t>(std::stoul(mValue));
	}

	template <>
	bool ConfigEntry::To<bool>() const
	{
		return To<std::int8_t>() != 0;
	}

	template <>
	float ConfigEntry::To<float>() const
	{
		return std::stof(mValue);
	}

	template <>
	double ConfigEntry::To<double>() const
	{
		return std::stod(mValue);
	}

	bool ConfigEntry::IsEmpty() const
	{
		return mValue.empty();
	}

	ConfigEntry::ConfigEntry(const std::string& value) :
		mValue(value)
	{
	}
}