using SWO5.Currency.DAL;
using SWO5.Currency.DAL.SQLe;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.Logic
{
    class SQLeBasedCurrencyConverter : ICurrencyConverter
    {
        // V1: Dynamic Factory in DAL-Interface - loads assembly
        // private IDaoFactory daoFactory = DaoFactoryProvider.GetDaoFactory();
        // V2: Conventional Factory Implementation
        private readonly IInstantDao instantDao;
        private readonly ICurrencyTypeDao currencyTypeDao;
        private readonly IExchangeRateDao exchangeRateDao;
        private readonly ICountryDao countryDao;

        public SQLeBasedCurrencyConverter()
        {
            IDaoFactory factory = new DaoFactorySQLe();
            instantDao = factory.InstantDao;
            currencyTypeDao = factory.CurrencyTypeDao;
            exchangeRateDao = factory.ExchangeRateDao;
            countryDao = factory.CountryDao;
        }

        public double ConvertFromTo(string from, string to, double value)
        {
            throw new NotImplementedException();
        }

        public double ConvertToEuro(string currency, double value)
        {
            throw new NotImplementedException();
        }

        public bool IsKnownCurrency(string currency)
        {
            throw new NotImplementedException();
        }
    }
}
