/* Copyright (c) 2018 BravoCoin.com */
/*
 * Copyright (c) 2016 Steemit, Inc., and contributors.
 */
#pragma once

#define BRAVO_BLOCKCHAIN_VERSION              ( version(0, 23, 0) )
#define BRAVO_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( BRAVO_BLOCKCHAIN_VERSION ) )

#ifdef IS_TEST_NET
#define BRAVO_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define BRAVO_INIT_PUBLIC_KEY_STR             (std::string( bravo::protocol::public_key_type(BRAVO_INIT_PRIVATE_KEY.get_public_key()) ))
#define BRAVO_CHAIN_ID                        (fc::sha256::hash("testnet"))

#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define BRAVO_SYMBOL  (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< BRAVO with 3 digits of precision

#define BRAVO_SYMBOL_TXT                      "TEST"
#define BRAVO_ADDRESS_PREFIX                  "TST"

#define BRAVO_GENESIS_TIME                    (fc::time_point_sec(1451606400))
#define BRAVO_MINING_TIME                     (fc::time_point_sec(1451606400))
#define BRAVO_CASHOUT_WINDOW_SECONDS          (60*60) /// 1 hr
#define BRAVO_CASHOUT_WINDOW_SECONDS_PRE_HF12 (BRAVO_CASHOUT_WINDOW_SECONDS)
#define BRAVO_CASHOUT_WINDOW_SECONDS_PRE_HF17 (BRAVO_CASHOUT_WINDOW_SECONDS)
#define BRAVO_SECOND_CASHOUT_WINDOW           (60*60*24*3) /// 3 days
#define BRAVO_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24) /// 1 day
#define BRAVO_VOTE_CHANGE_LOCKOUT_PERIOD      (60*10) /// 10 minutes
#define BRAVO_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define BRAVO_UPVOTE_LOCKOUT_HF17             (fc::minutes(5))
#define BRAVO_MAX_CASHOUT_WINDOWS               (3)  // cashout will be done for 3 times for testnet

#define BRAVO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE 0
#define BRAVO_MIN_ACCOUNT_CREATION_FEE          0

#define BRAVO_OWNER_AUTH_RECOVERY_PERIOD                  fc::seconds(120)
#define BRAVO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::seconds(50)
#define BRAVO_OWNER_UPDATE_LIMIT                          fc::seconds(0)
#define BRAVO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1
#else // IS LIVE BRAVO NETWORK

#ifdef FEWER_WITNESSES

#define BRAVO_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define BRAVO_INIT_PUBLIC_KEY_STR             (std::string( bravo::protocol::public_key_type(BRAVO_INIT_PRIVATE_KEY.get_public_key()) ))

#else

#define BRAVO_INIT_PUBLIC_KEY_STR             "BRV7o17Mp78B3WE3Sa1h8CK9mVNLBBN4mHuLAecUXxsb4tKCBnrHQ"

#endif // FEWER_WITNESSES

#define BRAVO_CHAIN_ID                        (bravo::protocol::chain_id_type())
#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define BRAVO_SYMBOL  (uint64_t(3) | (uint64_t('B') << 8) | (uint64_t('R') << 16) | (uint64_t('A') << 24) | (uint64_t('V') << 32) | (uint64_t('O') << 40)) ///< BRAVO with 3 digits of precision
#define BRAVO_SYMBOL_TXT                      "BRAVO"
#define BRAVO_ADDRESS_PREFIX                  "BRV"

#define BRAVO_GENESIS_TIME                    (fc::time_point_sec(1540282170))
#define BRAVO_MINING_TIME                     (fc::time_point_sec(1540282170))
#define BRAVO_CASHOUT_WINDOW_SECONDS_PRE_HF12 (60*60*24)    /// 1 day
#define BRAVO_CASHOUT_WINDOW_SECONDS_PRE_HF17 (60*60*12)    /// 12 hours
#define BRAVO_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
#define BRAVO_SECOND_CASHOUT_WINDOW           (60*60*24*30) /// 30 days
#define BRAVO_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24*14) /// 2 weeks
#define BRAVO_VOTE_CHANGE_LOCKOUT_PERIOD      (60*60*2)     /// 2 hours
#define BRAVO_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define BRAVO_UPVOTE_LOCKOUT_HF17             (fc::minutes(30))
#define BRAVO_MAX_CASHOUT_WINDOWS               (12)  // cashout will be done for 12 times

#define BRAVO_ORIGINAL_MIN_ACCOUNT_CREATION_FEE  100000
#define BRAVO_MIN_ACCOUNT_CREATION_FEE           1

#define BRAVO_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
#define BRAVO_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
#define BRAVO_OWNER_UPDATE_LIMIT                          fc::minutes(60)
#define BRAVO_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 3186477

#endif

