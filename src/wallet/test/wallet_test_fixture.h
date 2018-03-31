// Copyright (c) 2017-2018 EXVO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef EXVO_WALLET_TEST_FIXTURE_H
#define EXVO_WALLET_TEST_FIXTURE_H

#include "test/test_exvo.h"

/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup: public TestingSetup {
    WalletTestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~WalletTestingSetup();
};

#endif

