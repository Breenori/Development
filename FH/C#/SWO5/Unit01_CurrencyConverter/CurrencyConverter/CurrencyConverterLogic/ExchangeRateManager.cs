using SWO5.Currency.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SWO5.Currency.DAL;
using SWO5.Currency.DAL.SQLe;

namespace SWO5.Currency.Logic
{
    class ExchangeRateManager : IManager<ExchangeRate>
    {
        private IExchangeRateDao exchangeRateDao = DaoFactorySQLe.ExchangeRateDao;

        public ExchangeRate Create(ExchangeRate entity)
        {
            entity.Id = exchangeRateDao.Create(entity);
            return entity;
        }

        public IList<ExchangeRate> FindAll()
        {
            return exchangeRateDao.ReadAll();
        }

        public ExchangeRate FindById(long identity)
        {
            return exchangeRateDao.ReadForIdentity(identity);
        }

        public ExchangeRate Update(ExchangeRate entity)
        {
            entity.Id = exchangeRateDao.Update(entity);
            return entity;
        }
    }
}
