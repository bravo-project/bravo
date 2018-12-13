#pragma once

#include <bravo/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace bravo{ namespace app {
   struct api_context;
} }

namespace bravo { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const bravo::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // bravo::account_statistics

FC_API( bravo::account_statistics::account_statistics_api, )