using System;
using System.Collections.Generic;
using System.Linq;

namespace SWO5.Currency.Logic
{
    class SimpleCurrencyConverter : ICurrencyConverter
    {
        private Dictionary<string, double> exchangeRates = new Dictionary<string, double>()
        {
            {"EUR", 1.0},
            {"USD", 1.1554662 },
            {"GBP", 0.85000515 },
            {"CHF", 1.071769 }
        };

        public double ConvertFromTo(string from, string to, double value)
        {
            if(!IsKnownCurrency(from) || !IsKnownCurrency(to))
            {
                throw new ArgumentOutOfRangeException($"One of the supplied currencies ({from},{to}) is not supported.");
            }

            double toRate = ConvertToEuro(to, 1.0);
            double fromRate = ConvertToEuro(from, 1.0);

            return value * (fromRate / toRate);
        }

        public double ConvertToEuro(string currency, double value)
        {
            double rate;
            if(IsKnownCurrency(currency) && exchangeRates.TryGetValue(currency, out rate))
            {
                return value * rate;
            } else
            {
                throw new ArgumentOutOfRangeException($"The supplied currency {currency} is not supported");
            }
        }

        public bool IsKnownCurrency(string currency)
        {
            return currency != null && exchangeRates.Keys.Contains(currency);
        }
    }
}
