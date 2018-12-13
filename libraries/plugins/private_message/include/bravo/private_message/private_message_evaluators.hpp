#pragma once

#include <bravo/chain/evaluator.hpp>

#include <bravo/private_message/private_message_operations.hpp>
#include <bravo/private_message/private_message_plugin.hpp>

namespace bravo { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, bravo::private_message::private_message_plugin_operation, private_message )

} }
