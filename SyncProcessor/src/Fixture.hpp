/*
 * Fixture.hpp
 *
 *  Created on: Mar 26, 2014
 *      Author: ashish
 */

#ifndef FIXTURE_HPP_
#define FIXTURE_HPP_

namespace tms
{

typedef int NotifStatusID;
typedef int TradeId;
typedef int Version;
typedef int RequestID;

struct Trade
{
	NotifStatusID _notifStatusID;
	TradeId _tradeID;
	Version _version;
};

typedef boost::shared_ptr<Trade> TradePtr;

struct TradeUpdate
{
	RequestID _requestID;
	TradePtr _trade;
};

typedef boost::shared_ptr<TradeUpdate> TradeUpdatPtr;

}

#endif /* FIXTURE_HPP_ */
