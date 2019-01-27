#include <boost/test/unit_test.hpp>
#include <boost/program_options.hpp>

#include <graphene/utilities/tempdir.hpp>

#include <bravo/chain/bravo_objects.hpp>
#include <bravo/chain/history_object.hpp>
#include <bravo/account_history/account_history_plugin.hpp>
#include <bravo/witness/witness_plugin.hpp>

#include <fc/crypto/digest.hpp>
#include <fc/smart_ref_impl.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "database_fixture.hpp"

//using namespace bravo::chain::test;

uint32_t BRAVO_TESTING_GENESIS_TIMESTAMP = 1431700000;

namespace bravo { namespace chain {

using std::cout;
using std::cerr;

clean_database_fixture::clean_database_fixture()
{
   try {
   int argc = boost::unit_test::framework::master_test_suite().argc;
   char** argv = boost::unit_test::framework::master_test_suite().argv;
   for( int i=1; i<argc; i++ )
   {
      const std::string arg = argv[i];
      if( arg == "--record-assert-trip" )
         fc::enable_record_assert_trip = true;
      if( arg == "--show-test-names" )
         std::cout << "running test " << boost::unit_test::framework::current_test_case().p_name << std::endl;
   }
   auto ahplugin = app.register_plugin< bravo::account_history::account_history_plugin >();
   db_plugin = app.register_plugin< bravo::plugin::debug_node::debug_node_plugin >();
   auto wit_plugin = app.register_plugin< bravo::witness::witness_plugin >();
   init_account_pub_key = init_account_priv_key.get_public_key();

   boost::program_options::variables_map options;

   db_plugin->logging = false;
   ahplugin->plugin_initialize( options );
   db_plugin->plugin_initialize( options );
   wit_plugin->plugin_initialize( options );

   open_database();

   generate_block();
   db.set_hardfork( BRAVO_NUM_HARDFORKS );
   generate_block();

   //ahplugin->plugin_startup();
   db_plugin->plugin_startup();
   vest( "bravocoin", 10000 );

   // Fill up the rest of the required miners
   for( int i = BRAVO_NUM_INIT_MINERS; i < BRAVO_MAX_WITNESSES; i++ )
   {
      account_create( BRAVO_INIT_MINER_NAME + fc::to_string( i ), init_account_pub_key );
      fund( BRAVO_INIT_MINER_NAME + fc::to_string( i ), BRAVO_MIN_PRODUCER_REWARD.amount.value );
      witness_create( BRAVO_INIT_MINER_NAME + fc::to_string( i ), init_account_priv_key, "foo.bar", init_account_pub_key, BRAVO_MIN_PRODUCER_REWARD.amount );
   }

   validate_database();
   } catch ( const fc::exception& e )
   {
      edump( (e.to_detail_string()) );
      throw;
   }

   return;
}

clean_database_fixture::~clean_database_fixture()
{ try {
   // If we're unwinding due to an exception, don't do any more checks.
   // This way, boost test's last checkpoint tells us approximately where the error was.
   if( !std::uncaught_exception() )
   {
      BOOST_CHECK( db.get_node_properties().skip_flags == database::skip_nothing );
   }

   if( data_dir )
      db.close();
   return;
} FC_CAPTURE_AND_RETHROW() }

void clean_database_fixture::resize_shared_mem( uint64_t size )
{
   db.wipe( data_dir->path(), data_dir->path(), true );
   int argc = boost::unit_test::framework::master_test_suite().argc;
   char** argv = boost::unit_test::framework::master_test_suite().argv;
   for( int i=1; i<argc; i++ )
   {
      const std::string arg = argv[i];
      if( arg == "--record-assert-trip" )
         fc::enable_record_assert_trip = true;
      if( arg == "--show-test-names" )
         std::cout << "running test " << boost::unit_test::framework::current_test_case().p_name << std::endl;
   }
   init_account_pub_key = init_account_priv_key.get_public_key();

   db.open( data_dir->path(), data_dir->path(), INITIAL_TEST_SUPPLY, size, chainbase::database::read_write );

   boost::program_options::variables_map options;


   generate_block();
   db.set_hardfork( BRAVO_NUM_HARDFORKS );
   generate_block();

   vest( "bravocoin", 10000 );

   // Fill up the rest of the required miners
   for( int i = BRAVO_NUM_INIT_MINERS; i < BRAVO_MAX_WITNESSES; i++ )
   {
      account_create( BRAVO_INIT_MINER_NAME + fc::to_string( i ), init_account_pub_key );
      fund( BRAVO_INIT_MINER_NAME + fc::to_string( i ), BRAVO_MIN_PRODUCER_REWARD.amount.value );
      witness_create( BRAVO_INIT_MINER_NAME + fc::to_string( i ), init_account_priv_key, "foo.bar", init_account_pub_key, BRAVO_MIN_PRODUCER_REWARD.amount );
   }

   validate_database();
}

live_database_fixture::live_database_fixture()
{
   try
   {
      ilog( "Loading saved chain" );
      _chain_dir = fc::current_path() / "test_blockchain";
      FC_ASSERT( fc::exists( _chain_dir ), "Requires blockchain to test on in ./test_blockchain" );

      auto ahplugin = app.register_plugin< bravo::account_history::account_history_plugin >();
      ahplugin->plugin_initialize( boost::program_options::variables_map() );

      db.open( _chain_dir, _chain_dir );

      validate_database();
      generate_block();

      ilog( "Done loading saved chain" );
   }
   FC_LOG_AND_RETHROW()
}

live_database_fixture::~live_database_fixture()
{
   try
   {
      // If we're unwinding due to an exception, don't do any more checks.
      // This way, boost test's last checkpoint tells us approximately where the error was.
      if( !std::uncaught_exception() )
      {
         BOOST_CHECK( db.get_node_properties().skip_flags == database::skip_nothing );
      }

      db.pop_block();
      db.close();
      return;
   }
   FC_LOG_AND_RETHROW()
}

fc::ecc::private_key database_fixture::generate_private_key(string seed)
{
   static const fc::ecc::private_key committee = fc::ecc::private_key::regenerate( fc::sha256::hash( string( "init_key" ) ) );
   if( seed == "init_key" )
      return committee;
   return fc::ecc::private_key::regenerate( fc::sha256::hash( seed ) );
}

string database_fixture::generate_anon_acct_name()
{
   // names of the form "anon-acct-x123" ; the "x" is necessary
   //    to workaround issue #46
   return "anon-acct-x" + std::to_string( anon_acct_count++ );
}

void database_fixture::open_database()
{
   open_database(8 * 1024 * 1024);
}

void database_fixture::open_database(uint64_t file_size)
{
   if( !data_dir ) {
      data_dir = fc::temp_directory( graphene::utilities::temp_directory_path() );
      db._log_hardforks = false;
      db.open( data_dir->path(), data_dir->path(), INITIAL_TEST_SUPPLY, file_size, chainbase::database::read_write );
   }
}

void database_fixture::generate_block(uint32_t skip, const fc::ecc::private_key& key, int miss_blocks)
{
   skip |= default_skip;
   db_plugin->debug_generate_blocks( graphene::utilities::key_to_wif( key ), 1, skip, miss_blocks );
}

void database_fixture::generate_blocks( uint32_t block_count )
{
   auto produced = db_plugin->debug_generate_blocks( debug_key, block_count, default_skip, 0 );
   BOOST_REQUIRE( produced == block_count );
}

void database_fixture::generate_blocks(fc::time_point_sec timestamp, bool miss_intermediate_blocks)
{
   db_plugin->debug_generate_blocks_until( debug_key, timestamp, miss_intermediate_blocks, default_skip );
   BOOST_REQUIRE( ( db.head_block_time() - timestamp ).to_seconds() < BRAVO_BLOCK_INTERVAL );
}

const account_object& database_fixture::account_create(
   const string& name,
   const string& creator,
   const private_key_type& creator_key,
   const share_type& fee,
   const public_key_type& key,
   const public_key_type& post_key,
   const string& json_metadata
   )
{
   try
   {
      account_create_operation op;
      op.new_account_name = name;
      op.creator = creator;
      op.fee = asset( fee, BRAVO_SYMBOL );
      op.owner = authority( 1, key, 1 );
      op.active = authority( 1, key, 1 );
      op.posting = authority( 1, post_key, 1 );
      op.memo_key = key;
      op.json_metadata = json_metadata;

      trx.operations.push_back( op );      

      trx.set_expiration( db.head_block_time() + BRAVO_MAX_TIME_UNTIL_EXPIRATION );
      trx.sign( creator_key, db.get_chain_id() );
      trx.validate();
      db.push_transaction( trx, 0 );
      trx.operations.clear();
      trx.signatures.clear();

      const account_object& acct = db.get_account( name );

      return acct;
   }
   FC_CAPTURE_AND_RETHROW( (name)(creator) )
}

const account_object& database_fixture::account_create(
   const string& name,
   const public_key_type& key,
   const public_key_type& post_key
)
{
   try
   {
      return account_create(
         name,
         BRAVO_INIT_MINER_NAME,
         init_account_priv_key,
         std::max( db.get_witness_schedule_object().median_props.account_creation_fee.amount * BRAVO_CREATE_ACCOUNT_WITH_MODIFIER, share_type( 100 ) ),
         key,
         post_key,
         "" );
   }
   FC_CAPTURE_AND_RETHROW( (name) );
}

const account_object& database_fixture::account_create(
   const string& name,
   const public_key_type& key
)
{
   return account_create( name, key, key );
}

const witness_object& database_fixture::witness_create(
   const string& owner,
   const private_key_type& owner_key,
   const string& url,
   const public_key_type& signing_key,
   const share_type& fee )
{
   try
   {
      witness_update_operation op;
      op.owner = owner;
      op.url = url;
      op.block_signing_key = signing_key;
      op.fee = asset( fee, BRAVO_SYMBOL );

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + BRAVO_MAX_TIME_UNTIL_EXPIRATION );
      trx.sign( owner_key, db.get_chain_id() );
      trx.validate();
      db.push_transaction( trx, 0 );
      trx.operations.clear();
      trx.signatures.clear();

      return db.get_witness( owner );
   }
   FC_CAPTURE_AND_RETHROW( (owner)(url) )
}

void database_fixture::fund(
   const string& account_name,
   const share_type& amount
   )
{
   try
   {
      transfer( BRAVO_INIT_MINER_NAME, account_name, amount );

   } FC_CAPTURE_AND_RETHROW( (account_name)(amount) )
}

void database_fixture::fund(
   const string& account_name,
   const asset& amount
   )
{
   try
   {
      db_plugin->debug_update( [=]( database& db)
      {
         db.modify( db.get_account( account_name ), [&]( account_object& a )
         {
            if( amount.symbol == BRAVO_SYMBOL )
               a.balance += amount;
         });

         db.modify( db.get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
         {
            if( amount.symbol == BRAVO_SYMBOL )
               gpo.current_supply += amount;
         });

      }, default_skip );
   }
   FC_CAPTURE_AND_RETHROW( (account_name)(amount) )
}

void database_fixture::convert(
   const string& account_name,
   const asset& amount )
{
   FC_ASSERT(false, "convert assert is not supported any more");
}

void database_fixture::transfer(
   const string& from,
   const string& to,
   const share_type& amount )
{
   try
   {
      transfer_operation op;
      op.from = from;
      op.to = to;
      op.amount = amount;

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + BRAVO_MAX_TIME_UNTIL_EXPIRATION );
      trx.validate();
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (from)(to)(amount) )
}

