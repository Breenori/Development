using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL
{
    public interface IExchangeRateDao : IDao<ExchangeRate>
    {
        IList<ExchangeRate> FindExchangeRatesFor(Instant instant, string currencyCode);
    }
}
