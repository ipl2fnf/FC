/*
 * FC.h
 *
 *  Created on: Mar 26, 2014
 *      Author: ashish
 */

#pragma once

#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>

#include <list>


#include "Fixture.hpp"

namespace tms
{
namespace stp
{

namespace mi = boost::multi_index;

typedef unsigned int FC_RequestID;

class Tag
{
public:
	virtual ~Tag()
	{
	}

	const FC_RequestID& getFC_RequestID() const
	{
		return _reqID;
	}

	const tms::TradeId& getTradeId() const
	{
		return _tradeID;
	}

	const tms::Trade& getOldTrade() const
	{
		return *_oldTrade;
	}

	const tms::TradeUpdate& getTradeUpdate() const
	{
		return *_tradeUpdate;
	}

protected:

	tms::TradeId _tradeID;
	FC_RequestID _reqID;
	tms::TradePtr _oldTrade;
	tms::TradeUpdatPtr _tradeUpdate;
};

typedef boost::shared_ptr<Tag> TagPtr;

class FC
{

public:

	FC(boost::function<void(TagPtr)> complitionProc_,
			const boost::posix_time::seconds& timeout_);
	virtual ~FC();

	FC_RequestID notif(const tms::TradeId& tradeId_,
			const NotifStatusID& newNotifStatus_, TagPtr tag_);

	void handleTradeUpdate(TradeUpdatPtr tradeUpdate_);

	void rune_once(const bool blocking_ = false);

private:

	struct seq
	{
	};

	typedef mi::multi_index_container<TagPtr, //
			mi::indexed_by< //
					mi::sequenced<mi::tag<seq> >, //
					mi::ordered_unique< //
							mi::tag<tms::TradeId>, //
							mi::const_mem_fun<Tag, const tms::TradeId&, &tms::stp::Tag::getTradeId> //
					> //
			> //
	> OpenRequests;

	boost::function<void(TagPtr)> _complitionProc;
	boost::posix_time::seconds _timeout;
	boost::posix_time::ptime _nextTimeoutAt;
	typedef std::list<TradeUpdatPtr> TradeUpdateToProcess;
	TradeUpdateToProcess _tradeUpdateToProcess;
	boost::mutex _mtx_tradeUpdateToProcess;
	FC_RequestID _nextReqID;
	boost::mutex _mtx;
};

} // namespace stp
} // namespace tms
