#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"

#include "oatpp-swagger/Controller.hpp"

#include "controller/PhoneBookController.hpp"
#include "controller/SwaggerController.hpp"

void run() {

  oatpp::network::Server server(std::make_shared<oatpp::network::TcpConnectionProvider>("tcp://localhost:8000"));

  auto router = oatpp::web::server::HttpRouter::createShared();

  auto phoneBookController = PhoneBookController::createShared();
  phoneBookController->addEndpointsToRouter(router);

  auto swaggerController = SwaggerController::createShared();
  swaggerController->addEndpointsToRouter(router);

  OATPP_LOGI("Server", "Running on port %s...", server.getConnectionProvider()->getProperty("port").toString()->c_str());

  server.addRequestHandler(std::make_shared<oatpp::web::server::HttpConnectionHandler>(router));

  server.run();

}

int main() {
  oatpp::base::Environment::init();
  run();
  oatpp::base::Environment::destroy();
  return 0;
}
