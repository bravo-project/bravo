#include <bravo/witness/witness_operations.hpp>

#include <bravo/protocol/operation_util_impl.hpp>

namespace bravo { namespace witness {

void enable_content_editing_operation::validate()const
{
   chain::validate_account_name( account );
}

} } // bravo::witness

DEFINE_OPERATION_TYPE( bravo::witness::witness_plugin_operation )
