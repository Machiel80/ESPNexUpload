idf_component_register(SRCS ${srcs} "upload.c"
                        INCLUDE_DIRS ${include_dirs} "."
                        REQUIRES  cmd_nvs fatfs nvs_flash console 
                        ESPNexUpload )

set(target ${COMPONENT_LIB})
# ESPNexUploadWrapper ESPNexUpload
# Embed binaries into the app.
# In ESP-IDF this can also be done using EMBED_FILES option of idf_component_register.
# Here an external tool is used to make file embedding similar with other ports.
include(${CMAKE_CURRENT_LIST_DIR}/../firmware_tft/bin2array.cmake)
create_resources(${CMAKE_CURRENT_LIST_DIR}/../firmware_tft/bin ${CMAKE_BINARY_DIR}/binaries.c)
set_property(SOURCE ${CMAKE_BINARY_DIR}/binaries.c PROPERTY GENERATED 1)
target_sources(${target} PRIVATE ${CMAKE_BINARY_DIR}/binaries.c)
