using System;
using System.Collections.Generic;
using System.Linq;
using SWO5.Currency.DAL;
using SWO5.Currency.Domain;
using SWO5.Currency.EF;

namespace SWO5.Currency.Logic
{
    public class EFBasedCurrencyConverter : ICurrencyConverter
    {
       
        // Version 2: with dependency to Dao-Implementation
        private readonly IInstantDao instantDao;
        private readonly ICurrencyTypeDao currencyTypeDao;
        private readonly ICountryDao countryDao;
        private readonly IExchangeRateDao exchangeRateDao;

        public EFBasedCurrencyConverter()
        {
            instantDao = EFDaoFactory.InstantDao;
            currencyTypeDao = EFDaoFactory.CurrencyTypeDao;
            countryDao = EFDaoFactory.CountryDao;
            exchangeRateDao = EFDaoFactory.ExchangeRateDao;
        }

        public string[] Currencies => currencyTypeDao.ReadAll().Select(e => e.Code).ToArray();

        public IList<CurrencyType> CurrencyTypes => currencyTypeDao.ReadAll();

        public double ConvertFromTo(string from, string to, double value)
        {
            if (from == null || to == null)
                throw new ArgumentOutOfRangeException(
                   "The supplied currency code " + value + " is not supported.");

            if (!IsKnownCurrency(from)
                                || !IsKnownCurrency(to))
                throw new ArgumentOutOfRangeException(
                    "The supplied currency codes are not supported.");

            double fromRate = ConvertToEuro(from, 1.0);
            double toRate = ConvertToEuro(to, 1.0);
            return (value * toRate) / fromRate;
        }

        public double ConvertToEuro(string currency, double value)
        {
            // Query for the most recent rate from the db
            if (IsKnownCurrency(currency))
            {

                Instant instant = instantDao.FindCurrentInstant();
                var rate = exchangeRateDao.FindExchangeRatesFor(instant, currency).Select(e => e.Rate);
                return rate.Count() == 0 ? value : value * rate.Single();
            }
            else
            {
                throw new ArgumentOutOfRangeException(
                    "The supplied currency code " + currency + " is not supported.");
            }
        }

        /*public IList<Tuple<DateTime, ExchangeRate>> ExchangeRatesFor(string currency)
        {
            // select all exchange rates for a given currency and all instants
            IList<Instant> instants = instantDao.ReadAll();
            List<Tuple<DateTime, ExchangeRate>> result =
                new List<Tuple<DateTime, ExchangeRate>>();
            foreach (Instant instant in instants)
            {
                // read exchange rates for currency and instant
                IList<ExchangeRate> rates = exchangeRateDao.FindExchangeRatesFor(instant, currency);
                var res = from rate in rates
                          select new Tuple<DateTime, ExchangeRate>(instant.Time, rate);
                result.AddRange(res.ToList());
            }
            return result;
        }*/


        // Version 2: no n+1 loading of data
        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currency)
        {
            // select all exchange rates for a given currency and all instants
            return exchangeRateDao.FindExchangeRatesFor(currency);
        }

        public IList<Country> FindCountriesFor(CurrencyType currency)
        {
            return countryDao.ReadForCurrencyType(currency);
        }

        public bool IsKnownCurrency(string currency)
        {
            // query if currency is available
            return currencyTypeDao.ReadAll().Select(e => e.Code).Contains(currency);
        }
    }
}
