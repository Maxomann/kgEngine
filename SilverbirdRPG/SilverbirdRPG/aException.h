//_______EXCEPTION_H_______//

#pragma once
#include <string>
#include <map>

#define TEMPLATE_ERROR(type, message)(throw std::exception( (std::string( "_EXCEPTION_INFO_" ) + "\n" + "timestamp: " + __TIMESTAMP__ + "\n" + "file:      " + __FILE__ + "\n" + "line:      " + std::to_string( __LINE__ ) + "\n"+ "type:      " + type +"\n" + "what:      " + message).c_str() ))
#define REPORT_ERROR(message)(TEMPLATE_ERROR("undefined",message))
#define REPORT_ERROR_FILEACCESS(message)(TEMPLATE_ERROR("file access", message))
#define REPORT_ERROR_SCRIPT(message) (TEMPLATE_ERROR("script",message))
#define REPORT_ERROR_NOT_IMPLEMENTED() (TEMPLATE_ERROR("not implemented",""));
