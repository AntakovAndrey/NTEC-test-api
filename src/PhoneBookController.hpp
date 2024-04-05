#pragma once

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "DTOs.hpp"
#include "DatabaseClient.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class PhoneBookController : public oatpp::web::server::api::ApiController {
public:
  PhoneBookController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper),
                      OATPP_COMPONENT(std::shared_ptr<DatabaseClient>, databaseClient))
    : oatpp::web::server::api::ApiController(objectMapper)
    , m_databaseClient(databaseClient)
  {}

  ENDPOINT("POST", "/phone-book", createEntry,
           BODY_DTO(PhoneBookEntry::ObjectWrapper, entry))
  {
    m_databaseClient->createEntry(entry);
    return createResponse(Status::CODE_200, "Entry created successfully");
  }

  ENDPOINT("PUT", "/phone-book/{id}", updateEntry,
           PATH(Int32, id),
           BODY_DTO(PhoneBookEntry::ObjectWrapper, entry))
  {
    entry->id = id;
    m_databaseClient->updateEntry(entry);
    return createResponse(Status::CODE_200, "Entry updated successfully");
  }

  ENDPOINT("DELETE", "/phone-book/{id}", deleteEntry,
           PATH(Int32, id))
  {
    m_databaseClient->deleteEntryById(id);
    return createResponse(Status::CODE_200, "Entry deleted successfully");
  }

  ENDPOINT("GET", "/phone-book/{id}", getEntryById,
           PATH(Int32, id))
  {
    auto entry = m_databaseClient->getEntryById(id);
    return createDtoResponse(Status::CODE_200, entry);
  }

  ENDPOINT("GET", "/phone-book", getAllEntries)
  {
    auto entries = m_databaseClient->getAllEntries();
    return createDtoResponse(Status::CODE_200, entries);
  }

private:
  std::shared_ptr<DatabaseClient> m_databaseClient;

};

#include OATPP_CODEGEN_END(ApiController) 
