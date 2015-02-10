#include <tuple>
#include <cassert>
#include "StockInstrument.h"
#include "FinancialMarket.h"

FinancialMarket::FinancialMarket()
{
	// name, isin, mnemo
	typedef std::tuple<const std::string, const std::string, const std::string> TupleType;
	std::vector<TupleType> listing;

	// Name: TOTAL
	// ISIN: FR0000120271
	// Mmeno: FP
	listing.emplace_back(TupleType("TOTAL", "FR0000120271", "FP"));
	
	for (const auto& tuple : listing)
	{
		std::unique_ptr<Instrument> instrument(new StockInstrument(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple)));
		AddInstrument(std::move(instrument));
	}

    ob.AddOrder(Way::BUY, 10, 100);
    ob.AddOrder(Way::BUY, 5, 99);
    ob.AddOrder(Way::BUY, 8, 98);

    ob.AddOrder(Way::SELL, 5, 101);
    ob.AddOrder(Way::SELL, 8, 102);
    ob.AddOrder(Way::SELL, 10, 103);

    ob.Dump();
}

bool FinancialMarket::AddInstrument(std::unique_ptr<Instrument> instrument)
{
	assert(instrument != NULL);

	const auto it = referential_.find(instrument->GetISIN());
	if (it != referential_.end())
	{
		// Overwritting existing instrument...
		it->second = std::move(instrument);
	}
	else
	{
		referential_[instrument->GetISIN()] = std::move(instrument);
	}

	return true;
}