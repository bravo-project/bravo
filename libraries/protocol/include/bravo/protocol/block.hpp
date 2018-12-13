#pragma once
#include <bravo/protocol/block_header.hpp>
#include <bravo/protocol/transaction.hpp>

namespace bravo { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // bravo::protocol

FC_REFLECT_DERIVED( bravo::protocol::signed_block, (bravo::protocol::signed_block_header), (transactions) )
