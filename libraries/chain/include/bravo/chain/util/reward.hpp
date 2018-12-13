#pragma once

#include <bravo/chain/util/asset.hpp>
#include <bravo/chain/bravo_objects.hpp>

#include <bravo/protocol/asset.hpp>
#include <bravo/protocol/config.hpp>
#include <bravo/protocol/types.hpp>

#include <fc/reflect/reflect.hpp>

#include <fc/uint128.hpp>

namespace bravo { namespace chain { namespace util {

using bravo::protocol::asset;
using bravo::protocol::price;
using bravo::protocol::share_type;

using fc::uint128_t;

struct comment_reward_context
{
   share_type rshares;
   uint16_t   reward_weight = 0;
   asset      max_bravo;
   uint128_t  total_reward_shares2;
   asset      total_reward_fund_bravo;
   curve_id   reward_curve = quadratic;
   uint128_t  content_constant = BRAVO_CONTENT_CONSTANT_HF0;
};

uint64_t get_rshare_reward( const comment_reward_context& ctx );

inline uint128_t get_content_constant_s()
{
   return BRAVO_CONTENT_CONSTANT_HF0; // looking good for posters
}

uint128_t evaluate_reward_curve( const uint128_t& rshares, const curve_id& curve = quadratic, const uint128_t& content_constant = BRAVO_CONTENT_CONSTANT_HF0 );

inline bool is_comment_payout_dust( const price& p, uint64_t bravo_payout )
{
   return asset(bravo_payout, BRAVO_SYMBOL) < BRAVO_MIN_PAYOUT;
}

} } } // bravo::chain::util

FC_REFLECT( bravo::chain::util::comment_reward_context,
   (rshares)
   (reward_weight)
   (max_bravo)
   (total_reward_shares2)
   (total_reward_fund_bravo)
   (reward_curve)
   (content_constant)
   )