#ifdef FEWER_WITNESSES

#define BRAVO_MAX_WITNESSES                   3

#define BRAVO_MAX_VOTED_WITNESSES_HF0         1
#define BRAVO_MAX_MINER_WITNESSES_HF0         1
#define BRAVO_MAX_RUNNER_WITNESSES_HF0        1

#define BRAVO_MAX_VOTED_WITNESSES_HF17        3
#define BRAVO_MAX_MINER_WITNESSES_HF17        0
#define BRAVO_MAX_RUNNER_WITNESSES_HF17       0

#define BRAVO_HARDFORK_REQUIRED_WITNESSES     2

// These values have been lowered to make testing easier
#define BRAVO_500_USERS                       7
#define BRAVO_5K_USERS                        10
#define BRAVO_50K_USERS                       15

#else // the usual witness requirements

#define BRAVO_MAX_WITNESSES                   21

#define BRAVO_MAX_VOTED_WITNESSES_HF0         19
#define BRAVO_MAX_MINER_WITNESSES_HF0         1
#define BRAVO_MAX_RUNNER_WITNESSES_HF0        1

#define BRAVO_MAX_VOTED_WITNESSES_HF17        20
#define BRAVO_MAX_MINER_WITNESSES_HF17        0
#define BRAVO_MAX_RUNNER_WITNESSES_HF17       1

#define BRAVO_HARDFORK_REQUIRED_WITNESSES     17 // 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.

#define BRAVO_500_USERS                       500
#define BRAVO_5K_USERS                        5000
#define BRAVO_50K_USERS                       50000

#endif  // FEWER_WITNESSES

 //Bravo config
#define BRAVO_INIT_MINED_COIN_PER_BLOCK         25
#define BRAVO_MINED_COIN_HALVED_TIME            (1)	// 1 YEAR
#define BRAVO_MINED_COIN_HALVED_BLOCK           (BRAVO_BLOCKS_PER_YEAR*BRAVO_MINED_COIN_HALVED_TIME)

#define BRAVO_REWARD_MULTIPLIER_AT_500          10
#define BRAVO_REWARD_MULTIPLIER_AT_5K           100
#define BRAVO_REWARD_MULTIPLIER_AT_50K          1000

#define BRAVO_BLOCK_INTERVAL                  30
#define BRAVO_BLOCKS_PER_YEAR                 (365*24*60*60/BRAVO_BLOCK_INTERVAL)
#define BRAVO_BLOCKS_PER_DAY                  (24*60*60/BRAVO_BLOCK_INTERVAL)
#define BRAVO_START_VESTING_BLOCK             (BRAVO_BLOCKS_PER_DAY * 7)
#define BRAVO_START_MINER_VOTING_BLOCK        (BRAVO_BLOCKS_PER_DAY * 30)

#define BRAVO_INIT_MINER_NAME                 "bravocoin"
#define BRAVO_NUM_INIT_MINERS                 1
#define BRAVO_INIT_TIME                       (fc::time_point_sec());

#define BRAVO_MAX_TIME_UNTIL_EXPIRATION       (60*60) // seconds,  aka: 1 hour
#define BRAVO_MAX_MEMO_SIZE                   2048
#define BRAVO_MAX_PROXY_RECURSION_DEPTH       4
#define BRAVO_VESTING_WITHDRAW_INTERVALS_PRE_HF_16 104
#define BRAVO_VESTING_WITHDRAW_INTERVALS      13
#define BRAVO_VESTING_WITHDRAW_INTERVAL_SECONDS (60*60*24*7) /// 1 week per interval
#define BRAVO_MAX_WITHDRAW_ROUTES             10
#define BRAVO_SAVINGS_WITHDRAW_TIME        	(fc::days(3))
#define BRAVO_SAVINGS_WITHDRAW_REQUEST_LIMIT  100
#define BRAVO_VOTE_REGENERATION_SECONDS       (5*60*60*24) // 5 day
#define BRAVO_MAX_VOTE_CHANGES                5
#define BRAVO_REVERSE_AUCTION_WINDOW_SECONDS  (60*30) /// 30 minutes
#define BRAVO_MIN_VOTE_INTERVAL_SEC           3
#define BRAVO_VOTE_DUST_THRESHOLD             (50000000)

#define BRAVO_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(60*5)) // 5 minutes
#define BRAVO_MIN_REPLY_INTERVAL              (fc::seconds(20)) // 20 seconds
#define BRAVO_POST_AVERAGE_WINDOW             (60*60*24u) // 1 day
#define BRAVO_POST_MAX_BANDWIDTH              (4*BRAVO_100_PERCENT) // 2 posts per 1 days, average 1 every 12 hours
#define BRAVO_POST_WEIGHT_CONSTANT            (uint64_t(BRAVO_POST_MAX_BANDWIDTH) * BRAVO_POST_MAX_BANDWIDTH)

