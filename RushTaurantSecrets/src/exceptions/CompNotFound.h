#pragma once
#include <stdexcept>

namespace exceptions {
	class CompNotFound : std::exception {
	private:
		static std::string getMessage(const char* compReq, const char* compAsk) {
			return "Component " + std::string(compReq) + "was not found. " + compAsk + " needs this component to function.";
		}
	public:
		CompNotFound(const char* compReq, const char* compAsk) : std::exception(getMessage(compReq, compAsk).c_str()) { }
		CompNotFound(const std::string& compReq, const std::string& compAsk) : std::exception(getMessage(compReq.c_str(), compAsk.c_str()).c_str()) { }
	};
}