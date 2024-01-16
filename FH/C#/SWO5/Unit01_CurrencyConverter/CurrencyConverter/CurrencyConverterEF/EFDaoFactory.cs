using SWO5.Currency.DAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.EF
{
    public class EFDaoFactory : IDaoFactory
    {

        public static ICurrencyTypeDao CurrencyTypeDao => new CurrencyTypeDaoEF();

        public static IExchangeRateDao ExchangeRateDao => new ExchangeRateDaoEF();

        public static IInstantDao InstantDao => new InstantDaoEF();

        public static ICountryDao CountryDao => new CountryDaoEF();
        

    }
}
