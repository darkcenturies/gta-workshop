#pragma once

#include <string>

namespace reportpaths {

// Preserve diagnostic paths while hiding the Windows account directory.
std::string RedactUserProfile(const char* text, const char* userProfile);

// Relative paths belong to the game; absolute paths are local only when they
// are beneath the GTA SA root.
bool IsGameLocal(const char* path, const char* gameRoot);

}  // namespace reportpaths
