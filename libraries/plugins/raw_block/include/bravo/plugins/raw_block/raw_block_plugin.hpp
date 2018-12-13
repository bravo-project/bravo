
#pragma once

#include <bravo/app/plugin.hpp>

namespace bravo { namespace plugin { namespace raw_block {

using bravo::app::application;

class raw_block_plugin : public bravo::app::plugin
{
   public:
      raw_block_plugin( application* app );
      virtual ~raw_block_plugin();

      virtual std::string plugin_name()const override;
      virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;
};

} } }
