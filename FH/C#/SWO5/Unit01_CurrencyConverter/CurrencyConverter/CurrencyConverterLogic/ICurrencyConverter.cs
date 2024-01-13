using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;

namespace SWO5.Currency.Logic
{
    public interface ICurrencyConverter
    {
        bool IsKnownCurrency(String currency);

        double ConvertToEuro(String currency, double value);

        double ConvertFromTo(String from, String to, double value);
        String[] Currencies { get; }

        public IList<CurrencyType> CurrencyTypes { get; }

        public IList<Country> FindCountriesFor(CurrencyType currencyType);

       public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode);
    }
}
