cmake_minimum_required( VERSION 2.6 )

include(FindPkgConfig)
pkg_search_module( STAGE REQUIRED stage )

include_directories( ${STAGE_INCLUDE_DIRS} .. /usr/include/glib-2.0/ /usr/lib/glib-2.0/include )
link_directories( ${STAGE_LIBRARY_DIRS} )

SET( PLUGINS
     hoare-Project3-stage
     testStateSpace
)

# create a library module for each plugin and link libstage to each

foreach( PLUGIN ${PLUGINS} )
  ADD_LIBRARY( ${PLUGIN} MODULE ${PLUGIN}.cpp RobotCenterStage.cpp ../ActionSet.cpp ../StateSpace.cpp )
  TARGET_LINK_LIBRARIES( ${PLUGIN} ${STAGE_LIBRARIES} )
endforeach( PLUGIN )

# delete the "lib" prefix from the plugin libraries
SET_TARGET_PROPERTIES( ${PLUGINS} PROPERTIES PREFIX "" )

# install in <prefix>/lib
install( TARGETS ${PLUGINS} DESTINATION lib)

