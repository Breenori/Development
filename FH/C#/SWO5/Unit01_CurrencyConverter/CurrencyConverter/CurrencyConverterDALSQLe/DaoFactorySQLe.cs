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
        public static ICurrencyTypeDao CurrencyTypeDao => new CurrencyTypeDaoSQLe();

        public static ICountryDao CountryDao => new CountryDaoSQLe();

        public static IExchangeRateDao ExchangeRateDao => new ExchangeRateDaoSQLe();

        public static IInstantDao InstantDao => new InstantDaoSQLe();
    }
}
