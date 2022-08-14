idf_component_register(
    SRCS "src/ESPNexUpload.cpp"
	     "src/ESPNexUploadWrapper.cpp"
    INCLUDE_DIRS
        "src"
    REQUIRES driver
)