#pragma once

#include "transactions/TransactionFrame.h"
#include "ledger/OfferFrame.h"
#include <vector>
#include <functional>

namespace stellar
{

    class OfferExchange
    {

        LedgerDelta &mDelta;
        LedgerMaster &mLedgerMaster;

        std::vector<ClaimOfferAtom> mOfferTrail;
    public:

        OfferExchange(LedgerDelta &delta, LedgerMaster &ledgerMaster);

        // buys wheat with sheep from a single offer
        enum CrossOfferResult { eOfferPartial, eOfferTaken, eOfferCantConvert, eOfferError };
        CrossOfferResult crossOffer(OfferFrame& sellingWheatOffer,
            int64_t maxWheatReceived, int64_t& numWheatReceived,
            int64_t maxSheepSend, int64_t& numSheepSent);

        enum OfferFilterResult { eKeep, eSkip, eFail, eStop };

        enum ConvertResult { eOK, eFilterFail, eFilterStop, eBadOffer, eNotEnoughOffers };
        // buys wheat with sheep, crossing as many offers as necessary
        ConvertResult convertWithOffers(
            Currency& sheep, int64_t maxSheepSent, int64_t &sheepSend,
            Currency& wheat, int64_t maxWheatReceive, int64_t &weatReceived,
            std::function<OfferFilterResult(const OfferFrame &)> filter);

        std::vector<ClaimOfferAtom> getOfferTrail() { return mOfferTrail; }
    };

}