using SWO5.Currency.DAL;
using SWO5.Currency.DAL.SQLe;
using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.Logic
{
    class SQLeBasedCurrencyConverter : ICurrencyConverter
    {
        // Version 1: Dynamic Factory in DAL-Interface - loads assembly - does not require project reference
        // private IDaoFactory daoFactory = DaoFactoryProvider.GetDaoFactory();
        // Version 2: Conventional Factory Implementation
        private readonly IInstantDao instantDao;
        private readonly ICurrencyTypeDao currencyTypeDao;
        private readonly IExchangeRateDao exchangeRateDao;
        private readonly ICountryDao countryDao;

        public SQLeBasedCurrencyConverter()
        {
            IDaoFactory factory = new DaoFactorySQLe(); // requires project reference
            instantDao = factory.InstantDao;
            currencyTypeDao = factory.CurrencyTypeDao;
            exchangeRateDao = factory.ExchangeRateDao;
            countryDao = factory.CountryDao;
        }

        public string[] Currencies => currencyTypeDao.ReadAll().Select(c => c.Code).ToArray();

        public IList<CurrencyType> CurrencyTypes => currencyTypeDao.ReadAll().ToList();

        public double ConvertFromTo(string from, string to, double value)
        {
            if (from == null || to == null)
                throw new ArgumentOutOfRangeException(
                   $"The supplied currency code {value} is not supported.");

            if (!IsKnownCurrency(from)
                                || !IsKnownCurrency(to))
                throw new ArgumentOutOfRangeException(
                    "The supplied currency codes are not supported.");

            double toRate = ConvertToEuro(to, 1.0);
            double fromRate = ConvertToEuro(from, 1.0);
            return (value * toRate) / fromRate;
        }

        public double ConvertToEuro(string currency, double value)
        {
            if( IsKnownCurrency( currency ) )
            {
                Instant instant = instantDao.FindCurrentInstant();
                IEnumerable<double> rates = exchangeRateDao
                                                .FindExchangeRatesFor(instant, currency)
                                                .Select(e => e.Rate);
                return value * rates.FirstOrDefault();
            } else
            {
                throw new ArgumentOutOfRangeException($"The supplied currency code {currency} is not supported.");
            }
        }

        public IList<Country> FindCountriesFor(CurrencyType currencyType)
        {
            return countryDao.ReadForCurrencyType(currencyType);
        }

        /*
        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            IList<Instant> instants = instantDao.ReadAll();
            List<Tuple<DateTime, ExchangeRate>> result = new List<Tuple<DateTime, ExchangeRate>>();
            foreach(Instant instant in instants)
            {
                IList<ExchangeRate> rates = exchangeRateDao.FindExchangeRatesFor(instant, currencyCode);
                var res = from rate in rates
                          select new Tuple<DateTime, ExchangeRate>(instant.Time, rate);
                result.AddRange(res.ToList());
            }
            return result;
        }*/
        // above is the "n+1 problem". bad idea!

        public IList<Tuple<DateTime, ExchangeRate>> FindExchangeRatesFor(string currencyCode)
        {
            return exchangeRateDao.FindExchangeRatesFor(currencyCode);
        }

            public bool IsKnownCurrency(string currency)
        {
            return currencyTypeDao.ReadAll().Select(e => e.Code).Contains(currency);
        }

        
    }
}
