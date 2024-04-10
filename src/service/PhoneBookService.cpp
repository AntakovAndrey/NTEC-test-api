#include "PhoneBookService.hpp"

oatpp::Object<PhoneBookDto> PhoneBookService::createPhoneBook(const oatpp::Object<PhoneBookDto>& dto) {

  auto dbResult = m_database->createPhoneBook(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneBookDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];

}

oatpp::Object<PhoneBookDto> PhoneBookService::updatePhoneBook(const oatpp::Object<PhoneBookDto>& dto) {

  auto dbResult = m_database->updatePhoneBook(dto);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneBookDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
  return result[0];

}

oatpp::Object<PhoneBookDto> PhoneBookService::getPhoneBookById(const oatpp::String& id) {

  auto dbResult = m_database->getPhoneBookById(id);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "PhoneBook not found");

  auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneBookDto>>>();
  OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

  return result[0];

}

oatpp::Object<PageDto<oatpp::Object<PhoneBookDto>>> PhoneBookService::getAllPhoneBooks(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

  oatpp::UInt32 countToFetch = limit;

  if(limit > 10) {
    countToFetch = 10;
  }

  auto dbResult = m_database->getAllPhoneBooks(offset, countToFetch);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<PhoneBookDto>>>();

  auto page = PageDto<oatpp::Object<PhoneBookDto>>::createShared();
  page->offset = offset;
  page->limit = countToFetch;
  page->count = items->size();
  page->items = items;

  return page;

}

oatpp::Object<StatusDto> PhoneBookService::deletePhoneBookById(const oatpp::String& phoneBookId) {
  auto dbResult = m_database->deletePhoneBookById(phoneBookId);
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
  auto status = StatusDto::createShared();
  status->status = "OK";
  status->code = 200;
  status->message = "PhoneBook was successfully deleted";
  return status;
}