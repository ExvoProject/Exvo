// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2017 The Dash developers
// Copyright (c) 2017-2018 EXVO developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "CD 30/Mar/2018: Bitcoin Breaks Below $7K to Fall to 50-Day Low";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("00000b6321951f2ed170bbc9b7a360995176f2df418b0e275149bfce2fde3d6c");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31;
        consensus.nPowMaxAdjustUp = 23.7;

        consensus.nPowTargetTimespan = 30 * 60;
        consensus.nPowTargetSpacing = 60;

        consensus.fPowD106SwitchHeight = consensus.DifficultyAdjustmentInterval();

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 9576; 
        consensus.nMinerConfirmationWindow = 10080;  

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1524764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        // 1 day after inital mining
        consensus.MasternodePaymentStartHeight = 1440;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0x4a;
        pchMessageStart[2] = 0xc2;
        pchMessageStart[3] = 0xd1;
        nDefaultPort = 8585;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1522391995, 1084161, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("00000b1f125d98efe8eae2b305e76004a6ef35e8eb2880c2116e5787ef7628ff"));
        assert(genesis.hashMerkleRoot == uint256S("2f7e28f0f24f4589015b52a6a918739aaf54a9103d81eeda7e538a91e705431d"));

        vSeeds.push_back(CDNSSeedData("seed.exvo.io", "seed.exvo.io"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,33);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("00000b1f125d98efe8eae2b305e76004a6ef35e8eb2880c2116e5787ef7628ff")},
                { 12000, uint256S("00000000000d6321824f211678a61c785052a4c47679f6fcc3a246e1de148e75")}
            }
        };

        vTreasuryRewardAddress = {
            "3JhcWQAspDTnMiTmNbUHbBuNEH5TNYooVU"
        };

        // [1] UNIX timestamp of last known number of transactions
        // [2] total number of transactions between genesis and that timestamp
        //     (the tx=... number in the SetBestChain debug.log lines)
        // [3] estimated number of transactions per second after that timestamp
        chainTxData = ChainTxData{
            1522391995,
            1,
            1
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0000013dcc24cb29b041d5c89763f3aa44340faf556101783818a6ca8eb59e59");
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; 
        consensus.nPowMaxAdjustUp = 23.7; 

        consensus.nPowTargetTimespan = 1 * 60; 
        consensus.nPowTargetSpacing = 10; 

        consensus.fPowD106SwitchHeight = 30;

        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 6480; 
        consensus.nMinerConfirmationWindow = 8640; //1 day

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1524764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1524764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 1440;

        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0x1e;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xd1;
        nDefaultPort = 7565;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1522391996, 2010284, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0000066fa7536a73167169dbbcce5c8eecc9e45edfee9f928883cbdbb83c8258"));
        assert(genesis.hashMerkleRoot == uint256S(" 2f7e28f0f24f4589015b52a6a918739aaf54a9103d81eeda7e538a91e705431d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("0000066fa7536a73167169dbbcce5c8eecc9e45edfee9f928883cbdbb83c8258")}
            }
        };

        vTreasuryRewardAddress = {
            "93ASJtDuVYVdKXemH9BrtSMscznvsp9stD"
        };

        chainTxData = ChainTxData{
            1522391996,
            1,
            1
        };
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("000002db0642636c786f756062dd7a92f35a2be1665816f8bfa33111ae902b37");
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.BIP102HeightDelta = 0;

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 60; //1 minute
        consensus.nPowTargetSpacing = 1; //1 second

        consensus.fPowD106SwitchHeight = 30;

        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        consensus.nRuleChangeActivationThreshold = 5400; 
        consensus.nMinerConfirmationWindow = 7200; 

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 1440;

        pchMessageStart[0] = 0x6e;
        pchMessageStart[1] = 0x5c;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 7505;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1522391997, 1034529, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("00000ae7f805b5a9fe1762a15edee0d66a4b283ae8ef91ef7104faa5be0b6c76"));
        assert(genesis.hashMerkleRoot == uint256S("2f7e28f0f24f4589015b52a6a918739aaf54a9103d81eeda7e538a91e705431d"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("00000ae7f805b5a9fe1762a15edee0d66a4b283ae8ef91ef7104faa5be0b6c76") )
        };

        vTreasuryRewardAddress = {
            "2N6TJncxtMLSqEurFaEGtpLxdvq5wiVcR6S"
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}


std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const {
    size_t i = nHeight % vTreasuryRewardAddress.size();
    return vTreasuryRewardAddress[i];
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const {
    CExvoAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = boost::get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script; 
}

std::string CChainParams::GetTreasuryRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vTreasuryRewardAddress.size());
    return vTreasuryRewardAddress[i];
}

