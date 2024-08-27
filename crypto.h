#pragma once

#include <string>
#include <vector>

std::string sha256(const std::string &s);
std::vector<unsigned char> base64_decode(const std::string& input);
std::string blowfish_decode(const std::vector<unsigned char>& ciphertext, const std::string& key, const std::string& iv);