void database_fixture::vest( const string& from, const share_type& amount )
{
   try
   {
      transfer_to_vesting_operation op;
      op.from = from;
      op.to = "";
      op.amount = asset( amount, BRAVO_SYMBOL );

      trx.operations.push_back( op );
      trx.set_expiration( db.head_block_time() + BRAVO_MAX_TIME_UNTIL_EXPIRATION );
      trx.validate();
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (from)(amount) )
}

void database_fixture::vest( const string& account, const asset& amount )
{
   if( amount.symbol != BRAVO_SYMBOL )
      return;

   db_plugin->debug_update( [=]( database& db )
   {
      db.modify( db.get_dynamic_global_properties(), [&]( dynamic_global_property_object& gpo )
      {
         gpo.current_supply += amount;
      });

      db.create_vesting( db.get_account( account ), amount );

   }, default_skip );
}

void database_fixture::proxy( const string& account, const string& proxy )
{
   try
   {
      account_witness_proxy_operation op;
      op.account = account;
      op.proxy = proxy;
      trx.operations.push_back( op );
      db.push_transaction( trx, ~0 );
      trx.operations.clear();
   } FC_CAPTURE_AND_RETHROW( (account)(proxy) )
}

void database_fixture::set_price_feed( const price& new_price )
{
   /*try
   {
      for ( int i = 1; i < 8; i++ )
      {
         feed_publish_operation op;
         op.publisher = BRAVO_INIT_MINER_NAME + fc::to_string( i );
         op.exchange_rate = new_price;
         trx.operations.push_back( op );
         trx.set_expiration( db.head_block_time() + BRAVO_MAX_TIME_UNTIL_EXPIRATION );
         db.push_transaction( trx, ~0 );
         trx.operations.clear();
      }
   } FC_CAPTURE_AND_RETHROW( (new_price) )*/

   generate_blocks( BRAVO_BLOCKS_PER_HOUR );
//   BOOST_REQUIRE(
//#ifdef IS_TEST_NET
//      !db.skip_price_feed_limit_check ||
//#endif
//      db.get(feed_history_id_type()).current_median_history == new_price
//   );
}

