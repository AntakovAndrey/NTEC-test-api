
#ifndef PhoneBookController_hpp
#define PhoneBookController_hpp

#include "service/PhoneBookService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen


class PhoneBookController : public oatpp::web::server::api::ApiController {
public:
  PhoneBookController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  PhoneBookService m_phoneBookService; // Create PhoneBook service.
public:

  static std::shared_ptr<PhoneBookController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<PhoneBookController>(objectMapper);
  }
  
  ENDPOINT_INFO(createPhoneBook) {
    info->summary = "Create new PhoneBook";

    info->addConsumes<Object<PhoneBookDto>>("application/json");

    info->addResponse<Object<PhoneBookDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<PhoneBookDto>>(Status::CODE_500, "application/json");
    info->addResponse<Object<PhoneBookDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("POST", "phoneBooks", createPhoneBook,
           BODY_DTO(Object<PhoneBookDto>, phoneBookDto))
  {
    return createDtoResponse(Status::CODE_200, m_phoneBookService.createPhoneBook(phoneBookDto));
  }
  
  
  ENDPOINT_INFO(putPhoneBook) {
    info->summary = "Update PhoneBook by phoneBookId";

    info->addConsumes<Object<PhoneBookDto>>("application/json");

    info->addResponse<Object<PhoneBookDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["phoneBookId"].description = "PhoneBook Identifier";
  }
  ENDPOINT("PUT", "phoneBooks/{phoneBookId}", putPhoneBook,
           PATH(String, phoneBookId),
           BODY_DTO(Object<PhoneBookDto>, phoneBookDto))
  {
      phoneBookDto->id = phoneBookId;
    return createDtoResponse(Status::CODE_200, m_phoneBookService.updatePhoneBook(phoneBookDto));
  }
  
  
  ENDPOINT_INFO(getPhoneBookById) {
    info->summary = "Get one PhoneBook by phoneBookId";

    info->addResponse<Object<PhoneBookDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["phoneBookId"].description = "PhoneBook Identifier";
  }
  ENDPOINT("GET", "phoneBooks/{phoneBookId}", getPhoneBookById,
           PATH(String, phoneBookId))
  {
    return createDtoResponse(Status::CODE_200, m_phoneBookService.getPhoneBookById(phoneBookId));
  }
  
  
  ENDPOINT_INFO(getPhoneBooks) {
    info->summary = "get all stored phoneBooks";

    info->addResponse<oatpp::Object<PhoneBooksPageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ENDPOINT("GET", "phoneBook/offset/{offset}/limit/{limit}", getPhoneBooks,
           PATH(UInt32, offset),
           PATH(UInt32, limit))
  {
    return createDtoResponse(Status::CODE_200, m_phoneBookService.getAllPhoneBooks(offset, limit));
  }
  
  
  ENDPOINT_INFO(deletePhoneBook) {
    info->summary = "Delete PhoneBook by phoneBookId";

    info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

    info->pathParams["phoneBookId"].description = "PhoneBook Identifier";
  }
  ENDPOINT("DELETE", "phoneBook/{phoeBookId}", deletePhoneBook,
           PATH(String, phoneBookId))
  {
    return createDtoResponse(Status::CODE_200, m_phoneBookService.deletePhoneBookById(phoneBookId));
  }

};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif