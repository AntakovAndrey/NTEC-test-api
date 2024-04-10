
#ifndef EXAMPLE_POSTGRESQL_USERSERVICE_HPP
#define EXAMPLE_POSTGRESQL_USERSERVICE_HPP

#include "db/PhoneBookDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class PhoneBookService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<PhoneBookDb>, m_database); // Inject database component
public:

  oatpp::Object<PhoneBookDto> createPhoneBook(const oatpp::Object<PhoneBookDto>& dto);
  oatpp::Object<PhoneBookDto> updatePhoneBook(const oatpp::Object<PhoneBookDto>& dto);
  oatpp::Object<PhoneBookDto> getPhoneBookById(const oatpp::String& id);
  oatpp::Object<PageDto<oatpp::Object<PhoneBookDto>>> getAllPhoneBooks(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
  oatpp::Object<StatusDto> deletePhoneBookById(const oatpp::String& id);

};

#endif //EXAMPLE_POSTGRESQL_USERSERVICE_HPP
