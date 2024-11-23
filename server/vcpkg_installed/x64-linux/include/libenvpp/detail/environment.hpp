#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace env::detail {

#if LIBENVPP_PLATFORM_WINDOWS

std::optional<std::string> convert_string(const std::wstring& str);
std::optional<std::wstring> convert_string(const std::string& str);

#endif

[[nodiscard]] std::unordered_map<std::string, std::string> get_environment();

[[nodiscard]] std::optional<std::string> get_environment_variable(const std::string_view name);

void set_environment_variable(const std::string_view name, const std::string_view value);

void delete_environment_variable(const std::string_view name);

class set_scoped_environment_variable {
  public:
	set_scoped_environment_variable() = delete;
	set_scoped_environment_variable(const std::string_view name, const std::string_view value)
	    : m_name(name), m_old_value(get_environment_variable(name))
	{
		set_environment_variable(name, value);
	}

	set_scoped_environment_variable(const set_scoped_environment_variable&) = delete;
	set_scoped_environment_variable(set_scoped_environment_variable&&) = default;

	set_scoped_environment_variable& operator=(const set_scoped_environment_variable&) = delete;
	set_scoped_environment_variable& operator=(set_scoped_environment_variable&&) = default;

	~set_scoped_environment_variable()
	{
		if (m_old_value.has_value()) {
			set_environment_variable(m_name, *m_old_value);
		} else {
			delete_environment_variable(m_name);
		}
	}

  private:
	std::string m_name;
	std::optional<std::string> m_old_value;
};

[[nodiscard]] std::optional<std::string>
find_similar_env_var(const std::string_view var_name, const std::unordered_map<std::string, std::string>& environment,
                     const int edit_distance_cutoff);

std::optional<std::string> pop_from_environment(const std::string_view env_var,
                                                std::unordered_map<std::string, std::string>& environment);

} // namespace env::detail
