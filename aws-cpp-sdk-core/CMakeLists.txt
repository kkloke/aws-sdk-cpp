add_project(aws-cpp-sdk-core "Core http and utility library for the AWS C++ SDK")

if(VERSION_STRING)
    set(Version_VERSION_STRING ${VERSION_STRING})
    message(STATUS "Updating version info to ${VERSION_STRING}")
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/VersionConfig.h})
        FILE(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/VersionConfig.h})
    endif()

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/VersionConfig.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/VersionConfig.h")
else()
    message("Not able to compute versioning string, not updating.")
endif()

# If building shared libraries, custom memory management enabled is the default, otherwise regular memory management is the default.
# We make custom memory management the default on shared library builds because it is safer and much more difficult to accidentally
# allocate in one DLLs heap while freeing in another (which will lead to runtime crashes)
if(("${CUSTOM_MEMORY_MANAGEMENT}" STREQUAL "1") OR (BUILD_SHARED_LIBS AND NOT ("${CUSTOM_MEMORY_MANAGEMENT}" STREQUAL "0")))
    set(USE_AWS_MEMORY_MANAGEMENT ON)
    message(STATUS "Custom memory management enabled; stl objects now using custom allocators")
else()
    set(USE_AWS_MEMORY_MANAGEMENT OFF)
    message(STATUS "Custom memory management disabled")
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/SDKConfig.h.in" 
               "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/SDKConfig.h")

# Pretty sure we can use a regex here...
# Go ahead and glob every directory so we can work around Visual Studio's crap.
file(GLOB AWS_HEADERS "include/aws/core/*.h")
file(GLOB AWS_AUTH_HEADERS "include/aws/core/auth/*.h")
file(GLOB AWS_CLIENT_HEADERS "include/aws/core/client/*.h")
file(GLOB AWS_INTERNAL_HEADERS "include/aws/core/internal/*.h")
file(GLOB HTTP_HEADERS "include/aws/core/http/*.h")
file(GLOB HTTP_STANDARD_HEADERS "include/aws/core/http/standard/*.h")
file(GLOB CONFIG_HEADERS "include/aws/core/config/*.h")
file(GLOB PLATFORM_HEADERS "include/aws/core/platform/*.h")
file(GLOB UTILS_HEADERS "include/aws/core/utils/*.h")
file(GLOB UTILS_EVENT_HEADERS "include/aws/core/utils/event/*.h")
file(GLOB UTILS_BASE64_HEADERS "include/aws/core/utils/base64/*.h")
file(GLOB UTILS_CRYPTO_HEADERS "include/aws/core/utils/crypto/*.h")
file(GLOB UTILS_JSON_HEADERS "include/aws/core/utils/json/*.h")
file(GLOB UTILS_THREADING_HEADERS "include/aws/core/utils/threading/*.h")
file(GLOB UTILS_XML_HEADERS "include/aws/core/utils/xml/*.h")
file(GLOB UTILS_MEMORY_HEADERS "include/aws/core/utils/memory/*.h")
file(GLOB UTILS_STL_HEADERS "include/aws/core/utils/memory/stl/*.h")
file(GLOB UTILS_LOGGING_HEADERS "include/aws/core/utils/logging/*.h")
file(GLOB UTILS_RATE_LIMITER_HEADERS "include/aws/core/utils/ratelimiter/*.h")
file(GLOB UTILS_STREAM_HEADERS "include/aws/core/utils/stream/*.h")
file(GLOB JSONCPP_HEADERS "include/aws/core/external/json-cpp/*.h")
file(GLOB TINYXML2_HEADERS "include/aws/core/external/tinyxml2/tinyxml2.h")

