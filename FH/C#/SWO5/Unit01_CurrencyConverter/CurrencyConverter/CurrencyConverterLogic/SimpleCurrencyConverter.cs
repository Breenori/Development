using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;

namespace SWO5.Currency.Logic
{
    class SimpleCurrencyConverter : ICurrencyConverter
    {
        private readonly Dictionary<string, double> exchangeRates = new Dictionary<string, double>(){
            {"EUR", 1.0},
            {"USD", 1.171608 },
            {"GBP", 0.907957 },
            {"CHF", 1.080198 }
        };

        public string[] Currencies => throw new NotImplementedException();

        public IList<CurrencyType> CurrencyTypes => throw new NotImplementedException();

        public double ConvertFromTo(string from, string to, double value)
        {

            if (from == null || to == null)
                throw new ArgumentOutOfRangeException(
                   $"The supplied currency code {value} is not supported.");

            if (!IsKnownCurrency(from)
                                || !IsKnownCurrency(to))
                throw new ArgumentOutOfRangeException(
                    "The supplied currency codes are not supported.");

            double toRate = ConvertToEuro(from, 1.0);
            double fromRate = ConvertToEuro(to, 1.0);
            return (value * toRate) / fromRate;
        }

        public double ConvertToEuro(string currency, double value)
        {
            double rate;
            if (IsKnownCurrency(currency)
                    && exchangeRates.TryGetValue(currency, out rate))
            {
                return value / rate;
            }
            else
            {
                throw new ArgumentOutOfRangeException(
                    $"The supplied currency code {currency} is not supported.");
            }
        }

        public IList<Country> FindCountriesFor(CurrencyType currencyType)
        {
            throw new NotImplementedException();
        }

        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            throw new NotImplementedException();
        }

        public bool IsKnownCurrency(string currency)
        {
            return currency != null && currency.Length != 0 && exchangeRates.Keys.Contains(currency);

        }
    }

}
