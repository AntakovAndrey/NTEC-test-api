#pragma once

#include "oatpp-swagger/Controller.hpp"
#include "oatpp-swagger/Resources.hpp"

class SwaggerController {
public:
  static std::shared_ptr<oatpp::swagger::Controller> createShared() {
    return oatpp::swagger::Controller::createShared("/api-docs/swagger.json", 
                                                    "http://localhost:8000");
  }
};