const asset& database_fixture::get_balance( const string& account_name )const
{
  return db.get_account( account_name ).balance;
}

void database_fixture::sign(signed_transaction& trx, const fc::ecc::private_key& key)
{
   trx.sign( key, db.get_chain_id() );
}

vector< operation > database_fixture::get_last_operations( uint32_t num_ops )
{
   vector< operation > ops;
   const auto& acc_hist_idx = db.get_index< account_history_index >().indices().get< by_id >();
   auto itr = acc_hist_idx.end();

   while( itr != acc_hist_idx.begin() && ops.size() < num_ops )
   {
      itr--;
      ops.push_back( fc::raw::unpack< bravo::chain::operation >( db.get(itr->op).serialized_op ) );
   }

   return ops;
}

void database_fixture::validate_database( void )
{
   try
   {
      db.validate_invariants();
   }
   FC_LOG_AND_RETHROW();
}

namespace test {

bool _push_block( database& db, const signed_block& b, uint32_t skip_flags /* = 0 */ )
{
   return db.push_block( b, skip_flags);
}

void _push_transaction( database& db, const signed_transaction& tx, uint32_t skip_flags /* = 0 */ )
{ try {
   db.push_transaction( tx, skip_flags );
} FC_CAPTURE_AND_RETHROW((tx)) }

} // bravo::chain::test

} } // bravo::chain
