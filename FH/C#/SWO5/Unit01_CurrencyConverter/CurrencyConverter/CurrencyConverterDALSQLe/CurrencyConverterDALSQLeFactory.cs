using System;

namespace SWO5.Currency.DAL.SQLe
{
    [DaoFactoryCandidate(ProviderName ="SQL Express")]
    public class CurrencyConverterDALSQLeFactory : IDaoFactory
    {
        public ICurrencyTypeDao CurrencyTypeDao => new CurrencyTypeDaoSQLe();
        
        public IInstantDao InstantDao => new InstantDaoSQLe();
        
        public IExchangeRateDao ExchangeRateDao => new ExchangeRateDaoSQLe();

        public ICountryDao CountryDao => new CountryDaoSQLe();
    }
}
