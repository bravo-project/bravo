
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace bravo { namespace app {

class abstract_plugin;
class application;

} }

namespace bravo { namespace plugin {

void initialize_plugin_factories();
std::shared_ptr< bravo::app::abstract_plugin > create_plugin( const std::string& name, bravo::app::application* app );
std::vector< std::string > get_available_plugins();

} }
