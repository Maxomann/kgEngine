//_______EXCEPTION_H_______//

#pragma once
#include <string>
#include <map>

#define TEMPLATE_ERROR(type, message)(throw std::exception( (std::string( "_EXCEPTION_INFO_" ) + "\n" + "timestamp: " + __TIMESTAMP__ + "\n" + "file:      " + __FILE__ + "\n" + "line:      " + std::to_string( __LINE__ ) + "\n"+ "type:      " + type +"\n" + "what:      " + message).c_str() ))
#define REPORT_ERROR(message)(TEMPLATE_ERROR("null",message))
#define REPORT_ERROR_SCRIPT(message) (TEMPLATE_ERROR("skript",message))