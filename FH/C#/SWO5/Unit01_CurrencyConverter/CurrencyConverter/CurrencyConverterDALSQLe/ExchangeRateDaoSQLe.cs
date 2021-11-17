using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SWO5.Currency.DAL.SQLe
{
    class ExchangeRateDaoSQLe : AbstractDao<ExchangeRate>, IExchangeRateDao
    {
        public IList<ExchangeRate> FindExchangeRatesFor(Instant instant, string currencyCode)
        {
            throw new NotImplementedException();
        }

        protected override ExchangeRate FromDataRecord(IDataRecord record)
        {
            throw new NotImplementedException();
        }
    }
}
