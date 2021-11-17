using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SWO5.Currency.DAL;

namespace SWO5.Currency.DAL.SQLe
{
    [DaoFactoryCandidate(ProviderName ="Microsoft SQL Server")]
    public class DaoFactorySQLe : IDaoFactory
    {
        public ICurrencyTypeDao CurrencyTypeDao => new CurrencyTypeDaoSQLe();

        public ICountryDao CountryDao => new CountryDaoSQLe();

        public IExchangeRateDao ExchangeRateDao => new ExchangeRateDaoSQLe();

        public IInstantDao InstantDao => new InstantDaoSQLe();
    }
}