#define BRAVO_MAX_ACCOUNT_WITNESS_VOTES       30

#define BRAVO_100_PERCENT                     10000
#define BRAVO_1_PERCENT                       (BRAVO_100_PERCENT/100)
#define BRAVO_1_TENTH_PERCENT                 (BRAVO_100_PERCENT/1000)

#define BRAVO_CONTENT_REWARD_PERCENT          (75*BRAVO_1_PERCENT)
#define BRAVO_CONTENT_REWARD_PERCENT_HF23     (90*BRAVO_1_PERCENT)
#define BRAVO_CUSTOME_OP_FEE                  1

#define BRAVO_NEW_ACCOUNT_CREATION_SHARE        (80*BRAVO_1_PERCENT) //80% of account creation fee will be added to new account reward balance

#define BRAVO_BANDWIDTH_AVERAGE_WINDOW_SECONDS (60*60*24*7) ///< 1 week
#define BRAVO_BANDWIDTH_PRECISION             (uint64_t(1000000)) ///< 1 million
#define BRAVO_MAX_COMMENT_DEPTH               0xffff // 64k
#define BRAVO_SOFT_MAX_COMMENT_DEPTH          0xff // 255

#define BRAVO_MAX_RESERVE_RATIO               (20000)

#define BRAVO_CREATE_ACCOUNT_WITH_MODIFIER 30

#define BRAVO_MINING_REWARD                   asset( 1000, BRAVO_SYMBOL )
#define BRAVO_EQUIHASH_N                      140
#define BRAVO_EQUIHASH_K                      6

#define BRAVO_LIQUIDITY_TIMEOUT_SEC           (fc::seconds(60*60*24*7)) // After one week volume is set to 0
#define BRAVO_MIN_LIQUIDITY_REWARD_PERIOD_SEC (fc::seconds(60)) // 1 minute required on books to receive volume
#define BRAVO_LIQUIDITY_REWARD_PERIOD_SEC     (60*60)
#define BRAVO_LIQUIDITY_REWARD_BLOCKS         (BRAVO_LIQUIDITY_REWARD_PERIOD_SEC/BRAVO_BLOCK_INTERVAL)
#define BRAVO_MIN_LIQUIDITY_REWARD            (asset( 1000*BRAVO_LIQUIDITY_REWARD_BLOCKS, BRAVO_SYMBOL )) // Minumum reward to be paid out to liquidity providers
#define BRAVO_MIN_CONTENT_REWARD              BRAVO_MINING_REWARD
#define BRAVO_MIN_CURATE_REWARD               BRAVO_MINING_REWARD
#define BRAVO_MIN_PRODUCER_REWARD             BRAVO_MINING_REWARD
#define BRAVO_MIN_POW_REWARD                  BRAVO_MINING_REWARD

#define BRAVO_ACTIVE_CHALLENGE_FEE            asset( 2000, BRAVO_SYMBOL )
#define BRAVO_OWNER_CHALLENGE_FEE             asset( 30000, BRAVO_SYMBOL )
#define BRAVO_ACTIVE_CHALLENGE_COOLDOWN       fc::days(1)
#define BRAVO_OWNER_CHALLENGE_COOLDOWN        fc::days(1)

#define BRAVO_POST_REWARD_FUND_NAME           ("post")
#define BRAVO_COMMENT_REWARD_FUND_NAME        ("comment")
#define BRAVO_RECENT_RSHARES_DECAY_RATE_HF17  (fc::days(30))
#define BRAVO_RECENT_RSHARES_DECAY_RATE_HF19  (fc::days(15))
#define BRAVO_CONTENT_CONSTANT_HF0            (uint128_t(uint64_t(2000000000000ll)))
// note, if redefining these constants make sure calculate_claims doesn't overflow

// 5ccc e802 de5f
// int(expm1( log1p( 1 ) / BLOCKS_PER_YEAR ) * 2**BRAVO_APR_PERCENT_SHIFT_PER_BLOCK / 100000 + 0.5)
// we use 100000 here instead of 10000 because we end up creating an additional 9x for vesting
#define BRAVO_APR_PERCENT_MULTIPLY_PER_BLOCK          ( (uint64_t( 0x5ccc ) << 0x20) \
                                                        | (uint64_t( 0xe802 ) << 0x10) \
                                                        | (uint64_t( 0xde5f )        ) \
                                                        )
// chosen to be the maximal value such that BRAVO_APR_PERCENT_MULTIPLY_PER_BLOCK * 2**64 * 100000 < 2**128
#define BRAVO_APR_PERCENT_SHIFT_PER_BLOCK             87

