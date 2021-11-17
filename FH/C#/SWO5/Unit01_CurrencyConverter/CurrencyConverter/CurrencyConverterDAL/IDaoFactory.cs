using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface IDaoFactory
    {
        public ICurrencyTypeDao CurrencyTypeDao { get; }
        public ICountryDao CountryDao { get; }
        public IExchangeRateDao ExchangeRateDao {get;}
        public IInstantDao InstantDao { get; }
    }
}
