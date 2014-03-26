/*
 * FC.cpp
 *
 *  Created on: Mar 26, 2014
 *      Author: ashish
 */

#include "FC.h"

namespace tms
{
namespace stp
{

FC::FC(boost::function<void(TagPtr)> complitionProc_,
		const boost::posix_time::seconds& timeout_) :
		_complitionProc(complitionProc_), //
		_timeout(timeout_), //
		_nextTimeoutAt(boost::posix_time::second_clock::local_time()), //
		_nextReqID(1)

{
}

FC::~FC()
{
}

FC_RequestID FC::notif(const tms::TradeId& tradeId_,
		const NotifStatusID& newNotifStatus_, TagPtr tag_)
{

}

void FC::handleTradeUpdate(TradeUpdatPtr tradeUpdate_)
{
}

void FC::rune_once(const bool blocking_)
{
}

} // namespace stp
} // namespace tms
