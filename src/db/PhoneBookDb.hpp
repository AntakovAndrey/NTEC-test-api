
#ifndef PhoneBookDb_hpp
#define PhoneBookDb_hpp

#include "dto/PhoneBookDto.hpp"
#include "oatpp-postgresql/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * PhoneBookDb client definitions.
 */
class PhoneBookDb : public oatpp::orm::DbClient {
public:

  PhoneBookDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
    : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("PhoneBookDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(createPhoneBook,
        "INSERT INTO PhoneBook"
        "(id, phone, name, address) VALUES "
        "(uuid_generate_v4(), :phoneBook.phone, :phoneBook.name, :phoneBook.address)"
        "RETURNING *;",
        PREPARE(true), // user prepared statement!
        PARAM(oatpp::Object<PhoneBookDto>, phoneBook))

  QUERY(updatePhoneBook,
        "UPDATE PhoneBook "
        "SET "
        " phone=:phoneBook.phone, "
        " name=:phoneBook.name, "
        " address=:phoneBook.address"
        "WHERE "
        " id=:phoneBook.id "
        "RETURNING *;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::Object<PhoneBookDto>, phoneBook))

  QUERY(getPhoneBookById,
        "SELECT * FROM PhoneBook WHERE id=:id;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::String, id))

  QUERY(getAllPhoneBooks,
        "SELECT * FROM PhoneBook LIMIT :limit OFFSET :offset;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::UInt32, offset),
        PARAM(oatpp::UInt32, limit))

  QUERY(deletePhoneBookById,
        "DELETE FROM PhoneBook WHERE id=:id;",
        PREPARE(true), //<-- user prepared statement!
        PARAM(oatpp::String, id))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //EXAMPLE_POSTGRESQL_USERDB_HPP
