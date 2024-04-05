#pragma once

#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "controller/PhoneBookController.hpp"
#include "controller/SwaggerController.hpp"

class AppComponent {
public:

  OATPP_CREATE_COMPONENT(std::shared_ptr<PhoneBookController>, phoneBookController)([] {
    return std::make_shared<PhoneBookController>();
  }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<SwaggerController>, swaggerController)([] {
    return std::make_shared<SwaggerController>();
  }());

};