#ifndef OATPP_DEMO_CONTROLLER_USER_CONTROLLER_H
#define OATPP_DEMO_CONTROLLER_USER_CONTROLLER_H

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/macro/codegen.hpp"

#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
    VALUE(GUEST, 0, "ROLE_GUEST"),
    VALUE(ADMIN, 1, "ROLE_ADMIN")
)

class UserDto : public oatpp::DTO {

    DTO_INIT(UserDto, DTO)

        DTO_FIELD(Int32, id);
    DTO_FIELD(String, userName, "username");
    DTO_FIELD(String, email, "email");
    DTO_FIELD(String, password, "password");
    DTO_FIELD(Enum<Role>::AsString, role, "role");

};

#include OATPP_CODEGEN_END(DTO)


class UserService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:

    oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto) {

        auto dbResult = m_database->createUser(dto);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto userId = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

        return getUserById((v_int32)userId);

    }
    oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto>& dto) {

        auto dbResult = m_database->updateUser(dto);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
        return getUserById(dto->id);

    }
    oatpp::Object<UserDto> getUserById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr) {

        auto dbResult = m_database->getUserById(id, connection);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
        OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

        auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
        OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

        return result[0];

    }
    oatpp::Object<PageDto<oatpp::Object<UserDto>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

        oatpp::UInt32 countToFetch = limit;

        if (limit > 10) {
            countToFetch = 10;
        }

        auto dbResult = m_database->getAllUsers(offset, countToFetch);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

        auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();

        auto page = PageDto<oatpp::Object<UserDto>>::createShared();
        page->offset = offset;
        page->limit = countToFetch;
        page->count = items->size();
        page->items = items;

        return page;

    }
    oatpp::Object<StatusDto> deleteUserById(const oatpp::Int32& id) {
        auto dbResult = m_database->deleteUserById(userId);
        OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
        auto status = StatusDto::createShared();
        status->status = "OK";
        status->code = 200;
        status->message = "User was successfully deleted";
        return status;
    }

};


#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class UserController : public oatpp::web::server::api::ApiController {
public:
    UserController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
        : oatpp::web::server::api::ApiController(apiContentMappers)
    {}
private:
    UserService m_userService; // Create user service.
public:

    static std::shared_ptr<UserController> createShared(
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
    ) {
        return std::make_shared<UserController>(apiContentMappers);
    }

    ENDPOINT_INFO(createUser) {
        info->summary = "Create new User";

        info->addConsumes<Object<UserDto>>("application/json");

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "users", createUser,
        BODY_DTO(Object<UserDto>, userDto))
    {
        return createDtoResponse(Status::CODE_200, m_userService.createUser(userDto));
    }


    ENDPOINT_INFO(putUser) {
        info->summary = "Update User by userId";

        info->addConsumes<Object<UserDto>>("application/json");

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("PUT", "users/{userId}", putUser,
        PATH(Int32, userId),
        BODY_DTO(Object<UserDto>, userDto))
    {
        userDto->id = userId;
        return createDtoResponse(Status::CODE_200, m_userService.updateUser(userDto));
    }


    ENDPOINT_INFO(getUserById) {
        info->summary = "Get one User by userId";

        info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("GET", "users/{userId}", getUserById,
        PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getUserById(userId));
    }


    ENDPOINT_INFO(getUsers) {
        info->summary = "get all stored users";

        info->addResponse<oatpp::Object<UsersPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "users/offset/{offset}/limit/{limit}", getUsers,
        PATH(UInt32, offset),
        PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_userService.getAllUsers(offset, limit));
    }


    ENDPOINT_INFO(deleteUser) {
        info->summary = "Delete User by userId";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["userId"].description = "User Identifier";
    }
    ENDPOINT("DELETE", "users/{userId}", deleteUser,
        PATH(Int32, userId))
    {
        return createDtoResponse(Status::CODE_200, m_userService.deleteUserById(userId));
    }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif
