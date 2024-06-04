#include <iostream>
#include <oatpp/macro/component.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/network/tcp/ConnectionConfigurer.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/json/ObjectMapper.hpp>
//#include "controller/UserController.hpp"


//#include OATPP_CODEGEN_BEGIN(DTO)
//
//class StatusDto : public oatpp::DTO {
//
//    DTO_INIT(StatusDto, DTO)
//
//        DTO_FIELD_INFO(status) {
//        info->description = "Short status text";
//    }
//    DTO_FIELD(String, status);
//
//    DTO_FIELD_INFO(code) {
//        info->description = "Status code";
//    }
//    DTO_FIELD(Int32, code);
//
//    DTO_FIELD_INFO(message) {
//        info->description = "Verbose message";
//    }
//    DTO_FIELD(String, message);
//
//};
//
//#include OATPP_CODEGEN_END(DTO)
//
//class ErrorHandler : public oatpp::web::server::handler::ErrorHandler {
//private:
//    typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
//    typedef oatpp::web::protocol::http::Status Status;
//    typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;
//private:
//    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
//public:
//
//    ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) : m_objectMapper(objectMapper)
//    {}
//
//    std::shared_ptr<OutgoingResponse>
//        handleError(const Status& status, const oatpp::String& message, const Headers& headers) {
//        auto error = StatusDto::createShared();
//        error->status = "ERROR";
//        error->code = status.code;
//        error->message = message;
//
//        auto response = ResponseFactory::createResponse(status, error, m_objectMapper);
//
//        for (const auto& pair : headers.getAll()) {
//            response->putHeader(pair.first.toString(), pair.second.toString());
//        }
//
//        return response;
//    }
//
//};
//
//class AppComponent {
//public:
//
//
//    /**
//     * Database component
//     */
//    // DatabaseComponent databaseComponent;
//
//    /**
//     * Create ObjectMapper component to serialize/deserialize DTOs in Controller's API
//     */
//    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers)([] {
//
//        auto json = std::make_shared<oatpp::json::ObjectMapper>();
//        json->serializerConfig().json.useBeautifier = true;
//
//        auto mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
//        mappers->putMapper(json);
//
//        return mappers;
//
//        }());
//
//    /**
//     *  Create ConnectionProvider component which listens on the port
//     */
//    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
//        return oatpp::network::tcp::server::ConnectionProvider::createShared({ "0.0.0.0", 8000, oatpp::network::Address::IP_4 });
//        }());
//
//    /**
//     *  Create Router component
//     */
//    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
//        return oatpp::web::server::HttpRouter::createShared();
//        }());
//
//    /**
//     *  Create ConnectionHandler component which uses Router component to route requests
//     */
//    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
//
//        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
//        OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, contentMappers); // get ContentMappers component
//
//        auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
//        connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(
//            contentMappers->getMapper("application/json"))
//        );
//        return connectionHandler;
//
//        }());
//
//};

int main() {
    std::cout << "start" << std::endl;

    //AppComponent components; // 好多隐式关联依赖在一起，有点恶心。这个对象必须被之后创建的对象依赖。必须第一时间创建。

    oatpp::Environment::init();

    // C++ 还这么用宏，好恶心。
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    oatpp::web::server::api::Endpoints docEndpoints;
    //docEndpoints.append(router->addController(UserController::createShared())->getEndpoints());

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGd("Server", "Running on port {}...", connectionProvider->getProperty("port").toString());

    server.run();

    //OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    //dbConnectionProvider->stop();

    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";
    oatpp::Environment::destroy();

    return 0;
}
