#include <bravo/follow/follow_operations.hpp>

#include <bravo/protocol/operation_util_impl.hpp>

namespace bravo { namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } //bravo::follow

DEFINE_OPERATION_TYPE( bravo::follow::follow_plugin_operation )