#define BRAVO_APR_PERCENT_MULTIPLY_PER_ROUND          ( (uint64_t( 0x79cc ) << 0x20 ) \
                                                        | (uint64_t( 0xf5c7 ) << 0x10 ) \
                                                        | (uint64_t( 0x3480 )         ) \
                                                        )

#define BRAVO_APR_PERCENT_SHIFT_PER_ROUND             83

// We have different constants for hourly rewards
// i.e. hex(int(math.expm1( math.log1p( 1 ) / HOURS_PER_YEAR ) * 2**BRAVO_APR_PERCENT_SHIFT_PER_HOUR / 100000 + 0.5))
#define BRAVO_APR_PERCENT_MULTIPLY_PER_HOUR           ( (uint64_t( 0x6cc1 ) << 0x20) \
                                                        | (uint64_t( 0x39a1 ) << 0x10) \
                                                        | (uint64_t( 0x5cbd )        ) \
                                                        )

// chosen to be the maximal value such that BRAVO_APR_PERCENT_MULTIPLY_PER_HOUR * 2**64 * 100000 < 2**128
#define BRAVO_APR_PERCENT_SHIFT_PER_HOUR              77

// These constants add up to GRAPHENE_100_PERCENT.  Each GRAPHENE_1_PERCENT is equivalent to 1% per year APY
// *including the corresponding 9x vesting rewards*
#define BRAVO_CURATE_APR_PERCENT              3875
#define BRAVO_CONTENT_APR_PERCENT             3875
#define BRAVO_LIQUIDITY_APR_PERCENT            750
#define BRAVO_PRODUCER_APR_PERCENT             750
#define BRAVO_POW_APR_PERCENT                  750

#define BRAVO_MIN_PAYOUT                        (asset(20,BRAVO_SYMBOL))

#define BRAVO_MIN_ACCOUNT_NAME_LENGTH          3
#define BRAVO_MAX_ACCOUNT_NAME_LENGTH         16

#define BRAVO_MIN_PERMLINK_LENGTH             0
#define BRAVO_MAX_PERMLINK_LENGTH             256
#define BRAVO_MAX_WITNESS_URL_LENGTH          2048

#define BRAVO_INIT_SUPPLY                     int64_t(52346237000)
#define BRAVO_MAX_SHARE_SUPPLY                int64_t(200000000000000ll)
#define BRAVO_MAX_SIG_CHECK_DEPTH             2

#define BRAVO_MIN_TRANSACTION_SIZE_LIMIT      1024
#define BRAVO_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define BRAVO_MAX_TRANSACTION_SIZE            (1024*64)
#define BRAVO_MIN_BLOCK_SIZE_LIMIT            (BRAVO_MAX_TRANSACTION_SIZE)
#define BRAVO_MAX_BLOCK_SIZE                  (BRAVO_MAX_TRANSACTION_SIZE*BRAVO_BLOCK_INTERVAL*2000)
#define BRAVO_BLOCKS_PER_HOUR                 (60*60/BRAVO_BLOCK_INTERVAL)
#define BRAVO_FEED_HISTORY_WINDOW             (12*7) // 3.5 days
#define BRAVO_MIN_FEEDS                       (BRAVO_MAX_WITNESSES/3) /// protects the network from conversions before price has been established
#define BRAVO_CONVERSION_DELAY                (fc::hours(BRAVO_FEED_HISTORY_WINDOW)) //3.5 day conversion

#define BRAVO_MIN_UNDO_HISTORY                10
#define BRAVO_MAX_UNDO_HISTORY                10000

#define BRAVO_MIN_TRANSACTION_EXPIRATION_LIMIT (BRAVO_BLOCK_INTERVAL * 5) // 5 transactions per block
#define BRAVO_BLOCKCHAIN_PRECISION            uint64_t( 1000 )

#define BRAVO_BLOCKCHAIN_PRECISION_DIGITS     3
#define BRAVO_MAX_INSTANCE_ID                 (uint64_t(-1)>>16)
/** NOTE: making this a power of 2 (say 2^15) would greatly accelerate fee calcs */
#define BRAVO_MAX_AUTHORITY_MEMBERSHIP        10
#define BRAVO_MAX_ASSET_WHITELIST_AUTHORITIES 10
#define BRAVO_MAX_URL_LENGTH                  127

#define BRAVO_IRREVERSIBLE_THRESHOLD          (75 * BRAVO_1_PERCENT)

#define VIRTUAL_SCHEDULE_LAP_LENGTH  ( fc::uint128(uint64_t(-1)) )
#define VIRTUAL_SCHEDULE_LAP_LENGTH2 ( fc::uint128::max_value() )

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define BRAVO_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define BRAVO_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define BRAVO_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define BRAVO_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define BRAVO_ROOT_POST_PARENT                (account_name_type())
///@}

