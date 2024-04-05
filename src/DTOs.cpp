#pragma once

#include "oatpp/core/Types.hpp"

class PhoneBookEntry : public oatpp::DTO {

  DTO_INIT(PhoneBookEntry, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, phone);
  DTO_FIELD(String, name);
  DTO_FIELD(String, address);

};