file(GLOB AWS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
file(GLOB AWS_TINYXML2_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/external/tinyxml2/*.cpp")
file(GLOB AWS_JSONCPP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/external/json-cpp/*.cpp")
file(GLOB AWS_AUTH_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/auth/*.cpp")
file(GLOB AWS_CLIENT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/client/*.cpp")
file(GLOB AWS_INTERNAL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/internal/*.cpp")
file(GLOB AWS_MODEL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/aws/model/*.cpp")
file(GLOB HTTP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/http/*.cpp")
file(GLOB HTTP_STANDARD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/http/standard/*.cpp")
file(GLOB CONFIG_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/config/*.cpp")
file(GLOB UTILS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/*.cpp")
file(GLOB UTILS_EVENT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/event/*.cpp")
file(GLOB UTILS_BASE64_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/base64/*.cpp")
file(GLOB UTILS_CRYPTO_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/crypto/*.cpp")
file(GLOB UTILS_JSON_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/json/*.cpp")
file(GLOB UTILS_THREADING_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/threading/*.cpp")
file(GLOB UTILS_XML_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/xml/*.cpp")
file(GLOB UTILS_LOGGING_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/logging/*.cpp")
file(GLOB UTILS_MEMORY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/memory/*.cpp")
file(GLOB UTILS_MEMORY_STL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/memory/stl/*.cpp")
file(GLOB UTILS_STREAM_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/stream/*.cpp")
file(GLOB UTILS_CRYPTO_FACTORY_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/crypto/factory/*.cpp")

# http client implementations
if(ENABLE_CURL_CLIENT)
    file(GLOB HTTP_CURL_CLIENT_HEADERS "include/aws/core/http/curl/*.h")
    file(GLOB HTTP_CURL_CLIENT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/http/curl/*.cpp")
elseif(ENABLE_WINDOWS_CLIENT)
    if(USE_IXML_HTTP_REQUEST_2)
        file(GLOB HTTP_WINDOWS_CLIENT_HEADERS "include/aws/core/http/windows/IXmlHttpRequest2HttpClient.h")
        file(GLOB HTTP_WINDOWS_CLIENT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/http/windows/IXmlHttpRequest2HttpClient.cpp")
    else()
        file(GLOB HTTP_WINDOWS_CLIENT_HEADERS "include/aws/core/http/windows/Win*.h")
        file(GLOB HTTP_WINDOWS_CLIENT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/http/windows/Win*.cpp")
    endif()
endif()

# encryption implementations
if(ENABLE_BCRYPT_ENCRYPTION)
    file(GLOB UTILS_CRYPTO_BCRYPT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/utils/crypto/bcrypt/*.h")
    file(GLOB UTILS_CRYPTO_BCRYPT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/crypto/bcrypt/*.cpp")
elseif(ENABLE_OPENSSL_ENCRYPTION)
    file(GLOB UTILS_CRYPTO_OPENSSL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/utils/crypto/openssl/*.h")
    file(GLOB UTILS_CRYPTO_OPENSSL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/crypto/openssl/*.cpp")
elseif(ENABLE_COMMONCRYPTO_ENCRYPTION)
    file(GLOB UTILS_CRYPTO_COMMONCRYPTO_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/utils/crypto/commoncrypto/*.h")
    file(GLOB UTILS_CRYPTO_COMMONCRYPTO_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/utils/crypto/commoncrypto/*.cpp")
endif()   


file(GLOB AWS_NATIVE_SDK_COMMON_SRC
    ${AWS_SOURCE}
    ${AWS_TINYXML2_SOURCE}
    ${AWS_AUTH_SOURCE}
    ${AWS_CLIENT_SOURCE}
    ${AWS_INTERNAL_SOURCE}
    ${HTTP_STANDARD_SOURCE}
    ${HTTP_CLIENT_SOURCE}
    ${CONFIG_SOURCE}
    ${UTILS_EVENT_SOURCE}
    ${UTILS_BASE64_SOURCE}
    ${UTILS_CRYPTO_SOURCE}
    ${UTILS_JSON_SOURCE}
    ${UTILS_THREADING_SOURCE}
    ${UTILS_RETRY_SOURCE}
    ${UTILS_XML_SOURCE}
    ${UTILS_STREAM_SOURCE}
    ${UTILS_LOGGING_SOURCE}
    ${UTILS_MEMORY_SOURCE}
    ${UTILS_MEMORY_STL_SOURCE}
    ${UTILS_CRYPTO_OPENSSL_SOURCE}
    ${UTILS_CRYPTO_COMMONCRYPTO_SOURCE}
)

file(GLOB AWS_NATIVE_SDK_COMMON_HEADERS
  ${AWS_HEADERS}
  ${AWS_AUTH_HEADERS}
  ${AWS_CLIENT_HEADERS}
  ${AWS_INTERNAL_HEADERS}
  ${HTTP_HEADERS}
  ${HTTP_STANDARD_HEADERS}
  ${CONFIG_HEADERS}
  ${HTTP_CLIENT_HEADERS}
  ${PLATFORM_HEADERS}
  ${UTILS_HEADERS}
  ${UTILS_EVENT_HEADERS}
  ${UTILS_BASE64_HEADERS}
  ${UTILS_CRYPTO_HEADERS}
  ${UTILS_JSON_HEADERS}
  ${UTILS_THREADING_HEADERS}
  ${UTILS_RETRY_HEADERS}
  ${UTILS_XML_HEADERS}
  ${UTILS_LOGGING_HEADERS}
  ${UTILS_MEMORY_HEADERS}
  ${UTILS_STL_HEADERS}
  ${UTILS_STREAM_HEADERS}
  ${UTILS_RATE_LIMITER_HEADERS}
  ${JSONCPP_HEADERS}
  ${TINYXML2_HEADERS}
  ${HTTP_CURL_CLIENT_HEADERS}
  ${HTTP_WINDOWS_CLIENT_HEADERS}
  ${UTILS_CRYPTO_BCRYPT_HEADERS}
  ${UTILS_CRYPTO_OPENSSL_HEADERS}
  ${UTILS_CRYPTO_COMMONCRYPTO_HEADERS}
) 

# misc platform-specific, not related to features (encryption/http clients)
if(PLATFORM_WINDOWS)

  #add your windows specific impl stuff here.
  file(GLOB PLATFORM_WINDOWS_SOURCE = "${CMAKE_CURRENT_SOURCE_DIR}/source/platform/windows/*.cpp")

  file(GLOB AWS_NATIVE_SDK_WINDOWS_SRC 
    ${PLATFORM_WINDOWS_SOURCE}
  )
elseif(PLATFORM_LINUX OR PLATFORM_APPLE)

  #add unix specific impl stuff here.

  file(GLOB PLATFORM_LINUX_SHARED_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/platform/linux-shared/*.cpp")

  file(GLOB AWS_NATIVE_SDK_LINUX_SHARED_SRC 
     ${PLATFORM_LINUX_SHARED_SOURCE}
   )
elseif(PLATFORM_ANDROID)
  file(GLOB UTILS_LOGGING_ANDROID_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/utils/logging/android/*.h")
  file(GLOB PLATFORM_ANDROID_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source/platform/android/*.cpp")

  file(GLOB AWS_NATIVE_SDK_ANDROID_SRC 
     ${PLATFORM_ANDROID_SOURCE}
  )
  file(GLOB AWS_NATIVE_SDK_ANDROID_HEADERS
     ${UTILS_LOGGING_ANDROID_HEADERS}
  )
elseif(PLATFORM_CUSTOM)
  gather_custom_core_source(AWS_NATIVE_SDK_CUSTOM_SRC)
endif()

file(GLOB AWS_NATIVE_SDK_NON_UNITY_SRC
    ${HTTP_WINDOWS_CLIENT_SOURCE}
    ${HTTP_CURL_CLIENT_SOURCE}
    ${UTILS_CRYPTO_BCRYPT_SOURCE}
    ${AWS_NATIVE_SDK_WINDOWS_SRC}
    ${UTILS_CRYPTO_FACTORY_SOURCE}
    ${UTILS_SOURCE}
    ${HTTP_SOURCE}
    ${AWS_JSONCPP_SOURCE}
    ${AWS_NATIVE_SDK_CUSTOM_SRC}
)

file(GLOB AWS_NATIVE_SDK_UNITY_SRC
  ${AWS_NATIVE_SDK_COMMON_SRC}
  ${AWS_NATIVE_SDK_LINUX_SHARED_SRC}
  ${AWS_NATIVE_SDK_ANDROID_SRC}
)

if(ENABLE_UNITY_BUILD)
    enable_unity_build("core" AWS_NATIVE_SDK_UNITY_SRC)
endif()

file(GLOB AWS_NATIVE_SDK_UNIFIED_HEADERS
  ${AWS_NATIVE_SDK_COMMON_HEADERS}
  ${AWS_NATIVE_SDK_WINDOWS_HEADERS}
  ${AWS_NATIVE_SDK_UNIX_HEADERS}
  ${AWS_NATIVE_SDK_ANDROID_HEADERS}
)

file(GLOB AWS_NATIVE_SDK_SRC
    ${AWS_NATIVE_SDK_UNIFIED_HEADERS}
    ${AWS_NATIVE_SDK_UNITY_SRC}
    ${AWS_NATIVE_SDK_NON_UNITY_SRC}
)

# Visual studio project directory structure
if(MSVC)
    source_group("Header Files\\aws\\core" FILES ${AWS_HEADERS})
    source_group("Header Files\\aws\\core\\auth" FILES ${AWS_AUTH_HEADERS})
    source_group("Header Files\\aws\\core\\client" FILES ${AWS_CLIENT_HEADERS})
    source_group("Header Files\\aws\\core\\internal" FILES ${AWS_INTERNAL_HEADERS})
    source_group("Header Files\\aws\\core\\http" FILES ${HTTP_HEADERS})
    source_group("Header Files\\aws\\core\\http\\standard" FILES ${HTTP_STANDARD_HEADERS})
    source_group("Header Files\\aws\\core\\config" FILES ${CONFIG_HEADERS})
    source_group("Header Files\\aws\\core\\platform" FILES ${PLATFORM_HEADERS})
    source_group("Header Files\\aws\\core\\utils" FILES ${UTILS_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\base64" FILES ${UTILS_BASE64_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\crypto" FILES ${UTILS_CRYPTO_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\exceptions" FILES ${UTILS_EXCEPTIONS_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\json" FILES ${UTILS_JSON_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\threading" FILES ${UTILS_THREADING_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\xml" FILES ${UTILS_XML_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\logging" FILES ${UTILS_LOGGING_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\memory" FILES ${UTILS_MEMORY_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\memory\\stl" FILES ${UTILS_STL_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\stream" FILES ${UTILS_STREAM_HEADERS})
    source_group("Header Files\\aws\\core\\utils\\ratelimiter" FILES ${UTILS_RATE_LIMITER_HEADERS})
    source_group("Header Files\\aws\\core\\external\\json-cpp" FILES ${JSONCPP_HEADERS})
    source_group("Header Files\\aws\\core\\external\\tinyxml2" FILES ${TINYXML2_HEADERS})

    # http client conditional headers
    if(ENABLE_CURL_CLIENT)
        source_group("Header Files\\aws\\core\\http\\curl" FILES ${HTTP_CURL_CLIENT_HEADERS})
    elseif(ENABLE_WINDOWS_CLIENT)
        source_group("Header Files\\aws\\core\\http\\windows" FILES ${HTTP_WINDOWS_CLIENT_HEADERS})
    endif()

    # encryption conditional headers
    if(ENABLE_BCRYPT_ENCRYPTION)
        source_group("Header Files\\aws\\core\\utils\\crypto\\bcrypt" FILES ${UTILS_CRYPTO_BCRYPT_HEADERS})
    elseif(ENABLE_OPENSSL_ENCRYPTION)
        source_group("Header Files\\aws\\core\\utils\\crypto\\openssl" FILES ${UTILS_CRYPTO_OPENSSL_HEADERS})
    elseif(ENABLE_COMMONCRYPTO_ENCRYPTION)
        source_group("Header Files\\aws\\core\\utils\\crypto\\commoncrypto" FILES ${UTILS_CRYPTO_COMMONCRYPTO_HEADERS})
    endif()

    source_group("Source Files" FILES ${AWS_SOURCE})
    source_group("Source Files\\external\\json-cpp" FILES ${AWS_JSONCPP_SOURCE})
    source_group("Source Files\\external\\tinyxml2" FILES ${AWS_TINYXML2_SOURCE})
    source_group("Source Files\\auth" FILES ${AWS_AUTH_SOURCE})
    source_group("Source Files\\client" FILES ${AWS_CLIENT_SOURCE})
    source_group("Source Files\\internal" FILES ${AWS_INTERNAL_SOURCE})
    source_group("Source Files\\http" FILES ${HTTP_SOURCE})
    source_group("Source Files\\http\\standard" FILES ${HTTP_STANDARD_SOURCE})
    source_group("Source Files\\config" FILES ${CONFIG_SOURCE})
    source_group("Source Files\\platform\\windows" FILES ${PLATFORM_WINDOWS_SOURCE})
    source_group("Source Files\\utils" FILES ${UTILS_SOURCE})
    source_group("Source Files\\utils\\base64" FILES ${UTILS_BASE64_SOURCE})
    source_group("Source Files\\utils\\crypto" FILES ${UTILS_CRYPTO_SOURCE})
    source_group("Source Files\\utils\\crypto\\factory" FILES ${UTILS_CRYPTO_FACTORY_SOURCE})
    source_group("Source Files\\utils\\exceptions" FILES ${UTILS_EXCEPTIONS_SOURCE})
    source_group("Source Files\\utils\\json" FILES ${UTILS_JSON_SOURCE})
    source_group("Source Files\\utils\\threading" FILES ${UTILS_THREADING_SOURCE})
    source_group("Source Files\\utils\\xml" FILES ${UTILS_XML_SOURCE})
    source_group("Source Files\\utils\\stream" FILES ${UTILS_STREAM_SOURCE})
    source_group("Source Files\\utils\\logging" FILES ${UTILS_LOGGING_SOURCE})
    source_group("Source Files\\utils\\memory" FILES ${UTILS_MEMORY_SOURCE})
    source_group("Source Files\\utils\\memory\\stl" FILES ${UTILS_MEMORY_STL_SOURCE})

    # http client conditional source
    if(ENABLE_CURL_CLIENT)
        source_group("Source Files\\http\\curl" FILES ${HTTP_CURL_CLIENT_SOURCE})
    elseif(ENABLE_WINDOWS_CLIENT)
        source_group("Source Files\\http\\windows" FILES ${HTTP_WINDOWS_CLIENT_SOURCE})
    endif()

    # encryption conditional source
    if(ENABLE_BCRYPT_ENCRYPTION)
        source_group("Source Files\\utils\\crypto\\bcrypt" FILES ${UTILS_CRYPTO_BCRYPT_SOURCE})
    elseif(ENABLE_OPENSSL_ENCRYPTION)
        source_group("Source Files\\utils\\crypto\\openssl" FILES ${UTILS_CRYPTO_OPENSSL_SOURCE})
    elseif(ENABLE_COMMONCRYPTO_ENCRYPTION)
            source_group("Source Files\\utils\\crypto\\commoncrypto" FILES ${UTILS_CRYPTO_COMMONCRYPTO_SOURCE})
    endif()


endif(MSVC)

set(Core_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if(PLATFORM_CUSTOM)
  if(COMMAND add_custom_core_include_directories)
    add_custom_core_include_directories(CORE_CUSTOM_INCLUDE)
    SET(Core_INCLUDES ${Core_INCLUDES} ${CORE_CUSTOM_INCLUDE})
  endif()
  if(COMMAND add_custom_definitions)
    add_custom_definitions()
  endif()
endif()

include_directories(${Core_INCLUDES})

if(NOT PLATFORM_CUSTOM)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/aws/core/platform/refs)
endif()

if(USE_WINDOWS_DLL_SEMANTICS AND BUILD_SHARED_LIBS)
    add_definitions(-DAWS_CORE_EXPORTS=1)
endif()

if(BUILD_CURL)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CURL_INCLUDE_DIR}" )
endif()

if(BUILD_OPENSSL)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${OPENSSL_INCLUDE_DIR}" )
endif()

if(BUILD_ZLIB)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${ZLIB_INCLUDE_DIR}" )
endif()

add_library(${PROJECT_NAME} ${LIBTYPE} ${AWS_NATIVE_SDK_SRC})
add_library(AWS::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(PKG_CONFIG_LIB "-l${PROJECT_NAME}")

if(ENABLE_CURL_CLIENT AND BUILD_CURL)
    add_dependencies(${PROJECT_NAME} CURL)
endif()

if(ENABLE_OPENSSL_ENCRYPTION AND BUILD_OPENSSL)
    add_dependencies(${PROJECT_NAME} OPENSSL)
endif()

if(PLATFORM_CUSTOM)
  if(COMMAND add_custom_core_libraries)
    add_custom_core_libraries()
  endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} ${PLATFORM_DEP_LIBS} ${CLIENT_LIBS} ${CRYPTO_LIBS} ${AWS_SDK_ADDITIONAL_LIBRARIES})

if(USE_WINDOWS_DLL_SEMANTICS)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_WINDOWS_DLL_SEMANTICS)

    if(BUILD_SHARED_LIBS)
        target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_IMPORT_EXPORT=1)
    endif()
endif()

if(USE_GCC_FLAGS)
    target_compile_options(${PROJECT_NAME} PUBLIC -std=c++${CPP_STANDARD})

    if(NOT ENABLE_RTTI)
        target_compile_options(${PROJECT_NAME} PUBLIC -fno-rtti)
    endif()
else()

    if(NOT ENABLE_RTTI)
        target_compile_options(${PROJECT_NAME} PUBLIC /GR-)
    endif()
endif()

if(SIMPLE_INSTALL)
    install (
        TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}-targets"
        ARCHIVE DESTINATION ${ARCHIVE_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_DIRECTORY}
        RUNTIME DESTINATION ${BINARY_DIRECTORY}
    )
else()
    if(PLATFORM_CUSTOM)
        install_custom_library(${PROJECT_NAME})
    else()
        install (TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${ARCHIVE_DIRECTORY}/${SDK_INSTALL_BINARY_PREFIX}/${PLATFORM_INSTALL_QUALIFIER}/\${CMAKE_INSTALL_CONFIG_NAME}
                                         LIBRARY DESTINATION ${LIBRARY_DIRECTORY}/${SDK_INSTALL_BINARY_PREFIX}/${PLATFORM_INSTALL_QUALIFIER}/\${CMAKE_INSTALL_CONFIG_NAME}
                                         RUNTIME DESTINATION ${BINARY_DIRECTORY}/${SDK_INSTALL_BINARY_PREFIX}/${PLATFORM_INSTALL_QUALIFIER}/\${CMAKE_INSTALL_CONFIG_NAME})
    endif()
endif()

if(SIMPLE_INSTALL)
    configure_file("${CMAKE_SOURCE_DIR}/toolchains/pkg-config.pc.in" "${PROJECT_NAME}.pc" @ONLY)

    if(BUILD_SHARED_LIBS)
        install(
            FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
            DESTINATION ${LIBRARY_DIRECTORY}/pkgconfig)
    endif()
endif()

install (FILES ${AWS_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core)
install (FILES ${AWS_AUTH_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/auth)
install (FILES ${AWS_CLIENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/client)
install (FILES ${AWS_INTERNAL_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/internal)
install (FILES ${HTTP_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/http)
install (FILES ${HTTP_STANDARD_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/http/standard)
install (FILES ${PLATFORM_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/platform)
install (FILES ${UTILS_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils)
install (FILES ${UTILS_EVENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/event)
install (FILES ${UTILS_BASE64_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/base64)
install (FILES ${UTILS_CRYPTO_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/crypto)
install (FILES ${UTILS_JSON_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/json)
install (FILES ${UTILS_RETRY_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/retry)
install (FILES ${UTILS_XML_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/xml)
install (FILES ${UTILS_LOGGING_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/logging)
install (FILES ${UTILS_MEMORY_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/memory)
install (FILES ${UTILS_STL_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/memory/stl)
install (FILES ${UTILS_RATE_LIMITER_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/ratelimiter)
install (FILES ${UTILS_STREAM_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/stream)
install (FILES ${UTILS_THREADING_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/threading)
install (FILES ${JSONCPP_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/external/json-cpp)
install (FILES ${TINYXML2_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/external/tinyxml2)

# http client headers
if(ENABLE_CURL_CLIENT)
    install (FILES ${HTTP_CURL_CLIENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/http/curl)
elseif(ENABLE_WINDOWS_CLIENT)
    install (FILES ${HTTP_WINDOWS_CLIENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/http/windows)
endif()

# encryption headers
if(ENABLE_BCRYPT_ENCRYPTION)
  install (FILES ${UTILS_CRYPTO_BCRYPT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/crypto/bcrypt)
elseif(ENABLE_OPENSSL_ENCRYPTION)
  install (FILES ${UTILS_CRYPTO_OPENSSL_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/crypto/openssl)
elseif(ENABLE_COMMONCRYPTO_ENCRYPTION)
  install (FILES ${UTILS_CRYPTO_COMMONCRYPTO_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/aws/core/utils/crypto/commoncrypto)
endif()

do_packaging()

