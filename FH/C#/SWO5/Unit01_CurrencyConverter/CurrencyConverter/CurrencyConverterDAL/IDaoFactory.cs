using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface IDaoFactory
    {
        public static ICurrencyTypeDao CurrencyTypeDao { get; }

        public static ICountryDao CountryDao { get;  }

        public static IExchangeRateDao ExchangeRateDao { get; }

        public static IInstantDao InstantDao { get;  }

    }
}
