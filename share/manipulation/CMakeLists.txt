# Copyright: 2014 UC3M
# Author: Juan G Victores
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

set(appname manipulation)


file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/*.ini)

yarp_install(FILES ${conf} DESTINATION ${TEO-BODY_CONTEXTS_INSTALL_DIR}/${appname})

