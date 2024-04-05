#include "oatpp-postgresql/orm.hpp"

class DatabaseClient {
private:
  static constexpr const char* DB_URL = "postgresql://username:password@localhost:5432/database_name";

  oatpp::postgresql::ConnectionProvider::Config m_config;
  oatpp::postgresql::ConnectionProvider m_connectionProvider;
  oatpp::postgresql::Executor m_executor;

public:
  DatabaseClient()
    : m_config(DB_URL)
    , m_connectionProvider(m_config)
    , m_executor(m_connectionProvider)
  {}

  void createEntry(const PhoneBookEntry::ObjectWrapper& entry) {
    oatpp::postgresql::Connection connection = m_connectionProvider.getConnection();
    oatpp::postgresql::Executor executor(connection);
    executor.executeNonQuery("INSERT INTO phone_book (phone, name, address) VALUES ($1, $2, $3)",
                              {entry->phone, entry->name, entry->address});
  }

  void updateEntry(const PhoneBookEntry::ObjectWrapper& entry) {
    oatpp::postgresql::Connection connection = m_connectionProvider.getConnection();
    oatpp::postgresql::Executor executor(connection);
    executor.executeNonQuery("UPDATE phone_book SET phone=$2, name=$3, address=$4 WHERE id=$1",
                              {entry->id, entry->phone, entry->name, entry->address});
  }

  void deleteEntryById(int id) {
    oatpp::postgresql::Connection connection = m_connectionProvider.getConnection();
    oatpp::postgresql::Executor executor(connection);
    executor.executeNonQuery("DELETE FROM phone_book WHERE id=$1", {id});
  }

  PhoneBookEntry::ObjectWrapper getEntryById(int id) {
    oatpp::postgresql::Connection connection = m_connectionProvider.getConnection();
    oatpp::postgresql::Executor executor(connection);
    auto result = executor.execute("SELECT * FROM phone_book WHERE id=$1", {id});
    auto dto = PhoneBookEntry::createShared();
    if (!result->empty()) {
      auto row = result->fetchNext();
      dto->id = row["id"].getValue<int>();
      dto->phone = row["phone"].getValue<std::string>();
      dto->name = row["name"].getValue<std::string>();
      dto->address = row["address"].getValue<std::string>();
    }
    return dto;
  }

  oatpp::List<PhoneBookEntry::ObjectWrapper>::ObjectWrapper getAllEntries() {
    oatpp::postgresql::Connection connection = m_connectionProvider.getConnection();
    oatpp::postgresql::Executor executor(connection);
    auto result = executor.execute("SELECT * FROM phone_book");
    auto list = oatpp::List<PhoneBookEntry::ObjectWrapper>::createShared();
    while (!result->empty()) {
      auto row = result->fetchNext();
      auto dto = PhoneBookEntry::createShared();
      dto->id = row["id"].getValue<int>();
      dto->phone = row["phone"].getValue<std::string>();
      dto->name = row["name"].getValue<std::string>();
      dto->address = row["address"].getValue<std::string>();
      list->push_back(dto);
    }
    return list;
  }
};
