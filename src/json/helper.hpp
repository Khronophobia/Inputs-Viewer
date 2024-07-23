#pragma once

template<typename T>
[[nodiscard]]
bool verifyJsonObject(matjson::Value const& json, std::string_view key) {
    if (json.contains(key)) {
        return json[key].is<T>();
    }

    return false;
}