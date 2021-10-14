using System;

namespace SWO5.Currency.Logic
{
	public interface ICurrencyConverter
	{
		bool IsKnownCurrency(String currency);
		double ConvertToEuro(String currency, double value);
		double ConvertFromTo(String from, String to, double value);
	}
}
